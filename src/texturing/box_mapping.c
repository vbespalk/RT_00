/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box_mapping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 15:48:07 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/16 15:48:13 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

Uint32		ft_map_box(t_object *o, void *tex, t_vector hit)
{
	(void)tex;
	(void)hit;
	return (o->color.val);
}

Uint32		ft_checker_box(t_object *o, void *tex, t_vector hit)
{
	t_checkbrd	*t;
	float		phi;
	float		theta;
	float		uv[2];

	(void)o;
	t = (t_checkbrd *)tex;
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
		return (t->noise[0] ? o->ft_procedural(o, t->noise[0], hit) :
				t->color[0]);
	return (t->noise[1] ? o->ft_procedural(o, t->noise[1], hit) :
			t->color[1]);
}

Uint32		ft_procedural_box(t_object *o, void *tex, t_vector hit)
{
	t_procedural	*t;

	(void)o;
	t = (t_procedural *)tex;
	return (t->ft_get_color(t, ft_3_vector_scale(hit, t->scale)));
}
