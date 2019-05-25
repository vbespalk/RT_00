/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clndr_mapping.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 16:59:36 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/10 17:31:18 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static Uint32	ft_map_caps(t_cylinder *clnd, SDL_Surface *t,
		t_vector hit)
{
	Uint32		col;
	float		phi;
	int			xy[2];
	float		texh;

	phi = atan2f(hit[0], hit[2]);
	if (!(IN_RANGE(phi, 0.0f, 2.0f * M_PI)))
		phi = phi < 0.0f ? phi + 2 * (float)M_PI : phi - 2 * (float)M_PI;
	xy[0] = (int)((t->w - 1) * phi / 2.0f * (float)M_1_PI);
	texh = t->h * 0.5f * (1.f - clnd->ratio);
	if (hit[1] < 0)
		xy[1] = (int)((texh - 1) * CLAMP(sqrtf(hit[0] * hit[0] +
				hit[2] * hit[2]), 0, 1));
	else
		xy[1] = (int)((texh - 1) * (1 - CLAMP(sqrtf(hit[0] * hit[0] +
				hit[2] * hit[2]), 0, 1))
				+ (t->h - texh));
	if (!(IN_RANGE(xy[0], 0, t->w - 1) && IN_RANGE(xy[1], 0, t->h - 1)))
		return (0xff);
	ft_memcpy(&col, (Uint32 *)t->pixels + xy[1] * t->w
					+ xy[0], sizeof(Uint32));
	return (col);
}

Uint32			ft_map_clndr(t_object *o, void *tex, t_vector hit)
{
	Uint32		col;
	SDL_Surface	*t;
	float		phi;
	int			xy[2];
	t_cylinder	*clnd;

	clnd = ((t_cylinder *)o->fig);
	if (clnd->maxh == FLT_MAX)
		return (o->color.val);
	t = (SDL_Surface *)tex;
	if (!IN_RANGE(hit[1], -clnd->maxh + 1e-4, clnd->maxh - 1e-4))
		return (ft_map_caps(((t_cylinder *)o->fig), t, hit));
	phi = atan2f(hit[0], hit[2]);
	if (!(IN_RANGE(phi, 0.0f, 2 * M_PI)))
		phi = phi < 0 ? phi + 2 * (float)M_PI : phi;
	xy[0] = (int)((t->w - 1) * phi * 0.5f * (float)M_1_PI);
	xy[1] = (int)(((clnd->ratio * t->h - 1)) * (1.0f - ((hit[1] + clnd->maxh)
			* 0.5f) / clnd->maxh) + t->h * 0.5f * (1.f - clnd->ratio));
	if (!(IN_RANGE(xy[0], 0, t->w - 1) && IN_RANGE(xy[1], 0, t->h - 1)))
		return (0xff);
	ft_memcpy(&col, (Uint32 *)t->pixels + xy[1] * t->w
					+ xy[0], sizeof(Uint32));
	return (col);
}

Uint32			ft_checker_cyl(t_object *o, void *tex, t_vector coll)
{
	float		uv[2];
	t_cylinder	*clnd;
	t_checkbrd	*t;
	float		phi;

	clnd = (t_cylinder *)o->fig;
	t = (t_checkbrd *)tex;
	phi = atan2f(coll[2], coll[0]);
	if (!(IN_RANGE(phi, 0.0f, 2.0f * M_PI)))
		phi = phi < 0.0f ? phi + 2 * (float)M_PI : phi - 2 * (float)M_PI;
	uv[0] = (1 + phi / (float)M_PI);
	if (!IN_RANGE(coll[1], -clnd->maxh + 1e-4, clnd->maxh - 1e-4)
		&& clnd->maxh != FLT_MAX)
		uv[1] = sqrtf(coll[2] * coll[2] + coll[0] * coll[0]);
	else
		uv[1] = clnd->maxh == FLT_MAX ? (coll[1] + 100) * 0.3f :
			(coll[1] / clnd->maxh + 100) * 0.3f;
	if (!((fmodf(uv[0] * t->size, 1) > 0.5) ^
			(fmodf(uv[1] * t->size, 1) > 0.5)))
		return (t->noise[0] ? o->ft_procedural(o, t->noise[0], coll) :
			t->color[0]);
		return (t->noise[1] ? o->ft_procedural(o, t->noise[1], coll) :
			t->color[1]);
}

Uint32			ft_procedural_cyl(t_object *o, void *tex, t_vector coll)
{
	t_cylinder		*cyl;
	t_vector		point;
	t_procedural	*t;

	cyl = (t_cylinder *)o->fig;
	t = (t_procedural *)tex;
	point = coll;
	point[1] = cyl->maxh == FLT_MAX ? coll[1] : coll[1] / cyl->maxh;
	return (t->ft_get_color(tex, ft_3_vector_scale(point, t->scale)));
}
