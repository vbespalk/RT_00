/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:33:06 by vbespalk          #+#    #+#             */
/*   Updated: 2019/02/20 12:33:12 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static float	get_closer_pnt(
					const float t[2], const t_vector hit[2],
					t_vector norms[2], t_coll *coll)
{
	if ((t[0] < t[1] || t[1] < 0) && t[0] > 0)
	{
		coll->ucoll_pnt = hit[0];
		coll->norm = norms[0];
		return (t[0]);
	}
	else if (t[1] > 0)
	{
		coll->ucoll_pnt = hit[1];
		coll->norm = norms[1];
		return (t[1]);
	}
	return (FLT_MAX);
}

static int		ft_handle_solve_qdr(
					t_object *obj, t_vector v[4][2], float res[2])
{
	t_cone		*con;

	con = (t_cone *)obj->fig;
	return (!ft_solve_qdr(
		ft_3_vector_dot(v[0][1], v[0][1]) - con->tan2 * v[0][1][1] * v[0][1][1],
		2.0f * (ft_3_vector_dot(v[0][0], v[0][1])
			- con->tan2 * v[0][1][1] * v[0][0][1]),
		ft_3_vector_dot(v[0][0], v[0][0]) - con->tan2 * v[0][0][1] * v[0][0][1],
		res)
		&& IS_ZERO(v[0][1][1]));
}

float			ft_collide_cone(
					t_list **objs, t_object *obj,
					t_coll *coll, t_vector untr_od[2])
{
	t_vector	v[4][2];
	float		res[2];
	float		t;

	v[0][0] = ft_3_pnt_transform(&(obj->inverse), untr_od[0]);
	v[0][1] = ft_3_vec_transform(&(obj->inverse), untr_od[1]);
	v[1][0] = untr_od[0];
	v[1][1] = untr_od[1];
	if (ft_handle_solve_qdr(obj, v, res))
		return (FLT_MAX);
	res[0] = (res[0] <= 0 && res[1] <= 0)
		? FLT_MAX : ft_get_cone_cides_coll(objs, v, res, obj);
	res[1] = ((((t_cone *)obj->fig)->maxh == FLT_MAX
		&& ((t_cone *)obj->fig)->minh == -FLT_MAX)
		|| fabsf(v[0][1][1]) < 1e-6)
			? FLT_MAX : ft_get_cone_caps_coll(objs, v, obj);
	if (res[0] == FLT_MAX && res[1] == FLT_MAX)
		return (FLT_MAX);
	t = get_closer_pnt(res, v[2], v[3], coll);
	coll->coll_pnt = untr_od[0] + ft_3_vector_scale(untr_od[1], t);
	if (obj->is_neg)
		coll->coll_pnt += ft_3_vector_scale(coll->norm, SHIFT);
	coll->tex_o = obj;
	ft_choose_object(objs, obj, coll);
	return (t);
}

int				ft_is_inside_cone(t_object *o, t_vector point)
{
	t_cone		*cone;
	t_vector	upoint;

	cone = (t_cone *)o->fig;
	upoint = ft_3_pnt_transform(&(o->inverse), point);
	if (!IN_RANGE(upoint[1], cone->minh, cone->maxh))
		return (0);
	return ((ft_3_vector_dot(upoint, upoint)
		< upoint[1] * upoint[1] + powf(upoint[1] * cone->tan, 2.0f)) ? 1 : 0);
}

t_vector		ft_get_norm_cone(void *fig, t_matrix *inv_m, t_vector coll)
{
	t_cone		*con;

	con = (t_cone *)fig;
	return (ft_3_tounitvector(
		ft_3_norm_transform(
			inv_m,
			coll - ft_3_vector_scale((t_vector){ 0, coll[1], 0 },
			powf(con->tan, 2.0f) + 1))));
}
