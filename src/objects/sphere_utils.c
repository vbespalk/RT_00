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

t_vector	ft_collide_sphere(t_list **objs, t_object *obj, t_vector o, t_vector d)
{
	t_sphere	*sph;
	float		t1t2[2];
	t_vector	pos;
	t_vector	hit;


	sph = (t_sphere *)(obj->fig);
	pos = o - sph->origin;
	if (!ft_solve_sqr_(
		ft_3_vector_dot(d, d),
		2.0f * ft_3_vector_dot(d, pos),
		ft_3_vector_dot(pos, pos) - sph->radius * sph->radius,
		&t1t2)
		|| (t1t2[0] < FLT_MIN && t1t2[1] < FLT_MIN))
		return (ft_3_nullpointnew());
	if (t1t2[0] >= FLT_MIN)
	{
		hit = o + ft_3_vector_scale(d, t1t2[0]);
		if ((!(obj->is_neg) && ft_inside_what(objs, hit) < 0)
			|| (obj->is_neg && ft_inside_what(objs, hit) > 0))
	}
	return (t1t2[0] > FLT_MIN ? o + ft_3_vector_scale(d, t1t2[0]) :
		o + ft_3_vector_scale(d, t1t2[1]));

//	float		phi;
//	if (t1t2[0] > FLT_MIN)
//	{
//		hit = origin + direct * (t_vector){t1t2[0], t1t2[0], t1t2[0]} - sph->origin;
//		phi = atan2f(hit[0], hit[2]);
//		if (phi < 0.0)
//			phi += 2.0f * M_PI;
//		if ((phi >= sph->min_phi && phi <= sph->max_phi) &&
//			hit[1] <= sph->min_thcos * sph->radius &&
//			hit[1] >= sph->max_thcos * sph->radius) {
//			coll_pnt = origin + ft_3_vector_scale(direct, t1t2[0]);
//			return (coll_pnt);
//		}
//	}
//	if (t1t2[1] > FLT_MIN)
//	{
//		hit = origin + direct * (t_vector){t1t2[1], t1t2[1], t1t2[1]}  - sph->origin;
//		phi = atan2f(hit[0], hit[2]);
//		if (phi < 0.0)
//			phi += 2.0f * M_PI;
//		if ((phi >= sph->min_phi && phi <= sph->max_phi) &&
//			hit[1] <= sph->min_thcos * sph->radius &&
//			hit[1] >= sph->max_thcos * sph->radius) {
//			coll_pnt = origin + ft_3_vector_scale(direct, t1t2[1]);
//			return (coll_pnt);
//		}
//	}

}

int			ft_is_inside_sphere(void *fig, t_vector point)
{
	t_sphere	*sph;

	sph = (t_sphere *)fig;
	return ((ft_3_point_point_dist(sph->origin, point) < sph->radius) ? 1 : 0);
}

t_vector	ft_get_norm_sphere(void *fig, t_vector coll)
{
	return (ft_3_tounitvector(coll - ((t_sphere *)fig)->origin));
}
