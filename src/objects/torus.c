/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 22:17:04 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/14 22:17:06 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_torus	*ft_torusnew(t_object *o)
{
	t_torus	*trs;

	o->ft_collide = ft_collide_torus;
	o->ft_is_reachable = ft_is_reachable_torus;
	o->ft_is_inside = ft_is_inside_torus;
	o->ft_get_norm = ft_get_norm_torus;
	o->ft_translate = ft_translate_torus;
	o->ft_rotate = ft_rotate_torus;
	o->ft_scale = ft_scale_torus;
	o->ft_scale_height = ft_scale_torus;
	o->ft_mapping = ft_map_torus;
	o->ft_checker = ft_checker_tor;
	o->ft_procedural = ft_procedural_tor;
	trs = ft_smemalloc(sizeof(t_torus), "ft_torusnew");
	trs->r_inner = 2.f;
	trs->r_outer = 5.f;
	return (trs);
}

char	*ft_parse_torus(char **content, t_object *o)
{
	t_torus		*trs;

	trs = ft_torusnew(o);
	ft_get_attr(content, "inner_radius", (void *)(&(trs->r_inner)), DT_FLOAT);
	ft_get_attr(content, "outer_radius", (void *)(&(trs->r_outer)), DT_FLOAT);
	if (trs->r_inner > trs->r_outer)
		ft_swap_float(&(trs->r_inner), &(trs->r_outer));
//	trs->scale = trs->r_outer;
//	trs->r_inner /= trs->scale;
//	trs->r_outer = 1.f;
//	ft_3_transform_mat(&(o->transform), o->translate, o->rotate, trs->scale);
//	ft_3_inv_trans_mat(&(o->inverse), -o->translate, -o->rotate, 1.f / trs->scale);
	ft_3_transform_mat(&(o->transform), o->translate, o->rotate, FLT_MIN);
	ft_3_inv_trans_mat(&(o->inverse), -o->translate, -o->rotate, FLT_MIN);
	return ((void *)trs);
}

int		ft_translate_torus(Uint32 key, t_object *o, t_matrix *tr_m,
												t_matrix *inv_m)
{
//	t_torus *trs;

	if (!o)
		return (0);
//	trs = (t_torus *)o->fig;
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
//	ft_3_transform_mat(&(o->transform), o->translate, o->rotate, trs->scale);
//	ft_3_inv_trans_mat(&(o->inverse), -o->translate, -o->rotate, 1.f / trs->scale);
	return (1);
}

int		ft_rotate_torus(Uint32 key, t_object *o, t_matrix *tr_m,
												t_matrix *inv_m)
{
//	t_torus *trs;

	if (!o)
		return (0);
//	trs = (t_torus *)o->fig;
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
//	ft_3_transform_mat(&(o->transform), o->translate, o->rotate, trs->scale);
//	ft_3_inv_trans_mat(&(o->inverse), -o->translate, -o->rotate, 1.f / trs->scale);
	return (1);
}

int		ft_scale_torus(Uint32 key, t_object *o, t_matrix *tr_m,
												t_matrix *inv_m)
{
	t_torus	*trs;
	float	scale;

	if (!o)
		return (0);
//	(void)tr_m;
//	(void)inv_m;
	trs = (t_torus *)o->fig;
	scale = (key == SDLK_z || key == SDLK_r) ? 1.f + SCALE_F : 1.f - SCALE_F;
	trs->r_inner = trs->r_inner * scale;
	trs->r_outer = trs->r_outer * scale;
//	trs->scale *= scale;
	printf("INNER  %f OUTER %f\n", trs->r_inner, trs->r_outer);
//	ft_3_transform_mat(tr_m, o->translate, o->rotate, trs->scale);
//	ft_3_inv_trans_mat(inv_m, -o->translate, -o->rotate, 1.f / trs->scale);
	return (1);
}
