/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paraboloid_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 18:12:51 by vbespalk          #+#    #+#             */
/*   Updated: 2019/02/19 18:12:54 by vbespalk         ###   ########.fr       */
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

static t_vector	get_caps_coll(t_vector origin, t_vector direct, t_prbld *par, float dot)
{
	float		t;
	t_vector	coll;
	t_vector 	o;

	o = par->o + ft_3_vector_scale(par->v, par->maxh);
	t = (ft_3_vector_dot(o - origin, par->v)) * dot;
	if (t < FLT_MIN)
		return (ft_3_nullpointnew());
	coll = origin + ft_3_vector_scale(direct, t);
	if (ft_3_vector_dot(coll - o, coll - o) > 4.0f * par->r * par->maxh)
		return (ft_3_nullpointnew());
	return (coll);
}

int			ft_is_reachable_prbld(void *fig, t_vector origin, t_vector direct)
{
	(void)origin;
	(void)direct;
	(void)fig;
	return (1);
}

static t_vector	get_cides_coll(t_vector origin, t_vector direct, float *t, t_prbld *par)
{
	t_vector	coll[2];
	float 		m[2];

	coll[0] = origin + ft_3_vector_scale(direct, t[0]);
	m[0] = ft_3_vector_dot(par->v, coll[0] - par->o);
	coll[1] = origin + ft_3_vector_scale(direct, t[1]);
	m[1] = ft_3_vector_dot(par->v, coll[1] - par->o);
	if (par->maxh == FLT_MAX)
	{
		if (t[0] >= FLT_MIN)
			return (coll[0]);
		else if (t[1] >= FLT_MIN)
			return (coll[1]);
		return (ft_3_nullpointnew());
	}
	if (t[0] >= FLT_MIN && IN_RANGE(m[0], FLT_MIN, par->maxh))
		return (coll[0]);
	else if (t[1] >= FLT_MIN && IN_RANGE(m[1], FLT_MIN, par->maxh))
		return (coll[1]);
	return (ft_3_nullpointnew());
}

t_vector	ft_collide_prbld(t_list **objs, void *fig, t_vector o, t_vector d)
{
	t_prbld		*par;
	t_vector	coll[2];
	float		res[2];
	float 		dot_dv;
	float 		dot_vx;

	par = (t_prbld *)fig;
	dot_dv = ft_3_vector_dot(d, par->v);
	dot_vx = ft_3_vector_dot(o - par->o, par->v);
	if (!ft_solve_sqr_(ft_3_vector_dot(d, d) - dot_dv * dot_dv,
		2.0f * (ft_3_vector_dot(d, o - par->o) - dot_dv * (dot_vx + 2.f * par->r)),
		ft_3_vector_dot(o - par->o, o - par->o) - dot_vx * (dot_vx + 4.f * par->r),
		&res) || (res[0] < FLT_MIN && res[1] < FLT_MIN))
		return (ft_3_nullpointnew());
	coll[0] = get_cides_coll(o, d, res, par);
	if (par->maxh == FLT_MAX || fabsf(dot_dv) < 1e-6)
		return (coll[0]);
	coll[1] = get_caps_coll(o, d, par, 1.0f / dot_dv);
	return (get_closer_pnt(o, coll));
}

int			ft_is_inside_prbld(void *fig, t_vector point)
{
	t_prbld		*par;
	float 		hei;
	t_vector	rad;

	par = (t_prbld *)fig;
	hei = ft_3_vector_dot(par->v, point - par->o);
	if (!IN_RANGE(hei, -(1e-1), par->maxh) && par->maxh != FLT_MAX)
	{
		printf("HOORAY! OUTSIDE %f max %f\n", hei, par->maxh);
		return (0);
	}
	rad = point - (par->o + ft_3_vector_scale(par->v, par->r));
	printf("rad %f, dot %f\n", sqrtf(ft_3_vector_dot(rad, rad)), ft_3_vector_dot(point -
	(par->o - ft_3_vector_scale(par->v, par->r)), par->v));
	if (sqrtf(ft_3_vector_dot(rad, rad)) <= ft_3_vector_dot(point -
	(par->o - ft_3_vector_scale(par->v, par->r)), par->v))
	{
		printf("INSIDE\n");
		return (1);
	}
	printf("OUTSIDE\n");
	return (0);
}

t_vector	ft_get_norm_prbld(void *fig, t_vector coll)
{
	t_prbld		*par;
	float 		h;

	par = (t_prbld *)fig;
	h = ft_3_vector_dot(par->v, coll - par->o);
	if (h >= par->maxh - 1e-2)
		return(ft_3_tounitvector(par->v));
	else
		return (ft_3_tounitvector(coll - (par->o + ft_3_vector_scale(par->v, h + par->r))));
}
