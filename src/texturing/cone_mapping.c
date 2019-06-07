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

static Uint32	ft_map_caps(t_cone *cone, SDL_Surface *t,
		t_vector hit, float phi)
{
	Uint32		col;
	int			xy[2];
	float		texh[2];

	xy[0] = (int)((t->w - 1) * phi / 2.0f * (float)M_1_PI);
	texh[0] = t->h * cone->r[0] / cone->texh;
	texh[1] = t->h * cone->r[1] / cone->texh;
	if (IN_RANGE(hit[1], cone->minh - 1e-1, cone->minh + 1e-1))
	{
		hit = (t_vector){hit[0] / cone->r[0], hit[1], hit[2] / cone->r[0]};
		xy[1] = (int)((texh[0] - 1) * (1 - CLAMP(sqrtf(hit[0] * hit[0] +
				hit[2] * hit[2]), 0, 1)) + t->h - texh[0]);
	}
	else
	{
		hit = (t_vector){hit[0] / cone->r[1], hit[1], hit[2] / cone->r[1]};
		xy[1] = (int)((texh[1] - 1) * CLAMP(sqrtf(hit[0] * hit[0] +
				hit[2] * hit[2]), 0, 1));
	}
	if (!(IN_RANGE(xy[0], 0, t->w - 1) && IN_RANGE(xy[1], 0, t->h - 1)))
		return (0xff);
	ft_memcpy(&col, (Uint32 *)t->pixels + xy[1] * t->w
					+ xy[0], sizeof(Uint32));
	return (col);
}

/*
** rtph[2] for phi angle;
** rtph[0 - 1] for texture parts (sides, caps)
*/

Uint32			ft_map_cone(t_object *o, void *tex, t_vector hit)
{
	t_cone		*cone;
	SDL_Surface *t;
	Uint32		col;
	int			xy[2];
	float		rtph[3];

	cone = ((t_cone *)o->fig);
	if (cone->maxh == FLT_MAX || cone->minh == -FLT_MAX)
		return (o->color.val);
	t = (SDL_Surface *)tex;
	if (!(IN_RANGE((rtph[2] = atan2f(hit[0], hit[2])), 0.0f, 2 * M_PI)))
		rtph[2] = rtph[2] < 0 ? rtph[2] + 2 * (float)M_PI : rtph[2];
	if (!IN_RANGE(hit[1], cone->minh + 1e-1, cone->maxh - 1e-1))
		return (ft_map_caps(((t_cone *)o->fig), t, hit, rtph[2]));
	rtph[0] = t->h * (1.f - (cone->r[0] + cone->r[1]) / cone->texh);
	rtph[1] = t->h * (cone->r[1] / cone->texh);
	xy[0] = (int)((t->w - 1) * rtph[2] * 0.5f * (float)M_1_PI);
	xy[1] = (int)((rtph[0] - 1) * (fabsf((hit[1] - cone->maxh) /
			(cone->maxh - cone->minh))) + rtph[1]);
	if (!(IN_RANGE(xy[0], 0, t->w - 1) && IN_RANGE(xy[1], 0, t->h - 1)))
		return (0xff);
	ft_memcpy(&col, (Uint32 *)t->pixels + xy[1] * t->w
					+ xy[0], sizeof(Uint32));
	return (col);
}

Uint32			ft_checker_cone(t_object *o, void *tex, t_vector coll)
{
	t_cone		*cn;
	t_checkbrd	*t;
	float		uv[2];
	float		phi;
	float		r;

	cn = (t_cone *)o->fig;
	t = (t_checkbrd *)tex;
	if (!(IN_RANGE((phi = atan2f(coll[2], coll[0])), 0.0f, 2.0f * M_PI)))
		phi = phi < 0.0f ? phi + 2 * (float)M_PI : phi - 2 * (float)M_PI;
	uv[0] = (phi / (float)M_PI + 1);
	r = cn->r[0] < cn->r[1] && cn->r[1] != FLT_MIN ? cn->r[1] : cn->r[0];
	if (!IN_RANGE(coll[1], cn->minh + 1e-1, cn->maxh - 1e-1) &&
		!(cn->minh == -FLT_MAX && cn->maxh == FLT_MAX))
		uv[1] = sqrtf(powf(coll[2] / r, 2) + powf(coll[0] / r, 2));
	else
		uv[1] = (cn->minh != -FLT_MAX && cn->maxh != FLT_MAX) ?
			fabsf(coll[1] / (cn->maxh - cn->minh)) : fabsf(coll[1] / o->dist);
	if (!((fmodf(uv[0] * t->size, 1) > 0.5) ^
		(fmodf(uv[1] * t->size, 1) > 0.5)))
		return (t->noise[0] ? o->ft_procedural(o, t->noise[0], coll) :
			t->color[0]);
	return (t->noise[1] ? o->ft_procedural(o, t->noise[1], coll) :
			t->color[1]);
}

Uint32			ft_procedural_cone(t_object *o, void *tex, t_vector coll)
{
	t_cone			*cone;
	t_vector		point;
	t_procedural	*t;
	float			r;

	cone = (t_cone *)o->fig;
	t = (t_procedural *)tex;
	if (cone->minh == -FLT_MAX || cone->maxh == FLT_MAX)
	{
		point = ft_3_vector_scale(coll, 1 / (o->dist * 1.5f * cone->tan));
		point[1] = coll[1] / o->dist;
	}
	else
	{
		r = cone->r[0] < cone->r[1] &&
			cone->r[1] != FLT_MIN ? cone->r[1] : cone->r[0];
		point = ft_3_vector_scale(coll, 1 / r);
		point[1] = coll[1] / fabsf(cone->maxh - cone->minh);
	}
	return (t->ft_get_color(t, ft_3_vector_scale(point, t->scale)));
}
