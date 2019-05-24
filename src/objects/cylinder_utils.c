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

float			get_closer_pnt(
		const float *t, const t_vector *hit,
		t_coll *coll, t_vector norms[2])
{
	if ((t[0] < t[1] || t[1] < 0) && t[0] > 0)
	{
		coll->ucoll_pnt = hit[0];
		coll->norm = norms[0];
		return (t[0]);
	}
	else
	{
		coll->ucoll_pnt = hit[1];
		coll->norm = norms[1];
		return (t[1]);
	}
}

static float	get_cides_coll(
		t_list **objs, t_vector od[2], t_vector uod[2],
		t_vector *coll, t_vector *norm, float t[2], t_object *obj)
{
	int			i[2];
	t_vector	hit[2];
	t_vector	uhit[2];
	t_cylinder	*clnd;

	clnd = (t_cylinder *)(obj->fig);
	i[0] = -1;
	while (++i[0] < 2)
	{
		hit[i[0]] = od[0] + ft_3_vector_scale(od[1], t[i[0]]);
		if (t[i[0]] >= 0
			&& IN_RANGE(hit[i[0]][1], -clnd->maxh, clnd->maxh))
		{
			uhit[i[0]] = uod[0] + ft_3_vector_scale(uod[1], t[i[0]]);
			*norm = obj->ft_get_norm(obj->fig, &(obj->inverse), hit[i[0]]);
			if (obj->is_neg)
				uhit[i[0]] += ft_3_vector_scale(*norm, SHIFT);
			if (obj->react_neg || obj->is_neg)
				i[1] = ft_inside_type(objs, uhit[i[0]]);
			(*norm)[3] = i[1];
			if (ft_is_invisible(obj, i[1]))
			{
				t[i[0]] = 0;
				continue ;
			}
			*coll = hit[i[0]];
			return (t[i[0]]);
		}
	}
	return (FLT_MAX);
}

static float	get_caps_coll(
		t_list **objs, t_vector od[2], t_vector uod[2],
		t_vector *coll_pnt, t_vector *norm, t_object *obj)
{
	int			i[2];
	t_cylinder	*clnd;
	t_vector	pnts[6];
	float 		t[2];

	clnd = (t_cylinder *)(obj->fig);
	pnts[0] = (t_vector){od[0][0], od[0][1] + clnd->maxh, od[0][2], clnd->maxh};
	pnts[1] = (t_vector){od[0][0], od[0][1] - clnd->maxh, od[0][2], -clnd->maxh};
	t[0] = -(pnts[0][1]) / od[1][1];
	t[1] = -(pnts[1][1]) / od[1][1];
	if (t[0] <= 0 && t[1] <= 0)
		return (FLT_MAX);
	if (t[0] > t[1] || t[0] < 0)
	{
		ft_swap_float(&t[0], &t[1]);
		ft_swap(&pnts[0], &pnts[1], sizeof(t_vector));
	}
	pnts[2] = pnts[0] + ft_3_vector_scale(od[1], t[0]);
	pnts[3] = pnts[1] + ft_3_vector_scale(od[1], t[1]);
	i[0] = -1;
	while (++i[0] < 2)
	{
		if (t[i[0]] >= 0 && ft_3_vector_dot(pnts[i[0] + 2], pnts[i[0] + 2]) < 1)
		{
			pnts[i[0] + 2] += (t_vector){ 0, pnts[i[0]][3], 0 };
			pnts[i[0] + 4] = uod[0] + ft_3_vector_scale(uod[1], t[i[0]]);
			*norm = ft_get_norm_plane(obj->fig, &(obj->inverse), pnts[i[0] + 2]);
			if (ft_3_vector_cos(*norm, pnts[i[0] + 4] - obj->translate) < 0)
				*norm = ft_3_vector_invert(*norm);
			if (obj->is_neg)
				pnts[i[0] + 4] += ft_3_vector_scale(*norm, SHIFT);
			if (obj->react_neg || obj->is_neg)
				i[1] = ft_inside_type(objs, pnts[i[0] + 4]);
			(*norm)[3] = i[1];
			if (ft_is_invisible(obj, i[1]))
			{
				t[i[0]] = 0;
				continue ;
			}
			*coll_pnt = pnts[i[0] + 2];
			return (t[i[0]]);
		}
	}
	return (FLT_MAX);
}

float			ft_collide_cylinder(
		t_list **objs, t_object *obj,
		t_coll *coll, t_vector untr_od[2])
{
	t_vector	hit[2];
	float		res[2];
	float		t;
	t_vector	od[2];
	t_vector	norms[2];

	od[0] = ft_3_pnt_transform(&(obj->inverse), untr_od[0]);
	od[1] = ft_3_vec_transform(&(obj->inverse), untr_od[1]);
	if (!ft_solve_qdr(od[1][0] * od[1][0] + od[1][2] * od[1][2],
			2.0f * (od[0][0] * od[1][0] + od[0][2] * od[1][2]),
			od[0][0] * od[0][0] + od[0][2] * od[0][2] - 1, res))
		return (FLT_MAX);
	res[0] = get_cides_coll(objs, od, untr_od, &hit[0], &norms[0], res, obj);
	res[1] = (((t_cylinder *)obj->fig)->maxh == FLT_MAX ||
			  fabsf(od[1][1]) < 1e-6) ? FLT_MAX :
			 get_caps_coll(objs, od, untr_od, &hit[1], &norms[1], obj);
	if (res[0] == FLT_MAX && res[1] == FLT_MAX)
		return (FLT_MAX);
	t = get_closer_pnt(res, hit, coll, norms);
	coll->coll_pnt = untr_od[0] + ft_3_vector_scale(untr_od[1], t);
	if (obj->is_neg)
		coll->coll_pnt += ft_3_vector_scale(coll->norm, SHIFT);
	ft_choose_object(objs, obj, coll);
	coll->tex_o = obj;
	return (t);
}

int				ft_is_inside_cylinder(t_object *o, t_vector point)
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
