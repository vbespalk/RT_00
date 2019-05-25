/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 21:07:32 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/14 21:07:35 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_disk	*ft_disknew(t_object *o)
{
	t_disk	*dsk;

	o->ft_collide = ft_collide_disk;
	o->ft_is_inside = ft_is_inside_disk;
	o->ft_get_norm = ft_get_norm_disk;
	o->ft_translate = ft_translate_disk;
	o->ft_rotate = ft_rotate_disk;
	o->ft_scale = ft_scale_disk;
	o->ft_scale_height = ft_scale_disk;
	o->ft_mapping = ft_map_disk;
	o->ft_checker = ft_checker_dsk;
	o->ft_procedural = ft_procedural_dsk;
	dsk = ft_smemalloc(sizeof(t_disk), "ft_disknew");
	dsk->out_r = FLT_MAX;
	dsk->in_r = FLT_MIN;
	return (dsk);
}

char	*ft_parse_disk(char **content, t_object *o)
{
	t_disk		*dsk;

	dsk = ft_disknew(o);
	ft_get_attr(content, "inner_radius", (void *)(&(dsk->in_r)), DT_FLOAT);
	ft_get_attr(content, "outer_radius", (void *)(&(dsk->out_r)), DT_FLOAT);
	if (dsk->in_r > dsk->out_r)
		ft_swap_float(&dsk->in_r, &dsk->out_r);
	dsk->sq_in_r = dsk->in_r * dsk->in_r;
	dsk->sq_out_r = dsk->out_r * dsk->out_r;
	ft_3_transform_mat(&(o->transform), o->translate, o->rotate, FLT_MIN);
	ft_3_inv_trans_mat(&(o->inverse), -o->translate, -o->rotate, FLT_MIN);
	return ((void *)dsk);
}

int		ft_translate_disk(Uint32 key, t_object *o, t_matrix *tr_m,
													t_matrix *inv_m)
{
	if (!o)
		return (0);
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
	ft_3_transform_mat(tr_m, o->translate, o->rotate, FLT_MIN);
	ft_3_inv_trans_mat(inv_m, -o->translate, -o->rotate, FLT_MIN);
	return (1);
}

int		ft_rotate_disk(Uint32 key, t_object *o, t_matrix *tr_m,
												t_matrix *inv_m)
{
	if (!o)
		return (0);
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
	ft_3_transform_mat(tr_m, o->translate, o->rotate, FLT_MIN);
	ft_3_inv_trans_mat(inv_m, -o->translate, -o->rotate, FLT_MIN);
	return (1);
}

int		ft_scale_disk(Uint32 key, t_object *o, t_matrix *tr_m,
												t_matrix *inv_m)
{
	t_disk	*dsk;
	float	scale;

	if (!o)
		return (0);
	dsk = (t_disk *)o->fig;
	scale = key == SDLK_z || key == SDLK_r ? 1 + SCALE_F : 1 - SCALE_F;
	if (!(dsk->out_r != FLT_MAX && IN_RANGE(dsk->out_r * scale, MIN_R, MAX_R)))
		return (0);
	dsk->out_r = dsk->out_r == FLT_MAX ? FLT_MAX : dsk->out_r * scale;
	dsk->in_r = dsk->in_r == FLT_MIN ? FLT_MIN : dsk->in_r * scale;
	dsk->sq_in_r = dsk->in_r * dsk->in_r;
	dsk->sq_out_r = dsk->out_r * dsk->out_r;
	ft_3_transform_mat(tr_m, o->translate, o->rotate, FLT_MIN);
	ft_3_inv_trans_mat(inv_m, -o->translate, -o->rotate, FLT_MIN);
	return (1);
}
