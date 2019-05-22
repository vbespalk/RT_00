/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_transform.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 20:00:02 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/14 20:00:04 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	ft_translate_cone(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m)
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

int	ft_rotate_cone(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m)
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

int	ft_scale_cone(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m)
{
	t_cone	*cone;

	if (!o)
		return (0);
	(void)tr_m;
	(void)inv_m;
	cone = (t_cone *)o->fig;
	if (key == SDLK_z)
		cone->tan = cone->tan * (1.0f + SCANG_F);
	else if (key == SDLK_x)
		cone->tan = cone->tan * (1.0f - SCANG_F);
	cone->sq_tan = cone->tan * cone->tan + 1;
	cone->r[0] = (cone->minh == -FLT_MAX || cone->minh == 0) ?
		FLT_MIN : fabsf(cone->minh * cone->tan);
	cone->r[1] = (cone->maxh == FLT_MAX || cone->maxh == 0) ?
		FLT_MIN : fabsf(cone->maxh * cone->tan);
	if (!(cone->minh == -FLT_MAX || cone->maxh == FLT_MAX))
		cone->texh = sqrtf(powf(cone->maxh - cone->minh, 2) +
			powf(cone->r[1] - cone->r[0], 2)) + cone->r[0] + cone->r[1];
	return (1);
}

int	ft_scale_hei_cone(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m)
{
	t_cone	*cone;
	float	h;
	float	sc;

	if (!o || (((t_cone *)o->fig)->maxh == FLT_MAX
			|| (((t_cone *)o->fig)->minh == -FLT_MAX)))
		return (0);
	cone = (t_cone *)o->fig;
	sc = key == SDLK_r ? 1.f + SCALE_F * 0.5f : 1.f - SCALE_F * 0.5f;
	h = fabsf(cone->maxh - cone->minh);
	cone->maxh *= sc;
	cone->minh *= sc;
	o->translate += (t_vector){FLT_MIN, (h * sc - h), FLT_MIN};
	cone->tan = cone->r[0] != FLT_MIN ?
		fabsf(cone->r[0] / cone->minh) : fabsf(cone->r[1] / cone->maxh);
	cone->sq_tan = cone->tan * cone->tan + 1;
//	cone->tan = cone->r[1] != FLT_MIN ?
//			fabsf(cone->r[1] / cone->maxh) : cone->tan;
//	cone->r[0] = cone->minh != -FLT_MAX ? fabsf(cone->minh * cone->tan) : FLT_MIN;
//	cone->r[1] = cone->maxh != FLT_MAX ? fabsf(cone->maxh * cone->tan) : FLT_MIN;
	if (!(cone->minh == -FLT_MAX || cone->maxh == FLT_MAX))
		cone->texh = sqrtf(powf(cone->maxh - cone->minh, 2) +
			powf(cone->r[1] - cone->r[0], 2)) + cone->r[0] + cone->r[1];
	ft_3_transform_mat(tr_m, o->translate, o->rotate, FLT_MIN);
	ft_3_inv_trans_mat(inv_m, -o->translate, -o->rotate, FLT_MIN);
	return (1);
}
