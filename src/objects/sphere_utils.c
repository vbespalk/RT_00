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
	if ((*res)[0] > (*res)[1] || (*res)[0] < 0)
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

void		ft_collide_sphere(
				t_list **objs,
				t_object *obj,
				t_coll *coll,
				t_vector od[2])
{
	float		t1t2[2];
	int			i[2];
	t_sphere	*sph;
	t_vector	pos;
	t_vector	hit;

	sph = (t_sphere *)(obj->fig);
	pos = od[0] - sph->origin;
	if (!ft_solve_sqr_(
		ft_3_vector_dot(od[1], od[1]),
		2.0f * ft_3_vector_dot(od[1], pos),
		ft_3_vector_dot(pos, pos) - sph->radius * sph->radius,
		&t1t2)
		|| (t1t2[0] < 0 && t1t2[1] < 0))
		return ;
	i[0] = -1;
	while (++i[0] < 2)
	{
		if (t1t2[i[0]] > 0)
		{
			hit = od[0] + ft_3_vector_scale(od[1], t1t2[i[0]]);
			if (obj->is_neg)
				hit += ft_3_vector_scale(obj->ft_get_norm(obj->fig, hit), 0.1f);
			i[1] = ft_inside_type(objs, hit);
			if (i[1] < 0 || (obj->is_neg && i[1] == 0))
				t1t2[i[0]] = 0;
		}
	}
	if (t1t2[0] <= 0 && t1t2[1] <= 0)
		return ;
	hit = (t1t2[0] > 0)
		? od[0] + ft_3_vector_scale(od[1], t1t2[0])
		: od[0] + ft_3_vector_scale(od[1], t1t2[1]);
	if (obj->is_neg)
		hit += ft_3_vector_scale(obj->ft_get_norm(obj->fig, hit), 0.1f);
	coll->coll_pnt = hit;
	coll->norm = (obj->is_neg)
		? ft_3_vector_invert(obj->ft_get_norm(obj->fig, hit))
		: obj->ft_get_norm(obj->fig, hit);
	coll->o = (obj->is_neg)
		? ft_inside_obj(objs, hit, ft_get_inner_object)
		: obj;
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
