/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:33:06 by vbespalk          #+#    #+#             */
/*   Updated: 2019/02/20 12:33:12 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			ft_is_reachable_sphere(void *fig, t_vector origin, t_vector direct)
{
	t_sphere	*sph;
	float		cos;

	sph = (t_sphere *)fig;
	if (ft_3_point_point_dist(origin, sph->origin) < sph->radius)
		return (1);
	if (ft_3_line_point_dist(origin, direct, sph->origin) > sph->radius)
		return (0);
	cos = ft_3_vector_cos(direct, sph->origin - origin);
	return ((cos > 0) ? 1 : 0);
}

t_vector	ft_collide_sphere(void *fig, t_vector origin, t_vector direct)
{
	t_sphere	*sph;
	float		res[3];
	t_vector	coll_points[2];

	sph = (t_sphere *)fig;
	ft_solve_sqr(
		(float)(pow(direct[0], 2) + pow(direct[1], 2) + pow(direct[2], 2)),
		2.0f * (direct[0] * (origin[0] - sph->origin[0]) +
			direct[1] * (origin[1] - sph->origin[1]) +
			direct[2] * (origin[2] - sph->origin[2])),
		(float)(pow(origin[0] - sph->origin[0], 2) +
			pow(origin[1] - sph->origin[1], 2) +
			pow(origin[2] - sph->origin[2], 2) - pow(sph->radius, 2)), &res);
	if (!res[0])
		return (ft_3_nullpointnew());
	coll_points[0] = (res[1] > 0) ?
		origin + ft_3_vector_scale(direct, res[1]) : ft_3_nullpointnew();
	coll_points[1] = (res[2] > 0) ?
		origin + ft_3_vector_scale(direct, res[2]) : ft_3_nullpointnew();
	coll_points[0] = (ft_3_isnullpoint(coll_points[0]) ||
		(res[1] > res[2] && res[2] > 0)) ? coll_points[1] : coll_points[0];
	return (coll_points[0]);
}

int			ft_is_inside_sphere(void *fig, t_vector point)
{
	t_sphere	*sph;

	sph = (t_sphere *)fig;
	return ((ft_3_point_point_dist(sph->origin, point) < sph->radius) ? 1 : 0);
}

t_vector	ft_get_norm_sphere(void *fig, t_vector coll)
{
	return (ft_3_unitvectornew(((t_sphere *)fig)->origin, coll));
}
