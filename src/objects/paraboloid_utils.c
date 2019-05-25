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

static float	get_closer_pnt(
					const double t[2], const t_vector hit[2],
					t_coll *coll, t_object *obj)
{
	if ((t[0] < t[1]) && t[0] != FLT_MAX)
	{
		coll->ucoll_pnt = hit[0];
		coll->norm = obj->ft_get_norm(obj->fig, &obj->inverse, hit[0]);
		return ((float)t[0]);
	}
	if (t[1] != FLT_MAX)
	{
		coll->ucoll_pnt = hit[1];
		coll->norm = ft_get_norm_plane(obj->fig, &(obj->inverse), hit[1]);
		return ((float)t[1]);
	}
	return (FLT_MAX);
}

static float	get_caps_coll(
					t_list **objs, t_vector od[2], t_vector uod[2],
					t_vector *coll, t_vector *norm, t_object *obj)
{
	int			i;
	float		t;
	t_vector 	hit;
	t_prbld		*par;

	i = 0;
	par = (t_prbld *)(obj->fig);
	od[0][1] -= par->maxh;
	t = (par->maxh == FLT_MAX) ? FLT_MAX : -(od[0][1]) / od[1][1];
	if (t <= 0 || t == FLT_MAX)
		return (FLT_MAX);
	*coll = od[0] + ft_3_vector_scale(od[1], t);
	if (ft_3_vector_dot(*coll, *coll) > 4.0f * par->maxh)
		return (FLT_MAX);
	hit = uod[0] + ft_3_vector_scale(uod[1], t);
	*norm = ft_get_norm_plane(obj->fig, &(obj->inverse), *coll);
	if (obj->is_neg)
		hit += ft_3_vector_scale(*norm, SHIFT);
	if (obj->react_neg || obj->is_neg)
		i = ft_inside_type(objs, hit);
	if (ft_is_invisible(obj, i))
		return (FLT_MAX);
	(*coll)[1] += par->maxh;
	return (t);
}

static double	get_cides_coll(
					t_list **objs, t_vector od[2], t_vector uod[2], double t[2],
					t_vector *coll, t_vector *norm, t_object *obj)
{
	int			i[2];
	t_vector 	hit[2];
	t_vector 	uhit[2];
	t_prbld		*par;

	par = (t_prbld *)(obj->fig);
	i[0] = -1;
	i[1] = 0;
	while (++i[0] < 2)
	{
		hit[i[0]] = od[0] + ft_3_vector_scale(od[1], (float)t[i[0]]);
		if (t[i[0]] >= 0 && IN_RANGE(hit[i[0]][1], 0, par->maxh))
		{
			uhit[i[0]] = uod[0] + ft_3_vector_scale(uod[1], (float)t[i[0]]);
			*norm = obj->ft_get_norm(obj->fig, &obj->inverse, hit[i[0]]);
			if (obj->is_neg)
				uhit[i[0]] += ft_3_vector_scale(*norm, SHIFT);
			if (obj->react_neg || obj->is_neg)
				i[1] = ft_inside_type(objs, uhit[i[0]]);
			if (ft_is_invisible(obj, i[1]))
				continue ;
			*coll = hit[i[0]];
			return (t[i[0]]);
		}
	}
	return (FLT_MAX);
}

float			ft_collide_prbld(
					t_list **objs, struct s_object *obj,
					t_coll *coll, t_vector untr_od[2])
{
	int			i;
	t_prbld		*par;
	t_vector	hit[2];
	t_vector	norm[2];
	double		res[2];
	t_vector	od[2];

	par = (t_prbld *)obj->fig;
	od[0] = ft_3_pnt_transform(&(obj->inverse), untr_od[0]);
	od[1] = ft_3_vec_transform(&(obj->inverse), untr_od[1]);
	if ((!ft_solve_sq(
		ft_3_vector_dot(od[1], od[1]) - od[1][1] * od[1][1],
		2.0f * (ft_3_vector_dot(od[1], od[0]) - od[1][1] * (od[0][1] + 2.f)),
		ft_3_vector_dot(od[0], od[0]) - od[0][1] * (od[0][1] + 4.f),
		res) || (res[0] <= 0 && res[1] <= 0))
		&& (IS_ZERO(od[1][1]) || par->maxh == FLT_MAX))
		return (FLT_MAX);
	res[0] = get_cides_coll(objs, od, untr_od, res, &hit[0], &norm[0], obj);
	res[1] = get_caps_coll(objs, od, untr_od, &hit[1], &norm[1], obj);
	if (res[0] == FLT_MAX && res[1] == FLT_MAX)
		return (FLT_MAX);
	i = (res[0] < res[1]) ? 0 : 1;
	coll->ucoll_pnt = hit[i];
	coll->coll_pnt = untr_od[0] + ft_3_vector_scale(untr_od[1], (float)res[i]);
	coll->norm = norm[i];
	coll->tex_o = obj;
	ft_choose_object(objs, obj, coll);
	return ((float)res[i]);
}

int			ft_is_inside_prbld(t_object *o, t_vector point)
{
	t_prbld		*par;
	t_vector	r;

	par = (t_prbld *)o->fig;
	point = ft_3_pnt_transform(&(o->inverse), point);
	if (!IN_RANGE(point[1], -SHIFT, par->maxh) && par->maxh != FLT_MAX)
		return (0);
	r = (t_vector){point[0], point[1] - 1, point[2]};
	return (ft_3_vector_dot(r, r) <= (point[1] + 1) * (point[1] + 1) ? 1 : 0);
}

t_vector	ft_get_norm_prbld(void *fig, t_matrix *inv_m, t_vector coll)
{
	(void)fig;
	return (ft_3_tounitvector(ft_3_norm_transform(inv_m,
		ft_3_tounitvector(coll - ((t_vector){0, coll[1] + 2, 0})))));
}

