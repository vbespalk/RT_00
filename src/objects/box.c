/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 19:43:09 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/14 19:43:11 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_box		*ft_boxnew(t_object *o)
{
	t_box	*bx;

	o->ft_collide = ft_collide_box;
	o->ft_is_inside = ft_is_inside_box;
	o->ft_get_norm = ft_get_norm_plane;
	o->ft_translate = ft_translate_box;
	o->ft_rotate = ft_rotate_box;
	o->ft_scale = ft_scale_box;
	o->ft_scale_height = ft_scale_box;
	o->ft_mapping = ft_map_box;
	o->ft_checker = ft_checker_box;
	o->ft_procedural = ft_procedural_box;
	o->composed = true;
	bx = ft_smemalloc(sizeof(t_box), "ft_boxnew");
	bx->whl[0] = 10;
	bx->whl[1] = 10;
	bx->whl[2] = 10;
	bx->scale = 1;
	return (bx);
}

void		ft_init_box_pln(t_box *bx, t_plane *pln, int i)
{
	pln->is_in_box = true;
	if (i % 3 == 0)
	{
		bx->face[i]->translate = i == 0 ? (t_vector) {-bx->whl[0], 0, 0} :
				(t_vector) {bx->whl[0], 0, 0};
		pln->len_wh[0] = bx->whl[2];
		pln->len_wh[1] = bx->whl[1];
		bx->face[i]->rotate = (t_vector){FLT_MIN, FLT_MIN, DEG_TO_RAD(90)};
	}
	else if (i % 3 == 1)
	{
		bx->face[i]->translate = i == 1 ? (t_vector){0, -bx->whl[1], 0} :
				(t_vector){0, bx->whl[1], 0};
		pln->len_wh[0] = bx->whl[2];
		pln->len_wh[1] = bx->whl[0];
		bx->face[i]->rotate = (t_vector){FLT_MIN, FLT_MIN, FLT_MIN};
	}
	else
	{
		bx->face[i]->translate = i == 2 ? (t_vector){0, 0, -bx->whl[2]} :
				(t_vector){0, 0, bx->whl[2]};
		pln->len_wh[0] = bx->whl[1];
		pln->len_wh[1] = bx->whl[0];
		bx->face[i]->rotate = (t_vector){DEG_TO_RAD(90), FLT_MIN, FLT_MIN};
	}
}

char		*ft_parse_box(char **content, t_object *o)
{
	t_box		*bx;
	t_plane		*pln;
	int			i;

	bx = ft_boxnew(o);
	ft_get_attr(content, "length", (void *)(&(bx->whl[2])), DT_FLOAT);
	ft_get_attr(content, "width", (void *)(&(bx->whl[0])), DT_FLOAT);
	ft_get_attr(content, "height", (void *)(&(bx->whl[1])), DT_FLOAT);
	i = -1;
	while (++i < BOX_FACES)
	{
		bx->face[i] = ft_smemalloc(sizeof(t_object), "ft_init_box");
		bx->face[i]->fig = ft_planenew(bx->face[i]);
		pln = (t_plane *)bx->face[i]->fig;
		ft_init_box_pln(bx, pln, i);
		pln->ratio = pln->len_wh[1] / pln->len_wh[0];
		ft_3_transform_mat(&(bx->face[i]->transform), bx->face[i]->translate,
			bx->face[i]->rotate, pln->len_wh[0]);
		ft_3_inv_trans_mat(&(bx->face[i]->inverse), -bx->face[i]->translate,
			-bx->face[i]->rotate, 1.0f / pln->len_wh[0]);
	}
	ft_3_transform_mat(&(o->transform), o->translate, o->rotate, FLT_MIN);
	ft_3_inv_trans_mat(&(o->inverse), -o->translate, -o->rotate, FLT_MIN);
	return ((void *)bx);
}
