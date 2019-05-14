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
