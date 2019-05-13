/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_mapping.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 19:30:16 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/12 19:30:19 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

Uint32		ft_map_sphere(t_object *o, void *tex, t_vector hit)
{
	Uint32		col;
	float		theta;
	float		phi;
	int			xy[2];
	SDL_Surface	*t;

	t = (SDL_Surface *)tex;
	hit = ft_3_vector_rotate(hit, 0, ((t_sphere *)o->fig)->phi,
							 ((t_sphere *)o->fig)->theta);
	phi = atan2f(hit[2], hit[0]);
	if (!(IN_RANGE(phi, 0.0f, 2.0f * M_PI)))
		phi = phi < 0.0f ? phi + 2 * (float)M_PI : phi - 2 * (float)M_PI;
	theta = acosf(CLAMP(hit[1], -1.0f, 1.0f));
	if (!(IN_RANGE(theta, 0.0f, M_PI)))
		theta = theta < 0.0f ? theta + (float)M_PI : theta - (float)M_PI;
	xy[0] = (int)((t->w - 1) * phi / 2.0f * (float)M_1_PI);
	xy[1] = (int)((t->h - 1) * theta * (float)M_1_PI);
	if (!(IN_RANGE(xy[0], 0, t->w) &&
		IN_RANGE(xy[1], 0, t->h)))
		return (0xff);
	ft_memcpy(&col, (Uint32 *)t->pixels + xy[1] * t->w
			+ xy[0], sizeof(Uint32));
	return (col);
}

Uint32		ft_checker_sph(t_object *o, void *tex, t_vector coll)
{
	float		uv[2];
	t_checkbrd	*t;
	float		theta;
	float		phi;
	t_vector	hit;

	t = (t_checkbrd *)tex;
	hit = ft_3_vector_rotate(coll, 0, ((t_sphere *)o->fig)->phi,
			((t_sphere *)o->fig)->theta);
	phi = atan2f(hit[2], hit[0]);
	if (!(IN_RANGE(phi, 0.0f, 2.0f * M_PI)))
		phi = phi < 0.0f ? phi + 2 * (float)M_PI : phi - 2 * (float)M_PI;
	theta = acosf(hit[1]);
	if (!(IN_RANGE(theta, 0.0f, M_PI)))
		theta = theta < 0.0f ? theta + (float)M_PI : theta - (float)M_PI;
	uv[0] = (1 + phi / (float)M_PI);
	uv[1] = theta / (float)M_PI;
	if ((fmodf(uv[0] * t->size, 1) > 0.5f) ^
		(fmodf(uv[1] * t->size, 1) > 0.5f))
		return (t->noise[0] ? o->ft_procedural(o, t->noise[0], coll) :
			t->color[0]);
		return (t->noise[1] ? o->ft_procedural(o, t->noise[1], coll) :
			t->color[1]);
}

Uint32		ft_procedural_sph(t_object *o, void *tex, t_vector coll)
{
	t_procedural *t;

	t = (t_procedural *)tex;
	coll = ft_3_vector_rotate(coll, 0, ((t_sphere *)o->fig)->phi,
							 ((t_sphere *)o->fig)->theta);
	return (t->ft_get_color(t, NULL, ft_3_vector_scale(coll, t->scale)));
}
