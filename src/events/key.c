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
	if (sum == SDLK_j)
		e->color_mode[MD_SEPIA] = !(e->color_mode[MD_SEPIA]);
	if (sum == SDLK_n)
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