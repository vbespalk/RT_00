/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torus_mapping.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 21:13:57 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/12 21:14:05 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** angls[0] for phi
** angls[1] for theta
*/

Uint32		ft_map_torus(t_object *o, void *tex, t_vector coll)
{
	Uint32		col;
	float		ang[2];
	int			xy[2];
	float		dot;
	SDL_Surface	*t;

	t = (SDL_Surface *)tex;
	coll = ft_3_vector_scale(coll, 1 / ((t_torus *)o->fig)->r_inner);
	ang[0] = atan2f(coll[2], coll[0]);
	if (!(IN_RANGE(ang[0], 0.0f, 2.0f * M_PI)))
		ang[0] = (float)(ang[0] < 0.0f ? ang[0] + 2 * M_PI : ang[0] - 2 * M_PI);
	dot = ft_3_vector_dot(coll - ft_3_vector_scale(ft_3_tounitvector((t_vector)
		{coll[0], 0, coll[2]}), ((t_torus *)o->fig)->r_outer /
		((t_torus *)o->fig)->r_inner), (t_vector){coll[0], 0, coll[2]});
	ang[1] = 0.5f * acosf(CLAMP(coll[1], -1, 1));
	if (coll[1] > 0)
		ang[1] = (float)(dot < 0 ? M_PI * 0.25 - ang[1] : M_PI * 0.25 + ang[1]);
	else
		ang[1] = (float)(dot > 0 ? M_PI * 0.25 + ang[1] : 1.25 * M_PI - ang[1]);
	xy[0] = (int)((t->w - 1) * ang[0] * 0.5f * (float)M_1_PI);
	xy[1] = (int)((t->h - 1) * ang[1] * (float)M_1_PI);
	if (!(IN_RANGE(xy[0], 0, t->w - 1) && IN_RANGE(xy[1], 0, t->h - 1)))
		return (UINT32_MAX);
	ft_memcpy(&col, (Uint32 *)t->pixels + xy[1] * t->w + xy[0], sizeof(Uint32));
	return (col);
}

/*
** pnt[0] for normalized coll value
** pnt[1] for center inside torus ring
*/

Uint32		ft_checker_tor(t_object *o, void *tex, t_vector coll)
{
	float		uv[2];
	float		theta;
	float		phi;
	t_vector	pnt[2];
	t_checkbrd	*t;

	t = (t_checkbrd *)tex;
	phi = atan2f(coll[2], coll[0]);
	if (!(IN_RANGE(phi, 0.0f, 2.0f * M_PI)))
		phi = phi < 0.0f ? phi + 2 * (float)M_PI : phi - 2 * (float)M_PI;
	pnt[0] = ft_3_vector_scale(coll, 1 / ((t_torus *)o->fig)->r_inner);
	pnt[1] = pnt[0] - ft_3_tounitvector((t_vector)
			{pnt[0][0], FLT_MIN, pnt[0][2]});
	theta = (pnt[1][0] * pnt[1][0] + pnt[1][2] * pnt[1][2] <= 1) ?
			acosf(-CLAMP(pnt[0][1], -1, 1)) : acosf(CLAMP(pnt[0][1], -1, 1));
	uv[0] = (1 + phi * (float)M_1_PI);
	uv[1] = theta * (float)M_1_PI;
	if ((fmodf(uv[0] * t->size, 1) > 0.5) ^
		(fmodf(uv[1] * t->size, 1) > 0.5))
		return (t->noise[0] ? o->ft_procedural(o, t->noise[0], coll) :
				t->color[0]);
	return (t->noise[1] ? o->ft_procedural(o, t->noise[1], coll) :
				t->color[1]);
}

Uint32		ft_procedural_tor(t_object *o, void *tex, t_vector coll)
{
	t_procedural	*t;
	t_vector		point;

	t = (t_procedural *)tex;
	point = ft_3_vector_scale(coll, 1 / ((t_torus *)o->fig)->r_inner);
	return (t->ft_get_color(t, ft_3_vector_scale(point, t->scale)));
}
