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

	(*res)[0] = 0;
	(*res)[1] = 0;
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

//	sph = (t_sphere *)fig;
//	if (ft_3_point_point_dist(origin, sph->origin) < sph->radius)
//		return (1);
//	if (ft_3_line_point_dist(origin, direct, sph->origin) > sph->radius)
//		return (0);
//	cos = ft_3_vector_dot(direct, sph->origin - origin);
//	return ((cos > 0) ? 1 : 0);
	return (1);
}

float	ft_collide_sphere (t_list **objs, struct s_object *obj, t_coll *coll, t_vector untr_od[2])
{
	t_sphere	*sph;
	float		t1t2[2];
	t_vector	od[2];

	sph = (t_sphere *)obj;
	od[0] = ft_3_pnt_transform(&(obj->inverse), untr_od[0]);
	od[1] = ft_3_vec_transform(&(obj->inverse), untr_od[1]);
	if (!ft_solve_sqr_(ft_3_vector_dot(od[1], od[1]),
		2.0f * ft_3_vector_dot(od[1], od[0]),
		ft_3_vector_dot(od[0], od[0]) - 1, &t1t2)
		|| (t1t2[0] < FLT_MIN && t1t2[1] < FLT_MIN))
		return (-1);
	coll->ucoll_pnt = t1t2[0] > FLT_MIN ? od[0] + ft_3_vector_scale(od[1], t1t2[0]) :
					  od[0] + ft_3_vector_scale(od[1], t1t2[1]);
	coll->norm = ft_3_tounitvector(ft_3_norm_transform(&(obj->inverse),
			obj->ft_get_norm((void *)sph, coll->ucoll_pnt)));
	coll->o = obj;
	coll->tex_o = obj;
	return (t1t2[0] > FLT_MIN ? t1t2[0] : t1t2[1]);
}

int			ft_is_inside_sphere(t_object *o, t_vector point)
{
	point = ft_3_pnt_transform(&(o->inverse), point);
	return ((ft_3_point_point_dist(((t_sphere *)o->fig)->origin, point) < 1) ? 1 : 0);
}

t_vector	ft_get_norm_sphere(void *fig, t_vector coll)
{
//	return (ft_3_tounitvector(coll - ((t_sphere *)fig)->origin));
	return (ft_3_tounitvector(coll));

}
