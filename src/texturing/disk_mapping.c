/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk_mapping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 18:11:35 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/10 18:11:38 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

Uint32		ft_map_disk(t_object *o, void *tex, t_vector hit)
{
	Uint32		col;
	float		phi;
	int			xy[2];
	t_disk		*dsk;
	SDL_Surface	*t;

	dsk = (t_disk *)o->fig;
	if (dsk->out_r == FLT_MAX)
		return (o->color.val);
	t = (SDL_Surface *)tex;
	phi = atan2f(hit[2], hit[0]);
	if (!(IN_RANGE(phi, 0.0f, 2.0f * M_PI)))
		phi = phi < 0.0f ? phi + 2 * (float)M_PI : phi - 2 * (float)M_PI;
	hit = ft_3_vector_scale(hit, 1 / dsk->out_r);
	xy[0] = (int)((t->w - 1) * phi / 2.0f * (float)M_1_PI);
	xy[1] = (int)((t->h - 1) * CLAMP(sqrtf(hit[0] * hit[0] + hit[2] * hit[2]), 0, 1));
	if (!(IN_RANGE(xy[0], 0, t->w) &&
		  IN_RANGE(xy[1], 0, t->h)))
		return (0xff);
	ft_memcpy(&col, (Uint32 *)t->pixels + xy[1] * t->w
					+ xy[0], sizeof(Uint32));
	return (col);
}

Uint32		ft_procedural_dsk(t_object *o, void *tex, t_vector coll)
{
	t_procedural *t;

	t = (t_procedural *)tex;
	coll = ((t_disk *)o->fig)->out_r == FLT_MAX ?
			ft_3_vector_scale(coll, 1.0f / o->dist) :
			ft_3_vector_scale(coll, 1.0f / ((t_disk *)o->fig)->out_r);
	return (t->ft_get_color(t, ft_3_vector_scale(coll, t->scale)));
}

Uint32		ft_checker_dsk(t_object *o, void *tex, t_vector coll)
{
	t_disk		*dsk;
	t_checkbrd	*t;
	float		uv[2];
	t_vector	pnt;

	dsk = (t_disk *)o->fig;
	t = (t_checkbrd *)tex;
	pnt = coll;
	coll = dsk->out_r == FLT_MAX ? ft_3_vector_scale(coll, 1.0f / o->dist) :
		ft_3_vector_scale(coll, 1.0f / (dsk->out_r));
	uv[0] = (atan2f(coll[2], coll[0]) * M_1_PI + 1);
	uv[1] = sqrtf(coll[2] * coll[2] + coll[0] * coll[0]);
	if (!((fmodf(uv[0] * t->size, 1) > 0.5) ^
		(fmodf(uv[1] * t->size, 1) > 0.5)))
		return (t->noise[0] ? o->ft_procedural(o, t->noise[0], pnt) :
			t->color[0]);
		return (t->noise[1] ? o->ft_procedural(o, t->noise[1], pnt) :
			t->color[1]);
}
