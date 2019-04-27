/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 17:26:37 by vbespalk          #+#    #+#             */
/*   Updated: 2018/08/02 17:26:39 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	reset(t_env *e)
{
	t_list		*obj_lst;
	t_scene		*scene;
	t_object	*obj;

	scene = e->scn;
	scene->cam->cam_transl = scene->cam->origin;
	scene->cam->angles = (t_vector){0.0f, 0.0f, 0.0f};
	scene->cam->fov = FOV;
	e->selected = NULL;
	obj_lst = e->scn->objs;
	while (obj_lst)
	{
		obj = (t_object *)(obj_lst->content);
		obj->translate = obj->pos;
		obj->rotate = obj->rot;
		obj->scale = obj->size;
		obj_lst = obj_lst->next;
	}
}

static void	delnod_obj(void	*nod, size_t size)
{
	t_object *obj;

	obj = (t_object *)nod;
	ft_memdel((void **)&obj->fig);
	ft_memdel(&nod);
}

void	delete_obj(t_list **obj_lst, Uint32 id)
{
	t_list 		*temp;
	t_list 		*prev;

	if (!obj_lst || !(*obj_lst))
		return ;
	temp = *obj_lst;
	if (temp && ((t_object *)(temp->content))->id == id)
	{
		*obj_lst = temp->next;
		ft_lstdelone(&temp, delnod_obj);
		return ;
	}
	while (temp)
	{
		prev = temp;
		temp = temp->next;
		if (((t_object *)(temp->content))->id == id)
		{
			prev->next = temp->next;
			ft_lstdelone(&temp, delnod_obj);
			return ;
		}
	}
}

int					ft_switch_col_mode(t_env *e, Sint32 sum)
{
	if (sum == SDLK_g)
		e->color_mode[MD_GRAYSCALE] = !(e->color_mode[MD_GRAYSCALE]);
	if (sum == SDLK_u)
		e->color_mode[MD_SEPIA] = !(e->color_mode[MD_SEPIA]);
	if (sum == SDLK_h)
		e->color_mode[MD_NEGATIVE] = !(e->color_mode[MD_NEGATIVE]);
	if (sum == SDLK_i)
		e->color_mode[MD_INVERTED] = !(e->color_mode[MD_INVERTED]);
	e->color_mode[MD_COLOR] = (e->color_mode[MD_GRAYSCALE]
				|| e->color_mode[MD_SEPIA]
				|| e->color_mode[MD_NEGATIVE]
				|| e->color_mode[MD_INVERTED]) ? false : true;
	if (e->color_mode[MD_COLOR])
        return (1);
	ft_col_mode(e->sdl, e->color_mode);
    return (1);
}


void                    ft_switch_skybox(t_sdl *sdl, t_scene *scn)
{
    int i;

    if (!scn->skybox)
    {
        scn->skybox = (t_skybox *) ft_smemalloc(sizeof(t_skybox), "ft_switch_skybox");
        scn->skybox->textur_id[0] = ft_strdup(SKBX_NEGZ);
        scn->skybox->textur_id[1] = ft_strdup(SKBX_NEGY);
        scn->skybox->textur_id[2] = ft_strdup(SKBX_NEGX);
        scn->skybox->textur_id[3] = ft_strdup(SKBX_POSZ);
        scn->skybox->textur_id[4] = ft_strdup(SKBX_POSY);
        scn->skybox->textur_id[5] = ft_strdup(SKBX_POSX);
		scn->skybox->bbx = ft_init_aabb(ft_3_zeropointnew(), ft_3_zeropointnew());
        i = -1;
		while (++i < BOX_FACES)
        {
        	printf("INIT TEX %i, addr %p\n", i, scn->skybox->textur[i]);
			if (!(scn->skybox->textur[i] = init_texture(&scn->textures, sdl,
														scn->skybox->textur_id[i])))
			{
				printf("WARNING: CANT LOAD SKYBOX FILE \"%s\" IS MISSING\n",
					   scn->skybox->textur_id[i]);
//				 DELETE SKYBOX STRUCTURE;
				ft_skybox_del(&scn->skybox);
				return;
			}
		}
		scn->skybox_on = false;
    }
    scn->skybox_on = !scn->skybox_on;
}

void	ft_set_exposure(Sint32 sum, t_object *o, t_env *e)
{
	if (sum == SDLK_0)
			o->exposure = EXP_COLOR;
	else if (sum == SDLK_1 && o->texture != NULL)
			o->exposure = EXP_TEXTR;
	else if (sum == SDLK_2)
	{
		if (o->checker == NULL)
			ft_set_checker(&o->checker, o->color.val);
		o->exposure = EXP_CHCKR;
	}
//	else if (sum == SDLK_3)
//	{
//		if (o->noise == NULL)
//			ft_set_noise(&o->noise, e, o->color.val, sum);
//		o->exposure = EXP_NOISE;
//	}
	else if (sum == SDLK_3 || sum == SDLK_4 || sum == SDLK_5 || sum == SDLK_6
			|| sum == SDLK_7 || sum == SDLK_8 || sum == SDLK_9)
	{
		if (o->noise == NULL)
			ft_set_noise(&o->noise, e, o->color.val, sum);
		else if (sum != SDLK_3)
			ft_update_noise(o->noise, e, o->color.val, sum);
		o->exposure = EXP_NOISE;
	}
}