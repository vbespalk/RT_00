/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 17:26:37 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/06 18:54:59 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		delnod_obj(void *nod, size_t size)
{
	t_object	*obj;
	int			i;

	obj = (t_object *)nod;
	printf("DELNOD OBJ\n");
	if (obj->composed && (i = -1))
		while (++i < BOX_FACES)
			delnod_obj(((t_box *)obj->fig)->face[i], sizeof(t_object));
	ft_memdel((void **)&obj->fig);
	ft_memdel((void **)&obj->texture_id);
	if (obj->noise)
	{
		printf("DEL NOISE\n");
		ft_noise_del(&obj->noise);
	}
	if (obj->checker)
	{
		ft_checker_del(&obj->checker);
		printf("DEL CHECKER\n");
	}
	ft_memdel(&nod);
}

int				delete_obj(t_list **obj_lst, Uint32 id)
{
	t_list		*temp;
	t_list		*prev;

	if (!obj_lst || !(*obj_lst))
		return (0);
	temp = *obj_lst;
	if (temp && ((t_object *)(temp->content))->id == id)
	{
		*obj_lst = temp->next;
		ft_lstdelone(&temp, delnod_obj);
		return (1);
	}
	while (temp)
	{
		prev = temp;
		temp = temp->next;
		if (((t_object *)(temp->content))->id == id)
		{
			prev->next = temp->next;
			ft_lstdelone(&temp, delnod_obj);
			return (1);
		}
	}
	return (0);
}

int				ft_set_exposure(Sint32 sum, t_object *o, t_env *e)
{
	if (sum == SDLK_0 && !(o->tex_pnt = NULL))
		o->exposure = EXP_COLOR;
	else if (sum == SDLK_1 && o->texture != NULL)
	{
		o->exposure = EXP_TEXTR;
		o->tex_pnt = o->texture;
	}
	else if (sum == SDLK_2)
	{
		if (o->checker == NULL)
			ft_set_checker(&o->checker, o->color.val);
		o->tex_pnt = o->checker;
		o->exposure = EXP_CHCKR;
	}
	else if (sum == SDLK_3 || sum == SDLK_4 || sum == SDLK_5 || sum == SDLK_6
			|| sum == SDLK_7 || sum == SDLK_8 || sum == SDLK_9)
	{
		if (sum == SDLK_3 && o->noise == NULL)
			ft_set_procedural(&o->noise, TEX_LATTICE, o->color.val);
		o->tex_pnt = sum == SDLK_3 ?
				o->noise : e->smpl[CLAMP(sum - SDLK_4, 0, 5)];
		o->exposure = EXP_NOISE;
	}
	return (1);
}
