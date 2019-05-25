/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 19:13:18 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/22 19:13:20 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float		ft_collide_cylinder(
				t_list **objs, t_object *obj, t_coll *coll, t_vector untr_od[2])
{
	float		res[2];
	float		t;
	t_vector	v[4][2];

	v[0][0] = ft_3_pnt_transform(&(obj->inverse), untr_od[0]);
	v[0][1] = ft_3_vec_transform(&(obj->inverse), untr_od[1]);
	v[1][0] = untr_od[0];
	v[1][1] = untr_od[1];
	if (!ft_solve_qdr(v[0][1][0] * v[0][1][0] + v[0][1][2] * v[0][1][2],
		2.0f * (v[0][0][0] * v[0][1][0] + v[0][0][2] * v[0][1][2]),
		v[0][0][0] * v[0][0][0] + v[0][0][2] * v[0][0][2] - 1, res))
		return (FLT_MAX);
	res[0] = ft_get_clnd_cides_coll(objs, v, res, obj);
	res[1] = (((t_cylinder *)obj->fig)->maxh == FLT_MAX
		|| fabsf(v[0][1][1]) < 1e-6) ? FLT_MAX
		: ft_get_clnd_caps_coll(objs, v, obj);
	if (res[0] == FLT_MAX && res[1] == FLT_MAX)
		return (FLT_MAX);
	t = ft_get_clnd_closer_pnt(res, v[2], coll, v[3]);
	coll->coll_pnt = untr_od[0] + ft_3_vector_scale(untr_od[1], t);
	if (obj->is_neg)
		coll->coll_pnt += ft_3_vector_scale(coll->norm, SHIFT);
	coll->tex_o = obj;
	t < FLT_MAX ? ft_choose_object(objs, obj, coll) : 1;
	return (t);
}

int			ft_is_inside_cylinder(t_object *o, t_vector point)
{
	float maxh;

	maxh = ((t_cylinder *)o->fig)->maxh;
	point = ft_3_pnt_transform(&(o->inverse), point);
	if (!IN_RANGE(point[1], -maxh, maxh) && maxh != FLT_MAX)
		return (0);
	return (ft_3_vector_dot((t_vector){point[0], 0, point[2]},
				(t_vector){point[0], 0, point[2]}) <= 1 ? 1 : 0);
}

t_vector	ft_get_norm_cylinder(void *fig, t_matrix *inv_m, t_vector coll)
{
	(void)fig;
	return (ft_3_tounitvector(ft_3_norm_transform(
			inv_m, (coll - (t_vector){0, coll[1], 0}))));
}
