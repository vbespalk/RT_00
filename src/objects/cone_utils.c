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

static int			ft_solve_sqr_(float a, float b, float c, float (*res)[2])
{
	float	d;

	d = (float)pow(b, 2) - 4.0f * a * c;
	if (d < 0)
		return (0);
	d = sqrtf(d);
	(*res)[0] = (-b + d) / (2.0f * a);
	(*res)[1] = (-b - d) / (2.0f * a);
	if (((*res)[0] > (*res)[1] && (*res)[1] > FLT_MIN) || (*res)[0] < FLT_MIN)
		ft_swap_float(&(*res)[0], &(*res)[1]);
	return (1);
}

static float	get_closer_pnt(
					const float t[2], const t_vector hit[2], t_vector norms[2],
					t_coll *coll, t_object *obj)
{
	coll->o = obj;
	coll->tex_o = obj;
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

static float	get_cides_coll(
					t_list **objs, t_vector od[2], t_vector uod[2],
					t_vector *coll, t_vector *norm, float t[2], t_object *obj)
{
	int			i[2];
	t_vector	hit[2];
	t_vector	uhit[2];
	t_cone		*cone;

	cone = (t_cone *)(obj->fig);
	hit[0] = od[0] + ft_3_vector_scale(od[1], t[0]);
	if (cone->maxh == FLT_MAX && cone->minh == FLT_MIN)
	{
		*coll = hit[0];
		return (t[0]);
	}
	hit[1] = od[0] + ft_3_vector_scale(od[1], t[1]);
	i[0] = -1;
	while (++i[0] < 2)
	{
		if (t[i[0]] >= FLT_MIN
			&& IN_RANGE(hit[i[0]][1], cone->minh, cone->maxh))
		{
			uhit[i[0]] = uod[0] + ft_3_vector_scale(uod[1], t[i[0]]);
			*norm = ft_3_tounitvector(
				ft_3_norm_transform(
					&(obj->inverse),
					hit[i[0]] - ft_3_vector_scale(
						(t_vector){ 0, hit[i[0]][1], 0 },
						powf(cone->tan, 2.0f) + 1)));
			if (obj->is_neg)
				uhit[i[0]] += ft_3_vector_scale(*norm, SHIFT);
			i[1] = ft_inside_type(objs, uhit[i[0]]);
			(*norm)[3] = i[1];
			if (obj->is_neg && i[1] != 1)
				*norm = ft_3_vector_invert(*norm);
			if (i[1] < 0 || (obj->is_neg && i[1] == 0))
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
	t_cone		*cone;
	t_vector	pnts[6];
	float 		t[2];
	float 		sq_r[2];

	cone = (t_cone *)(obj->fig);
	pnts[0] = od[0] - (t_vector){FLT_MIN, cone->minh, FLT_MIN};
	pnts[1] = od[0] - (t_vector){FLT_MIN, cone->maxh, FLT_MIN};
	t[0] = cone->minh == -FLT_MAX ? -FLT_MAX : -(pnts[0][1]) / od[1][1];
	t[1] = cone->maxh == FLT_MAX ? -FLT_MAX : -(pnts[1][1]) / od[1][1];
	sq_r[0] = cone->r[0] * cone->r[0];
	sq_r[1] = cone->r[1] * cone->r[1];
	if (t[0] <= 0 && t[1] <= 0)
		return (FLT_MAX);
	((t[0] > t[1] && t[1] > FLT_MIN) || t[0] < FLT_MIN)
		? ft_swap_float(&t[0], &t[1]),
			ft_swap(&pnts[0], &pnts[1], sizeof(t_vector)),
			ft_swap_float(&sq_r[0], &sq_r[1])
		: 1;
	pnts[2] = pnts[0] + ft_3_vector_scale(od[1], t[0]);
	pnts[3] = pnts[1] + ft_3_vector_scale(od[1], t[1]);
	i[0] = -1;
	while (++i[0] < 2)
	{
		if (t[i[0]] >= 0 && ft_3_vector_dot(
			pnts[i[0] + 2], pnts[i[0] + 2]) < sq_r[i[0]])
		{
			pnts[i[0] + 4] = uod[0] + ft_3_vector_scale(uod[1], t[i[0]]);
			*norm = ft_3_tounitvector(
				ft_3_norm_transform(&(obj->inverse), (t_vector) {0, 1, 0}));
			if (obj->is_neg)
				pnts[i[0] + 4] += ft_3_vector_scale(*norm, SHIFT);
			i[1] = ft_inside_type(objs, pnts[i[0] + 4]);
			(*norm)[3] = i[1];
			if (obj->is_neg && i[1] != 1)
				*norm = ft_3_vector_invert(*norm);
			if (i[1] < 0 || (obj->is_neg && i[1] == 0))
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

float			ft_collide_cone(t_list **objs, t_object *obj,
								 t_coll *coll, t_vector untr_od[2])
{
	t_cone		*con;
	t_vector	hit[2];
	float		res[2];
	float		sq_tan;
	t_vector	od[2];
	t_vector	norms[2];
	float 		t;

	con = (t_cone *)obj->fig;
	od[0] = ft_3_pnt_transform(&(obj->inverse), untr_od[0]);
	od[1] = ft_3_vec_transform(&(obj->inverse), untr_od[1]);
	sq_tan = 1 + con->tan * con->tan;
	if (!ft_solve_quadratic(
		ft_3_vector_dot(od[1], od[1]) - sq_tan * od[1][1] * od[1][1],
		2.0f * (ft_3_vector_dot(od[0], od[1]) - sq_tan * od[1][1] * od[0][1]),
		ft_3_vector_dot(od[0], od[0]) - sq_tan * od[0][1] * od[0][1],
		res) && IS_ZERO(od[1][1]))
		return (FLT_MAX);
	res[0] = (res[0] <= 0 && res[1] <= 0)
		? FLT_MAX
		: get_cides_coll(objs, od, untr_od, &hit[0], &norms[0], res, obj);
	res[1] = ((con->maxh == FLT_MAX && con->minh == -FLT_MAX)
		|| fabsf(od[1][1]) < 1e-6)
		? FLT_MAX
		: get_caps_coll(objs, od, untr_od, &hit[1], &norms[1], obj);
	if (res[0] == FLT_MAX && res[1] == FLT_MAX)
		return (FLT_MAX);
	t = get_closer_pnt(res, hit, norms, coll, obj);
	coll->coll_pnt = untr_od[0] + ft_3_vector_scale(untr_od[1], t);
	if (obj->is_neg)
	{
		coll->coll_pnt += ft_3_vector_scale(
			coll->norm, (coll->norm[3] != 1) ? -SHIFT : SHIFT);
		coll->o = ft_inside_obj(objs, coll->coll_pnt, ft_get_inner_object);
		coll->coll_pnt -= ft_3_vector_scale(
			coll->norm, (coll->norm[3] != 1) ? -SHIFT : SHIFT);
	}
	else
		coll->o = obj;
	return (t);
}

int			ft_is_inside_cone(t_object *o, t_vector point)
{
	t_cone		*cone;
	t_vector	upoint;

	cone = (t_cone *)o->fig;
	upoint = ft_3_pnt_transform(&(o->inverse), point);
	if (!IN_RANGE(upoint[1], cone->minh, cone->maxh))
	{
//		printf("OUTSIDE HEI\n");
		return (0);
	}
//	if ((ft_3_vector_dot(upoint, upoint) < upoint[1] * upoint[1] + powf(upoint[1] * cone->tan, 2)))
//		printf("INSIDE: (%8.3f, %8.3f, %8.3f)\n",
//			point[0], point[1], point[2]);
//	else
//		printf("OUTSIDE\n");
	return ((ft_3_vector_dot(upoint, upoint)
			< upoint[1] * upoint[1] + powf(upoint[1] * cone->tan, 2.0f)) ? 1 : 0);
}

t_vector	ft_get_norm_cone(void *fig, t_vector coll)
{
	t_cone 		*con;

	con = (t_cone *)fig;
//	con->h = ft_3_vector_dot(con->v, coll - con->o);
//	if (con->maxh != FLT_MAX && con->h >= con->maxh - 1e-2)
//		return (con->v);
//	if (con->minh != FLT_MIN && con->h <= con->minh + 1e-2)
//		return (-con->v);
//	return (ft_3_tounitvector(coll - ((t_cone *)fig)->o - ft_3_vector_scale(con->v,
//			(1.0f + con->tan * con->tan) * con->h)));
	return (ft_3_nullpointnew());
}