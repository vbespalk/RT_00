/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 15:36:36 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/23 15:36:38 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	check_intersection(
		t_list **objs, t_object *obj,
		t_vector *cucn, t_coll *coll)
{
	int i;

	i = 0;
	if (obj->is_neg)
		cucn[0] += ft_3_vector_scale(cucn[2], SHIFT);
	if (obj->react_neg || obj->is_neg)
		i = ft_inside_type(objs, cucn[0]);
	if (ft_is_invisible(obj, i))
		return (0);
	coll->coll_pnt = cucn[0];
	coll->ucoll_pnt = cucn[1];
	coll->norm = cucn[2];
	coll->tex_o = obj;
	return (1);
}

static int	get_intersections(
		double *res, const t_vector *untr_od,
		t_vector *od, t_object *obj)
{
	t_torus		*trs;
	double		doxr[4];
	double		abcde[5];
	int			num;

	trs = (t_torus *)obj->fig;
	od[0] = ft_3_pnt_transform(&(obj->inverse), untr_od[0]);
	od[1] = ft_3_vec_transform(&(obj->inverse), untr_od[1]);
	doxr[0] = ft_3_vector_dot(od[1], od[1]);
	doxr[1] = ft_3_vector_dot(od[0], od[0]) -
			(trs->r_inner2 + trs->r_outer2);
	doxr[2] = ft_3_vector_dot(od[0], od[1]);
	doxr[3] = 4 * trs->r_outer2;
	abcde[0] = doxr[0] * doxr[0];
	abcde[1] = 4 * doxr[0] * doxr[2];
	abcde[2] = 2 * doxr[0] * doxr[1] + 4 * doxr[2] * doxr[2] +
			doxr[3] * od[1][1] * od[1][1];
	abcde[3] = 4 * doxr[1] * doxr[2] + 2 * doxr[3] * od[0][1] * od[1][1];
	abcde[4] = doxr[1] * doxr[1] - 4 * trs->r_outer *
				trs->r_outer * (trs->r_inner2 - od[0][1] * od[0][1]);
	if ((num = ft_solve_quartic(abcde, res)) == 0)
		return (0);
	return (num);
}

float		ft_collide_torus(
		t_list **objs, struct s_object *obj,
		t_coll *coll, t_vector uod[2])
{
	double		res[4];
	t_vector	od[2];
	t_vector	cucn[3];
	int			i[3];
	double		t;

	if ((i[2] = get_intersections(res, uod, od, obj)) == 0)
		return (FLT_MAX);
	i[0] = -1;
	i[1] = 0;
	t = FLT_MAX;
	while (++i[0] < i[2])
	{
		if (res[i[0]] < t && res[i[0]] > 0)
		{
			cucn[1] = od[0] + ft_3_vector_scale(od[1], (float)res[i[0]]);
			cucn[2] = obj->ft_get_norm(obj->fig, &(obj->inverse), cucn[1]);
			cucn[0] = uod[0] + ft_3_vector_scale(uod[1], (float)res[i[0]]);
			if (!check_intersection(objs, obj, cucn, coll))
				continue ;
			t = res[i[0]];
		}
	}
	(t < FLT_MAX) ? ft_choose_object(objs, obj, coll) : 1;
	return ((float)t);
}

int			ft_is_inside_torus(t_object *o, t_vector point)
{
	t_torus		*trs;
	double		k;
	double		r[2];
	t_vector	a;

	trs = (t_torus *)o->fig;
	point = ft_3_pnt_transform(&(o->inverse), point);
	k = point[1];
	if (fabs(k) > trs->r_inner)
		return (0);
	a = (t_vector){point[0], FLT_MIN, point[2]};
	r[1] = ft_3_vector_dot(a, a);
	a = point - ft_3_vector_scale(ft_3_tounitvector(a), trs->r_outer);
	r[0] = ft_3_vector_dot(a, a);
	if (r[1] > trs->r_outer2 + trs->r_inner2 + 2 * trs->r_outer *
		trs->r_inner || r[0] > trs->r_inner2)
		return (0);
	return (1);
}

t_vector	ft_get_norm_torus(void *fig, t_matrix *inv_m, t_vector coll)
{
	t_torus		*trs;
	t_vector	norm;
	float		dot;
	float		r;

	trs = (t_torus *)fig;
	dot = ft_3_vector_dot(coll, coll);
	r = trs->r_outer2 + trs->r_inner2;
	norm = ZERO_PNT;
	norm[0] = 4.0 * coll[0] * (dot - r);
	norm[1] = 4.0 * coll[1] * (dot - r + 2.0 * trs->r_outer2);
	norm[2] = 4.0 * coll[2] * (dot - r);
	return (ft_3_tounitvector(ft_3_norm_transform(inv_m, norm)));
}
