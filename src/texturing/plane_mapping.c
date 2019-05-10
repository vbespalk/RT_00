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

Uint32		ft_map_plane(t_object *o, SDL_Surface *tex, t_vector hit)
{
	t_plane		*pln;
	Uint32		col;
	int			xy[2];
	float		uv[2];

	pln = (t_plane *)o->fig;
	if (pln->len_wh[0] == FLT_MIN || pln->len_wh[1] == FLT_MIN)
		return (o->color.val);
	uv[0] = 0.5f * ft_3_vector_dot(hit - (t_vector){-pln->ratio, 0, -1},
			X_AXIS);
	uv[1] = 1 - (ft_3_vector_dot(hit - (t_vector){-pln->ratio, 0, -1},
			Z_AXIS)) / (pln->ratio * 2);
	xy[0] = (int)((tex->w - 1) * uv[0]);
	xy[1] = (int)((tex->h - 1) * uv[1]);
	if (!(IN_RANGE(xy[0], 0, tex->w) && IN_RANGE(xy[1], 0, tex->h)))
		return (UINT32_MAX);
	ft_memcpy(&col, (Uint32 *)tex->pixels + xy[1] * tex->w + xy[0],
			sizeof(Uint32));
	return (col);
}

Uint32		ft_checker_pln(t_object *o, t_checkbrd *tex, t_vector coll)
{
	t_plane		*pln;
	float		x;
	float		z;

	pln = (t_plane *)o->fig;
	coll = pln->len_wh[0] == FLT_MIN ?
			ft_3_vector_scale(coll, 1.0f / o->dist) : coll;
	x = (sinf((float)M_PI * coll[0] * tex->size));
	z = (sinf((float)M_PI * coll[2] * tex->size));
	if ((x * z < 0))
		return (tex->noise[0] ? o->ft_procedural(o, tex->noise[0], coll) :
			tex->color[0]);
		return (tex->noise[1] ? o->ft_procedural(o, tex->noise[1], coll) :
			tex->color[1]);
}

Uint32		ft_procedural_pln(t_object *o, t_procedural *tex, t_vector coll)
{
	t_plane	*pln;

	pln = (t_plane *)o->fig;
	coll[0] = pln->len_wh[0] == FLT_MIN ? coll[0] : (coll[0] * pln->len_wh[0]) /
		pln->len_wh[1];
	return (tex->ft_get_color(tex, NULL, ft_3_vector_scale(coll, tex->scale)));
}

Uint32		ft_map_box(t_object *o, SDL_Surface *tex, t_vector hit)
{
	return (UINT32_MAX);
}

Uint32		ft_checker_box(t_object *o, t_checkbrd *tex, t_vector coll)
{
	return (UINT_MAX);
}
