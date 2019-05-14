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

Uint32		ft_map_torus(t_object *o, void *tex, t_vector coll)
{
	Uint32		col;
	float		theta;
	float		phi;
	int			xy[2];
	t_vector	cnt;
	SDL_Surface	*t;

	t = (SDL_Surface *)tex;
	coll = ft_3_vector_scale(coll, 1 / ((t_torus *)o->fig)->r_inner);
	phi = atan2f(coll[2], coll[0]);
	if (!(IN_RANGE(phi, 0.0f, 2.0f * M_PI)))
		phi = phi < 0.0f ? phi + 2 * (float)M_PI : phi - 2 * (float)M_PI;
	cnt = coll - ft_3_tounitvector((t_vector){coll[0], FLT_MIN, coll[2]});
	theta = 0.5f * acosf(CLAMP(coll[1], -1, 1));
	if (!(IN_RANGE(theta, 0.0f, M_PI)))
		theta = theta < 0.0f ? theta + (float)M_PI : theta - (float)M_PI;
	if (IN_RANGE(cnt[0] * cnt[0] + cnt[2] * cnt[2], 0, 1))
		theta = (float)M_PI - theta;
	xy[0] = (int)((t->w - 1) * phi * 0.5f * (float)M_1_PI);
	xy[1] = (int)((t->h - 1) * theta * (float)M_1_PI);
	if (!(IN_RANGE(xy[0], 0, t->w) && IN_RANGE(xy[1], 0, t->h)))
		return (UINT32_MAX);
	ft_memcpy(&col, (Uint32 *)t->pixels + xy[1] * t->w
		+ xy[0], sizeof(Uint32));
	return (col);
}

/*
** pnt[0] for normilized coll value
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
