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

Uint32			ft_map_prbld(t_object *o, void *tex, t_vector hit)
{
	t_prbld		*prbl;
	SDL_Surface	*t;
	Uint32		col;
	float		hei;
	float		phi;
	int			xy[2];

	prbl = ((t_prbld *)o->fig);
	if (((t_prbld *)o->fig)->maxh == FLT_MAX)
		return (o->color.val);
	t = (SDL_Surface *)tex;
	hei = sqrtf(hit[1] / prbl->maxh);
	if (IN_RANGE(hit[1], -1e-6, 1e-6))
		return (ft_map_caps(((t_prbld *)o->fig), tex, hit, hei));
	phi = atan2f(hit[0], hit[2]);
	if (!(IN_RANGE(phi, 0.0f, 2 * M_PI)))
		phi = phi < 0 ? phi + 2 * (float)M_PI : phi;
	xy[0] = (int)((t->w - 1) * phi * 0.5f * (float)M_1_PI);
	xy[1] = (int)((t->h - 1) * hei);
	if (!(IN_RANGE(xy[0], 0, t->w) && IN_RANGE(xy[1], 0, t->h)))
		return (0xff);
	ft_memcpy(&col, (Uint32 *)t->pixels + xy[1] * t->w
					+ xy[0], sizeof(Uint32));
	return (col);
}

Uint32			ft_procedural_prbld(t_object *o, void *tex, t_vector coll)
{
	t_prbld			*prbl;
	t_procedural	*t;
	t_vector		point;

	prbl = (t_prbld *)o->fig;
	t = (t_procedural *)tex;
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
	return (t->ft_get_color(t, ft_3_vector_scale(point, t->scale)));
}

Uint32			ft_checker_prbld(t_object *o, void *tex, t_vector coll)
{
	float		uv[2];
	t_prbld		*prbl;
	t_checkbrd	*t;
	float		phi;
	t_vector	pnt;

	prbl = (t_prbld *)o->fig;
	t = (t_checkbrd *)tex;
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
	if (!((fmodf(uv[0] * t->size, 1) > 0.5) ^
		(fmodf(uv[1] * t->size, 1) > 0.5)))
		return (t->noise[0] ? o->ft_procedural(o, t->noise[0], coll) :
			t->color[0]);
		return (t->noise[1] ? o->ft_procedural(o, t->noise[1], coll) :
			t->color[1]);
}
