/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clnd_transform.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 20:32:53 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/14 20:32:56 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	ft_translate_cylinder(Uint32 key, t_object *o, t_matrix *tr_m,
		t_matrix *inv_m)
{
	t_cylinder *clnd;

	if (!o)
		return (0);
	clnd = (t_cylinder *)o->fig;
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
	ft_3_transform_mat(tr_m, o->translate, o->rotate, clnd->r);
	ft_3_inv_trans_mat(inv_m, -o->translate, -o->rotate, 1.0f / clnd->r);
	return (1);
}

int	ft_rotate_cylinder(Uint32 key, t_object *o, t_matrix *tr_m,
		t_matrix *inv_m)
{
	t_cylinder *clnd;

	if (!o)
		return (0);
	clnd = (t_cylinder *)o->fig;
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
	ft_3_transform_mat(tr_m, o->translate, o->rotate, clnd->r);
	ft_3_inv_trans_mat(inv_m, -o->translate, -o->rotate, 1.0f / clnd->r);
	return (1);
}

int	ft_scale_cylinder(Uint32 key, t_object *o, t_matrix *tr_m,
		t_matrix *inv_m)
{
	t_cylinder	*clnd;
	float		scale;

	if (!o)
		return (0);
	clnd = (t_cylinder *)o->fig;
	if (key == SDLK_z)
		scale = 1.f + SCALE_F;
	else
		scale = 1.f - SCALE_F;
	clnd->r = clnd->r * scale > 900000 ? clnd->r : clnd->r * scale;
	if (clnd->maxh != FLT_MAX)
		clnd->maxh = clnd->maxh / scale;
	ft_3_transform_mat(tr_m, o->translate, o->rotate, clnd->r);
	ft_3_inv_trans_mat(inv_m, -o->translate, -o->rotate, 1.0f / clnd->r);
	return (1);
}

int	ft_scale_hei_cylinder(Uint32 key, t_object *o, t_matrix *tr_m,
		t_matrix *inv_m)
{
	t_cylinder	*clnd;
	float		scale;

	(void)tr_m;
	(void)inv_m;
	if (!o || ((t_cylinder *)o->fig)->maxh == FLT_MAX)
		return (0);
	clnd = (t_cylinder *)o->fig;
	if (key == SDLK_r)
		scale = 1 + SCALE_F;
	else
		scale = 1 - SCALE_F;
	clnd->maxh = clnd->maxh * scale;
	return (1);
}
