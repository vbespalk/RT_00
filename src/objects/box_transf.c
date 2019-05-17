/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box_transf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 19:49:35 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/14 19:49:39 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	ft_translate_box(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m)
{
	t_box	*bx;

	if (!o)
		return (0);
	bx = (t_box *)o->fig;
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
	ft_3_transform_mat(tr_m, o->translate, o->rotate, bx->scale);
	ft_3_inv_trans_mat(inv_m, -o->translate, -o->rotate, 1.f / bx->scale);
	return (1);
}

int	ft_rotate_box(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m)
{
	t_box	*bx;

	if (!o)
		return (0);
	bx = (t_box *)o->fig;
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
	ft_3_transform_mat(tr_m, o->translate, o->rotate, bx->scale);
	ft_3_inv_trans_mat(inv_m, -o->translate, -o->rotate, 1.f / bx->scale);
	return (1);
}

int	ft_scale_box(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m)
{
	t_box		*bx;

	if (!o)
		return (0);
	bx = (t_box *)o->fig;
	if (key == SDLK_z || key == SDLK_r)
		bx->scale *= (1.f + SCALE_F);
	else
		bx->scale *= (1.f - SCALE_F);
	ft_3_transform_mat(tr_m, o->translate, o->rotate, bx->scale);
	ft_3_inv_trans_mat(inv_m, -o->translate, -o->rotate, 1.f / bx->scale);
	return (1);
}

int	ft_scale_hei_null(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m)
{
	(void)key;
	(void)o;
	(void)tr_m;
	(void)inv_m;
	return (0);
}
