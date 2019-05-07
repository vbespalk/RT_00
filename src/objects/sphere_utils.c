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
	if ((*res)[0] > (*res)[1] || (*res)[0] < 0)
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


float		ft_collide_sphere (t_list **objs, struct s_object *obj, t_coll *coll, t_vector untr_od[2])
{
	float		t1t2[2];
	int			i[2];
	t_vector	od[2];
	t_vector	hit[2];
	t_vector	uhit[2];
	t_vector	norm[2];

	od[0] = ft_3_pnt_transform(&(obj->inverse), untr_od[0]);
	od[1] = ft_3_vec_transform(&(obj->inverse), untr_od[1]);
	if (!ft_solve_sqr_(
			ft_3_vector_dot(od[1], od[1]),
			2.0f * ft_3_vector_dot(od[1], od[0]),
			ft_3_vector_dot(od[0], od[0]) - 1,
			&t1t2)
		|| (t1t2[0] <= 0 && t1t2[1] <= 0))
		return (FLT_MAX);
	i[0] = -1;
	while (++i[0] < 2)
	{
		if (t1t2[i[0]] > 0)
		{
			hit[i[0]] = untr_od[0] + ft_3_vector_scale(untr_od[1], t1t2[i[0]]);
			uhit[i[0]] = od[0] + ft_3_vector_scale(od[1], t1t2[i[0]]);
			norm[i[0]] = ft_3_tounitvector(
				ft_3_norm_transform(&(obj->inverse),
				obj->ft_get_norm(obj->fig, uhit[i[0]])));
			if (obj->is_neg)
				hit[i[0]] += ft_3_vector_scale(norm[i[0]], SHIFT);
			i[1] = ft_inside_type(objs, hit[i[0]]);
//			printf("norm: (%8.3f, %8.3f, %8.3f) -> (%8.3f, %8.3f, %8.3f)\n",
//				hit[i[0]][0], hit[i[0]][1], hit[i[0]][2],
//				norm[i[0]][0], norm[i[0]][1], norm[i[0]][2]);
//			if (obj->is_neg)
//				printf("inside type: %2d\n", i[1]);
			if (i[1] < 0 || (obj->is_neg && i[1] == 0))
				t1t2[i[0]] = 0;
		}
	}
	if (t1t2[0] <= 0 && t1t2[1] <= 0)
		return (FLT_MAX);
	i[0] = (t1t2[0] > 0) ? 0 : 1;
	coll->coll_pnt = hit[i[0]];
	coll->ucoll_pnt = uhit[i[0]];
	coll->norm = norm[i[0]];

//	printf("t: %f", t1t2[i[0]]);
//	printf("norm before invert: (%8.3f, %8.3f, %8.3f)\n",
//		   coll->norm[0], coll->norm[1], coll->norm[2]);
	if (obj->is_neg && i[1] != 1)
		coll->norm = ft_3_vector_invert(coll->norm);
//	printf("norm after invert: (%8.3f, %8.3f, %8.3f)\n",
//		   coll->norm[0], coll->norm[1], coll->norm[2]);

	if (obj->is_neg)
	{
		coll->o = ft_inside_obj(objs, coll->coll_pnt, ft_get_inner_object);
		coll->coll_pnt -= ft_3_vector_scale(norm[i[0]], SHIFT);
	}
	else
		coll->o = obj;

//	if (obj->is_neg)
//		printf("%s\n", (coll->o->is_neg) ? "in neg" : "in norm");

	coll->tex_o = coll->o;
	return (t1t2[i[0]]);
}

int			ft_is_inside_sphere(t_object *o, t_vector point)
{
	point = ft_3_pnt_transform(&(o->inverse), point);
	return ((ft_3_vector_len(point) < 1) ? 1 : 0);
}

t_vector	ft_get_norm_sphere(void *fig, t_vector coll)
{
//	return (ft_3_tounitvector(coll - ((t_sphere *)fig)->origin));
	return (ft_3_tounitvector(coll));

}
