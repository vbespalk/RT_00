/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:33:06 by vbespalk          #+#    #+#             */
/*   Updated: 2019/02/20 12:33:12 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int			ft_solve_sqr_(float a, float b, float c, float (*res)[2])
{
	float	d;

	d = (float)pow(b, 2) - 4.0f * a * c;
	if (d < 0)
		return (0);
	d = sqrtf(d);
	(*res)[0] = (-b + d) / (2.0f * a);
	(*res)[1] = (-b - d) / (2.0f * a);
	if ((*res)[0] > (*res)[1] || (*res)[0] < FLT_MIN)
		ft_swap_float(&(*res)[0], &(*res)[1]);
	return (1);
}

static t_vector	get_closer_pnt(t_vector origin, t_vector *coll)
{
	float t[2];

	if (ft_3_isnullpoint(coll[0]))
		return (coll[1]);
	if (ft_3_isnullpoint(coll[1]))
		return (coll[0]);
	t[0] = ft_3_vector_len(coll[0] - origin);
	t[1] = ft_3_vector_len(coll[1] - origin);
	return (t[0] < t[1] ? coll[0] : coll[1]);
}

/*
** ADD 1e-1 TO t TO AVOID MISSES BETW SIDES AND CAPS
*/

static t_vector	get_cides_coll(t_vector origin, t_vector direct, float *t, t_cylinder *clnd)
{
	t_vector	coll[2];
	float 		m[2];

	coll[0] = origin + ft_3_vector_scale(direct, t[0]);
	m[0] = ft_3_vector_dot(clnd->v, coll[0] - clnd->o);
	coll[1] = origin + ft_3_vector_scale(direct, t[1]);
	m[1] = ft_3_vector_dot(clnd->v, coll[1] - clnd->o);
	if (clnd->maxh == FLT_MAX)
	{
		if (t[0] > FLT_MIN)
			return (coll[0]);
		else if (t[1] > FLT_MIN)
			return (coll[1]);
		return (ft_3_nullpointnew());
	}
	if (t[0] >= FLT_MIN && IN_RANGE(m[0], 0.0f, clnd->maxh))
		return (coll[0]);
	else if (t[1] >= FLT_MIN && IN_RANGE(m[1], 0.0f, clnd->maxh))
		return (coll[1]);
	return (ft_3_nullpointnew());
}

static t_vector	get_caps_coll(t_vector origin, t_vector direct, t_cylinder *clnd, float dot)
{
	float		t[2];
	t_vector	coll[2];
	t_vector 	o[2];

	o[0] = clnd->o;
	o[1] = clnd->o + ft_3_vector_scale(clnd->v, clnd->maxh);
	t[0] = (ft_3_vector_dot(o[0], -clnd->v) - ft_3_vector_dot(origin, -clnd->v)) * -dot;
	t[1] = (ft_3_vector_dot(o[1], clnd->v) - ft_3_vector_dot(origin, clnd->v)) * dot;
	if (t[0] < 1e-6 && t[1] < 1e-6)
		return (ft_3_nullpointnew());
	coll[0] = ft_3_nullpointnew();
	coll[1] = ft_3_nullpointnew();
	if (t[0] > FLT_MIN) {
		coll[0] = origin + ft_3_vector_scale(direct, t[0]);
		if (ft_3_vector_dot(coll[0] - o[0], coll[0] - o[0]) > clnd->r * clnd->r)
			coll[0] = ft_3_nullpointnew();
	}
	if (t[1] > FLT_MIN) {
		coll[1] = origin + ft_3_vector_scale(direct, t[1]);
		if (ft_3_vector_dot(coll[1] - o[1], coll[1]	- o[1]) > clnd->r * clnd->r)
			coll[1] = ft_3_nullpointnew();
	}
	if (t[0] < FLT_MIN)
		return (coll[1]);
	else if (t[1] < FLT_MIN)
		return (coll[0]);
	return (t[0] < t[1] && !ft_3_isnullpoint(coll[0]) ? coll[0] : coll[1]);
}

int					ft_is_reachable_cylinder(void *fig, t_vector origin, t_vector direct)
{
	return (1);
}

t_vector			ft_collide_cylinder(void *fig, t_vector origin, t_vector direct)
{
	t_cylinder	*clnd;
	t_vector	coll[2];
	float		res[2];
	float 		dot_dv;
	float 		dot_vx;

	clnd = (t_cylinder *)fig;
	dot_dv = ft_3_vector_dot(direct, clnd->v);
	dot_vx = ft_3_vector_dot(origin - clnd->o, clnd->v);
	if (!ft_solve_sqr_(ft_3_vector_dot(direct, direct) - dot_dv * dot_dv,
		2.0f * (ft_3_vector_dot(origin - clnd->o, direct) - dot_dv * dot_vx),
		ft_3_vector_dot(origin - clnd->o, origin - clnd->o) - dot_vx *
		dot_vx - clnd->r * clnd->r, &res))
		return (fabsf(dot_dv) < 1e-6 ? ft_3_nullpointnew() : \
			get_caps_coll(origin, direct, clnd, 1.0f / dot_dv));
	coll[0] = get_cides_coll(origin, direct, res, clnd);
	if (clnd->maxh == FLT_MAX || fabsf(dot_dv) < 1e-6)
		return (coll[0]);
	coll[1] = get_caps_coll(origin, direct, clnd, 1.0f / dot_dv);
	return (get_closer_pnt(origin, coll));
}

int			ft_is_inside_cylinder(void *fig, t_vector point)
{
	t_cylinder	*clnd;

	clnd = (t_cylinder *)fig;
	return ((ft_3_point_point_dist(clnd->o, point) < clnd->r) ? 1 : 0);
}

t_vector	ft_get_norm_cylinder(void *fig, t_vector coll)
{
	t_cylinder *clnd;
	float 		h;

	clnd = (t_cylinder *)fig;
	h = ft_3_vector_dot(clnd->v, coll - clnd->o);
	if (h >= clnd->maxh - 1e-2)
		return (clnd->v);
	if (h <= 1e-2)
		return (-clnd->v);
	return (ft_3_tounitvector(coll - ((t_cylinder *)fig)->o
	- ft_3_vector_scale(((t_cylinder *)fig)->v, h)));
}
