/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prbld_transform.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 21:12:58 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/14 21:13:01 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	ft_translate_prbld(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m)
{
	t_prbld	*prbl;

	if (!o)
		return (0);
	prbl = (t_prbld *)o->fig;
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
	ft_3_transform_mat(tr_m, o->translate, o->rotate, prbl->r);
	ft_3_inv_trans_mat(inv_m, -o->translate, -o->rotate, 1.f / prbl->r);
	return (1);
}

int	ft_rotate_prbld(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m)
{
	t_prbld *prbl;

	if (!o)
		return (0);
	prbl = (t_prbld *)o->fig;
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
	ft_3_transform_mat(tr_m, o->translate, o->rotate, prbl->r);
	ft_3_inv_trans_mat(inv_m, -o->translate, -o->rotate, 1.f / prbl->r);
	return (1);
}

int	ft_scale_prbld(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m)
{
	t_prbld	*prbl;
	float	scale;

	if (!o)
		return (0);
	prbl = (t_prbld *)o->fig;
	scale = key == SDLK_z ? 1.f + SCALE_F : 1.f - SCALE_F;
	if (IN_RANGE(prbl->r * scale, 1.f, 800000.f))
	{
		prbl->r *= scale;
		prbl->maxh = prbl->maxh == FLT_MAX ? FLT_MAX : prbl->maxh / scale;
	}
	ft_3_transform_mat(tr_m, o->translate, o->rotate, prbl->r);
	ft_3_inv_trans_mat(inv_m, -o->translate, -o->rotate, 1.f / prbl->r);
	return (1);
}

int	ft_scale_hei_prbld(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m)
{
	t_prbld	*prbl;
	float	scale;

	(void)tr_m;
	(void)inv_m;
	if (!o || ((t_prbld *)o->fig)->maxh == FLT_MAX)
		return (0);
	prbl = (t_prbld *)o->fig;
	scale = key == SDLK_r ? 1.f + SCALE_F : 1.f - SCALE_F;
	prbl->maxh = prbl->maxh == FLT_MAX ? FLT_MAX : prbl->maxh * scale * scale;
	prbl->r = prbl->r / scale;
	ft_3_transform_mat(tr_m, o->translate, o->rotate, prbl->r);
	ft_3_inv_trans_mat(inv_m, -o->translate, -o->rotate, 1.f / prbl->r);
	return (1);
}
