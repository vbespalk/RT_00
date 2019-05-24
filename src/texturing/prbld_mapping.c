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

static Uint32	ft_map_caps(t_prbld *prbl, SDL_Surface *t,
		t_vector hit, float phi)
{
	Uint32		col;
	int			xy[2];
	float		texh;

	xy[0] = (int)((t->w - 1) * phi / 2.0f * (float)M_1_PI);
	texh = t->h * (1.f - prbl->ratio);
	hit = ft_3_vector_scale(hit, (1 / sqrtf(4.0f * prbl->maxh)));
	xy[1] = (int)((texh - 1) * (1.f - CLAMP(sqrtf(hit[0] * hit[0] +
			hit[2] * hit[2]), 0, 1)) + t->h * prbl->ratio);
	if (!(IN_RANGE(xy[0], 0, t->w - 1) && IN_RANGE(xy[1], 0, t->h - 1)))
		return (0xff);
	ft_memcpy(&col, (Uint32 *)t->pixels + xy[1] * t->w
					+ xy[0], sizeof(Uint32));
	return (col);
}

Uint32			ft_map_prbld(t_object *o, void *tex, t_vector hit)
{
	t_prbld		*prbl;
	SDL_Surface	*t;
	Uint32		col;
	float		phi;
	int			xy[2];

	prbl = ((t_prbld *)o->fig);
	if (((t_prbld *)o->fig)->maxh == FLT_MAX)
		return (o->color.val);
	t = (SDL_Surface *)tex;
	phi = atan2f(hit[0], hit[2]);
	if (!(IN_RANGE(phi, 0.0f, 2 * M_PI)))
		phi = phi < 0 ? phi + 2 * (float)M_PI : phi;
	if (IN_RANGE(hit[1], prbl->maxh - 1e-1, prbl->maxh + 1e-1))
		return (ft_map_caps(((t_prbld *)o->fig), tex, hit, phi));
	xy[0] = (int)((t->w - 1) * phi * 0.5f * (float)M_1_PI);
	xy[1] = (int)((t->h * prbl->ratio - 1) *
		CLAMP(sqrtf(hit[1] / prbl->maxh), 0, 1));
	if (!(IN_RANGE(xy[0], 0, t->w - 1) && IN_RANGE(xy[1], 0, t->h - 1)))
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
	t_prbld		*prb;
	t_checkbrd	*t;
	float		phi;

	prb = (t_prbld *)o->fig;
	t = (t_checkbrd *)tex;
	if (!(IN_RANGE((phi = atan2f(coll[2], coll[0])), 0.0f, 2.0f * M_PI)))
		phi = phi < 0.0f ? phi + 2 * (float)M_PI : phi - 2 * (float)M_PI;
	uv[0] = phi / (float)M_PI + 1;
	if (prb->maxh != FLT_MAX && IN_RANGE(coll[1], prb->maxh - 1e-1,
			prb->maxh + 1e-1))
		uv[1] = sqrtf(powf(coll[2] / sqrtf(4.0f * prb->maxh), 2) +
				powf(coll[0] / sqrtf(4.0f * prb->maxh), 2));
	else
		uv[1] = prb->maxh == FLT_MAX ? coll[1] / sqrtf(o->dist) :
				sqrtf(coll[1] / prb->maxh);
	if (!((fmodf(uv[0] * t->size, 1) > 0.5) ^
		(fmodf(uv[1] * t->size, 1) > 0.5)))
		return (t->noise[0] ? o->ft_procedural(o, t->noise[0], coll) :
			t->color[0]);
		return (t->noise[1] ? o->ft_procedural(o, t->noise[1], coll) :
			t->color[1]);
}
