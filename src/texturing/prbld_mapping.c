/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prbld_mapping.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 18:25:52 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/10 18:25:55 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static Uint32	ft_map_caps(t_prbld *prbl, SDL_Surface *tex,
		t_vector hit, float hei)
{
	return (UINT32_MAX);
}

Uint32			ft_map_prbld(t_object *o, SDL_Surface *tex, t_vector hit)
{
	t_prbld		*prbl;
	Uint32		col;
	float		hei;
	float		phi;
	int			xy[2];

	prbl = ((t_prbld *)o->fig);
	if (((t_prbld *)o->fig)->maxh == FLT_MAX)
		return (o->color.val);
	hei = sqrtf(hit[1] / prbl->maxh);
	if (IN_RANGE(hit[1], -1e-6, 1e-6))
		return (ft_map_caps(((t_prbld *)o->fig), tex, hit, hei));
	phi = atan2f(hit[0], hit[2]);
	if (!(IN_RANGE(phi, 0.0f, 2 * M_PI)))
		phi = phi < 0 ? phi + 2 * (float)M_PI : phi;
	xy[0] = (int)((tex->w - 1) * phi * 0.5f * (float)M_1_PI);
	xy[1] = (int)((tex->h - 1) * hei);
	if (!(IN_RANGE(xy[0], 0, tex->w) && IN_RANGE(xy[1], 0, tex->h)))
		return (0xff);
	ft_memcpy(&col, (Uint32 *)tex->pixels + xy[1] * tex->w
					+ xy[0], sizeof(Uint32));
	return (col);
}

Uint32			ft_procedural_prbld(t_object *o, t_procedural *tex,
		t_vector coll)
{
	t_prbld		*prbl;
	t_vector	point;

	prbl = (t_prbld *)o->fig;
	if (prbl->maxh == FLT_MAX)
	{
		point = ft_3_vector_scale(coll, (1 / sqrtf(o->dist)));
		point[1] = coll[1] / sqrtf(o->dist);
	}
	else
	{
		point = ft_3_vector_scale(coll, (1 / sqrtf(4.0f * prbl->maxh)));
		point[1] = coll[1] / (prbl->maxh);
	}
	return (tex->ft_get_color(tex, NULL, ft_3_vector_scale(point, tex->scale)));
}

Uint32			ft_checker_prbld(t_object *o, t_checkbrd *tex, t_vector coll)
{
	float		uv[2];
	t_prbld		*prbl;
	float		phi;
	t_vector	pnt;

	prbl = (t_prbld *)o->fig;
	phi = atan2f(coll[2], coll[0]);
	if (!(IN_RANGE(phi, 0.0f, 2.0f * M_PI)))
		phi = phi < 0.0f ? phi + 2 * (float)M_PI : phi - 2 * (float)M_PI;
	uv[0] = phi / (float)M_PI + 1;
	if (prbl->maxh != FLT_MAX && IN_RANGE(coll[1], -1e-6, 1e-6))
	{
		pnt = ft_3_vector_scale(coll, (1 / sqrtf(4.0f * prbl->maxh)));
		uv[1] = sqrtf(powf(pnt[2], 2) + powf(pnt[0], 2));
	}
	else
		uv[1] = prbl->maxh == FLT_MAX ? coll[1] / sqrtf(o->dist) :
				sqrtf(coll[1] / prbl->maxh);
	if (!((fmodf(uv[0] * tex->size, 1) > 0.5) ^
		(fmodf(uv[1] * tex->size, 1) > 0.5)))
		return (tex->noise[0] ? o->ft_procedural(o, tex->noise[0], coll) :
			tex->color[0]);
		return (tex->noise[1] ? o->ft_procedural(o, tex->noise[1], coll) :
			tex->color[1]);
}
