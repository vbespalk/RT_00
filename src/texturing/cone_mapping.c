/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_mapping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 17:36:08 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/10 17:36:23 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static Uint32	ft_map_caps(t_cone *cone, SDL_Surface *tex,
		t_vector hit, float hei)
{
	return (UINT32_MAX);
}

Uint32			ft_map_cone(t_object *o, void *tex, t_vector hit)
{
	t_cone		*cone;
	SDL_Surface *t;
	Uint32		col;
	float		hei;
	float		phi;
	int			xy[2];

	cone = ((t_cone *)o->fig);
	if (((t_cone *)o->fig)->maxh == FLT_MAX)
		return (o->color.val);
	t = (SDL_Surface *)tex;
	hei = fabsf(cone->maxh) > fabsf(cone->minh) ?
		fabsf((hit[1]) / cone->maxh) : fabsf((hit[1]) / cone->minh);
	if (IN_RANGE(hit[1], -1e-1, 1e-1))
		return (ft_map_caps(((t_cone *)o->fig), t, hit, hei));
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

Uint32			ft_checker_cone(t_object *o, void *tex, t_vector coll)
{
	t_cone		*con;
	t_checkbrd	*t;
	float		uv[2];
	float		phi;
	float		r;

	con = (t_cone *)o->fig;
	t = (t_checkbrd *)tex;
	phi = atan2f(coll[2] / con->tan, coll[0] / con->tan);
	if (!(IN_RANGE(phi, 0.0f, 2.0f * M_PI)))
		phi = phi < 0.0f ? phi + 2 * (float)M_PI : phi - 2 * (float)M_PI;
	uv[0] = (phi / (float)M_PI + 1);
	r = con->r[0] < con->r[1] && con->r[1] != FLT_MIN ? con->r[1] : con->r[0];
	if (con->minh != -FLT_MAX || con->maxh != FLT_MAX)
	{
		if (IN_RANGE(coll[1], -1e-1, 1e-1))
			uv[1] = sqrtf(powf(coll[2] / r, 2) + powf(coll[0] / r, 2));
		else
			uv[1] = con->minh < con->maxh && con->maxh != FLT_MAX ?
				fabsf(coll[1] / con->maxh) : fabsf(coll[1] / con->minh);
	}
	else
		uv[1] = fabsf(coll[1] / o->dist);
	if (!((fmodf(uv[0] * t->size, 1) > 0.5) ^
		(fmodf(uv[1] * t->size, 1) > 0.5)))
		return (t->noise[0] ? o->ft_procedural(o, t->noise[0], coll) :
			t->color[0]);
		return (t->noise[1] ? o->ft_procedural(o, t->noise[1], coll) :
			t->color[1]);
}

Uint32			ft_procedural_cone(t_object *o,void *tex, t_vector coll)
{
	t_cone			*cone;
	t_vector		point;
	t_procedural	*t;
	float		r;

	cone = (t_cone *)o->fig;
	t = (t_procedural *)tex;
	r = cone->r[0] < cone->r[1] &&
		cone->r[1] != FLT_MIN ? cone->r[1] : cone->r[0];
	if ((cone->minh != -FLT_MAX || cone->maxh != FLT_MAX) &&
			IN_RANGE(coll[1], -1e-1, 1e-1))
		point = ft_3_vector_scale(coll, 1.f / r);
	else if (cone->minh == -FLT_MAX && cone->maxh == FLT_MAX)
	{
		point = ft_3_vector_scale(coll, 1 / (o->dist * 1.5f * cone->tan));
		point[1] = coll[1] / o->dist;
	}
	else
	{
		point = ft_3_vector_scale(coll, 1 / r);
		point[1] = coll[1] / (cone->minh < cone->maxh &&
				cone->minh > -FLT_MAX ? cone->maxh : cone->minh);
	}
	return (t->ft_get_color(t, NULL, ft_3_vector_scale(point, t->scale)));
}
