/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_mapping.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 18:00:00 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/10 18:00:16 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

Uint32		ft_map_plane(t_object *o, void *tex, t_vector hit)
{
	t_plane		*pln;
	SDL_Surface	*t;
	Uint32		col;
	int			xy[2];
	float		uv[2];

	pln = (t_plane *)o->fig;
	if (pln->len_wh[0] == FLT_MIN || pln->len_wh[1] == FLT_MIN)
		return (o->color.val);
	t = (SDL_Surface *)tex;
	uv[0] = 0.5f * ft_3_vector_dot(hit - (t_vector){-pln->ratio, 0, -1},
			X_AXIS);
	uv[1] = 1 - (ft_3_vector_dot(hit - (t_vector){-pln->ratio, 0, -1},
			Z_AXIS)) / (pln->ratio * 2);
	xy[0] = (int)((t->w - 1) * uv[0]);
	xy[1] = (int)((t->h - 1) * uv[1]);
	if (!(IN_RANGE(xy[0], 0, t->w) && IN_RANGE(xy[1], 0, t->h)))
		return (UINT32_MAX);
	ft_memcpy(&col, (Uint32 *)t->pixels + xy[1] * t->w + xy[0],
			sizeof(Uint32));
	return (col);
}

Uint32		ft_checker_pln(t_object *o, void *tex, t_vector coll)
{
	t_plane		*pln;
	t_checkbrd	*t;
	float		x;
	float		z;

	pln = (t_plane *)o->fig;
	t = (t_checkbrd *)tex;
	coll = pln->len_wh[0] == FLT_MIN ?
			ft_3_vector_scale(coll, 1.0f / o->dist) : coll;
	x = (sinf((float)M_PI * coll[0] * t->size));
	z = (sinf((float)M_PI * coll[2] * t->size));
	if ((x * z < 0))
		return (t->noise[0] ? o->ft_procedural(o, t->noise[0], coll) :
			t->color[0]);
		return (t->noise[1] ? o->ft_procedural(o, t->noise[1], coll) :
			t->color[1]);
}

Uint32		ft_procedural_pln(t_object *o, void *tex, t_vector coll)
{
	t_plane			*pln;
	t_procedural	*t;

	pln = (t_plane *)o->fig;
	t = (t_procedural *)tex;
	coll[0] = pln->len_wh[0] == FLT_MIN ? coll[0] : (coll[0] * pln->len_wh[0]) /
		pln->len_wh[1];
	return (t->ft_get_color(t, ft_3_vector_scale(coll, t->scale)));
}
