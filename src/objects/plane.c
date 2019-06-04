/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 13:25:05 by domelche          #+#    #+#             */
/*   Updated: 2018/08/23 13:27:24 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_plane	*ft_planenew(t_object *o)
{
	t_plane	*pln;

	o->ft_collide = ft_collide_plane;
	o->ft_is_inside = ft_is_inside_plane;
	o->ft_get_norm = ft_get_norm_plane;
	o->ft_translate = ft_translate_plane;
	o->ft_rotate = ft_rotate_plane;
	o->ft_scale = ft_scale_plane;
	o->ft_scale_height = ft_scale_plane;
	o->ft_mapping = ft_map_plane;
	o->ft_checker = ft_checker_pln;
	o->ft_procedural = ft_procedural_pln;
	pln = ft_smemalloc(sizeof(t_plane), "ft_planenew");
	pln->is_in_box = false;
	pln->len_wh[0] = FLT_MIN;
	pln->len_wh[1] = FLT_MIN;
	return (pln);
}

void	*ft_parse_plane(char **content, t_object *o)
{
	t_plane	*pln;

	pln = ft_planenew(o);
	ft_get_attr(content, "width", (void *)(&(pln->len_wh[0])), DT_FLOAT);
	ft_get_attr(content, "height", (void *)(&(pln->len_wh[1])), DT_FLOAT);
	if (pln->len_wh[0] == FLT_MIN || pln->len_wh[1] == FLT_MIN)
	{
		pln->len_wh[0] = FLT_MIN;
		pln->len_wh[1] = FLT_MIN;
	}
	pln->ratio = (pln->len_wh[0] != FLT_MIN) ?
			pln->len_wh[1] / pln->len_wh[0] : FLT_MIN;
	ft_3_transform_mat(&(o->transform), o->translate, o->rotate,
			pln->len_wh[0]);
	ft_3_inv_trans_mat(&(o->inverse), -o->translate, -o->rotate,
			(pln->len_wh[0] == FLT_MIN ? FLT_MIN : 1.0f / pln->len_wh[0]));
	return ((void *)pln);
}

int		ft_translate_plane(Uint32 key, t_object *o, t_matrix *tr_m,
													t_matrix *inv_m)
{
	t_plane *pln;

	if (!o)
		return (0);
	pln = (t_plane *)o->fig;
	if (key == SDLK_d)
		o->translate[2] += TRANS_F;
	if (key == SDLK_a)
		o->translate[2] -= TRANS_F;
	if (key == SDLK_w)
		o->translate[1] += TRANS_F;
	if (key == SDLK_s)
		o->translate[1] -= TRANS_F;
	if (key == SDLK_e)
		o->translate[0] += TRANS_F;
	if (key == SDLK_q)
		o->translate[0] -= TRANS_F;
	ft_3_transform_mat(tr_m, o->translate, o->rotate,
			(pln->len_wh[0] == FLT_MIN ? FLT_MIN : pln->len_wh[0]));
	ft_3_inv_trans_mat(inv_m, -o->translate, -o->rotate,
			(pln->len_wh[0] == FLT_MIN ? FLT_MIN : 1.0f / pln->len_wh[0]));
	return (1);
}

int		ft_rotate_plane(Uint32 key, t_object *o, t_matrix *tr_m,
													t_matrix *inv_m)
{
	t_plane		*pln;

	if (!o)
		return (0);
	pln = (t_plane *)o->fig;
	if (key == SDLK_DOWN)
		o->rotate[2] += ROTAT_F;
	else if (key == SDLK_UP)
		o->rotate[2] -= ROTAT_F;
	else if (key == SDLK_LEFT)
		o->rotate[1] -= ROTAT_F;
	else if (key == SDLK_RIGHT)
		o->rotate[1] += ROTAT_F;
	else if (key == SDLK_PAGEDOWN)
		o->rotate[0] += ROTAT_F;
	else if (key == SDLK_PAGEUP)
		o->rotate[0] -= ROTAT_F;
	ft_3_transform_mat(tr_m, o->translate, o->rotate, pln->len_wh[0]);
	ft_3_inv_trans_mat(inv_m, -o->translate, -o->rotate,
		(pln->len_wh[0] == FLT_MIN ? FLT_MIN : 1.0f / pln->len_wh[0]));
	return (1);
}

int		ft_scale_plane(Uint32 key, t_object *o, t_matrix *tr_m,
													t_matrix *inv_m)
{
	t_plane	*pln;
	float	scale;

	if (!o)
		return (0);
	pln = (t_plane *)o->fig;
	if (pln->len_wh[0] == FLT_MIN || pln->len_wh[1] == FLT_MIN)
		return (0);
	scale = (key == SDLK_z || key == SDLK_r) ? 1.f + SCALE_F : 1.f - SCALE_F;
	if (!IN_RANGE(pln->len_wh[0] * scale, MIN_R, MAX_R) ||
			!IN_RANGE(pln->len_wh[1] * scale, MIN_R, MAX_R))
		return (0);
	pln->len_wh[0] *= scale;
	pln->len_wh[1] *= scale;
	ft_3_transform_mat(tr_m, o->translate, o->rotate, pln->len_wh[0]);
	ft_3_inv_trans_mat(inv_m, -o->translate, -o->rotate, 1.f / pln->len_wh[0]);
	return (1);
}
