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

static  t_vector	ft_collide_cap(t_vector origin, t_vector direct, t_vector par_o, t_vector par_d)
{
	t_vector coll;

	coll = ft_3_line_plane_inter(par_o, par_d, origin, direct);
	return ((!ft_3_pointcmp(ft_3_unitvectornew(origin, coll), direct, 1e-6)) ?
			ft_3_nullpointnew() : coll);
}

int			ft_is_reachable_prbld(void *fig, t_vector origin, t_vector direct)
{
	t_prbld		*par;

	par = (t_prbld *)fig;
	return ((ft_3_vector_cos(direct, par->o - origin) > 0) ? 1 : 0);
	// return (1);
}

t_vector	ft_collide_prbld(t_list **objs, void *fig, t_vector o, t_vector d)
{
	t_prbld		*par;
	float		a;
	float		b;
	float		c;
	float		res[3];
	t_vector	coll;

	par = (t_prbld *)fig;
	a = ft_3_vector_dot(d, d) - \
		ft_3_vector_dot(d, par->d) * ft_3_vector_dot(d, par->d);
	b = 2.0f * (ft_3_vector_dot(d, o - par->o) - \
		ft_3_vector_dot(d, par->d) * (ft_3_vector_dot(o - par->o, par->d) + 2.f * par->r));
	c = ft_3_vector_dot(o - par->o, o - par->o) - \
		ft_3_vector_dot(o - par->o, par->d) * (ft_3_vector_dot(o - par->o, par->d) + 4.f * par->r);
	ft_solve_sqr(a, b, c, &res);
	if (!res[0] || (res[1] < FLT_MIN && res[2] < FLT_MIN))
		return (ft_3_nullpointnew());
	if (res[1] < FLT_MIN || res[1] > res[2])
		ft_swap_float(&res[1], &res[2]);
	coll = o + ft_3_vector_scale(d, res[1]);
	par->h = ft_3_vector_dot(coll - par->o, par->d);
	if (par->h > par->maxh)
	{
		if (res[2] > FLT_MIN)
		{
		coll = o + ft_3_vector_scale(d, res[2]);
		par->h = ft_3_vector_dot(coll - par->o, par->d);
		if (par->h > par->maxh)
			return(ft_3_nullpointnew());
		coll = ft_collide_cap(o, d, par->o + ft_3_vector_scale(par->d, par->maxh), par->d);
		}
	}
	return (par->h > par->maxh ? ft_3_nullpointnew() : coll);
}

int			ft_is_inside_prbld(void *fig, t_vector point)
{
	(void)fig;
	(void)point;
	return (0);
}

t_vector	ft_get_norm_prbld(void *fig, t_vector coll)
{
	t_prbld		*par;

	par = (t_prbld *)fig;
	if (fabs(ft_3_vector_dot(coll - (par->o + ft_3_vector_scale(par->d, par->maxh)), par->d)) <= 0.1)
		par->n = ft_3_tounitvector(par->d);
	else
		par->n = ft_3_tounitvector(coll - par->o - ft_3_vector_scale(par->d, par->h + par->r));
	return (par->n);
}
