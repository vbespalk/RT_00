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

static float	ft_check_cides_coll(t_cone_coll *cc)
{
	t_cone		*cone;

	cone = (t_cone *)(cc->obj->fig);
	if (cc->t[cc->i[0]] >= FLT_MIN
		&& IN_RANGE(cc->pnts[0][cc->i[0]][1], cone->minh, cone->maxh))
	{
		cc->pnts[1][cc->i[0]] =
			cc->v[1][0] + ft_3_vector_scale(cc->v[1][1], cc->t[cc->i[0]]);
		cc->v[3][0] = cc->obj->ft_get_norm(
			cc->obj->fig, &cc->obj->inverse, cc->pnts[0][cc->i[0]]);
		if (cc->obj->is_neg)
			cc->pnts[1][cc->i[0]] += ft_3_vector_scale(cc->v[3][0], SHIFT);
		if (cc->obj->react_neg || cc->obj->is_neg)
			cc->i[1] = ft_inside_type(cc->objs, cc->pnts[1][cc->i[0]]);
		cc->v[3][0][3] = cc->i[1];
		if (ft_is_invisible(cc->obj, cc->i[1]))
			return (FLT_MAX);
		cc->v[2][0] = cc->pnts[0][cc->i[0]];
		return (cc->t[cc->i[0]]);
	}
	return (FLT_MAX);
}

static float	get_cides_coll(
					t_list **objs, t_vector v[4][2], float t[2], t_object *obj)
{
	float		res;
	t_cone_coll	cc;

	cc.objs = objs;
	cc.obj = obj;
	cc.t = t;
	cc.v = v;
	cc.pnts[0][0] = v[0][0] + ft_3_vector_scale(v[0][1], t[0]);
	if (((t_cone *)(obj->fig))->maxh == FLT_MAX
	&& ((t_cone *)(obj->fig))->minh == FLT_MIN)
	{
		v[2][0] = cc.pnts[0][0];
		return (t[0]);
	}
	cc.pnts[0][1] = v[0][0] + ft_3_vector_scale(v[0][1], t[1]);
	cc.i[0] = -1;
	while (++cc.i[0] < 2)
	{
		res = ft_check_cides_coll(&cc);
		if (res == FLT_MAX)
			continue ;
		return (res);
	}
	return (FLT_MAX);
}

static void		ft_init_pnts(
					t_object *obj, t_vector pnts[3][2],
					t_vector v[4][2], float t[4])
{
	t_cone		*cone;

	cone = (t_cone *)(obj->fig);
	pnts[0][0] = (t_vector) {
		v[0][0][0], v[0][0][1] - cone->minh, v[0][0][2], cone->minh };
	pnts[0][1] = (t_vector) {
		v[0][0][0], v[0][0][1] - cone->maxh, v[0][0][2], cone->maxh };
	t[0] = cone->minh == -FLT_MAX ? -FLT_MAX : -(pnts[0][0][1]) / v[0][1][1];
	t[1] = cone->maxh == FLT_MAX ? -FLT_MAX : -(pnts[0][1][1]) / v[0][1][1];
	t[2] = cone->r[0] * cone->r[0];
	t[3] = cone->r[1] * cone->r[1];
	if (t[0] <= 0 && t[1] <= 0)
		return ;
	if ((t[0] > t[1] && t[1] > FLT_MIN) || t[0] < FLT_MIN)
	{
		ft_swap_float(&t[0], &t[1]);
		ft_swap(&pnts[0][0], &pnts[0][1], sizeof(t_vector));
		ft_swap_float(&t[2], &t[3]);
	}
}

static float	ft_check_caps_coll(t_cone_coll *cc)
{
	if (cc->t[cc->i[0]] >= 0 && ft_3_vector_dot(
		cc->pnts[1][cc->i[0]], cc->pnts[1][cc->i[0]]) < cc->t[cc->i[0] + 2])
	{
		cc->pnts[2][cc->i[0]] =
			cc->v[1][0] + ft_3_vector_scale(cc->v[1][1], cc->t[cc->i[0]]);
		cc->v[3][1] = ft_get_norm_plane(
			cc->obj->fig, &(cc->obj->inverse), cc->pnts[2][cc->i[0]]);
		if (cc->obj->is_neg)
			cc->pnts[2][cc->i[0]] += ft_3_vector_scale(cc->v[3][1], SHIFT);
		if (cc->obj->react_neg || cc->obj->is_neg)
			cc->i[1] = ft_inside_type(cc->objs, cc->pnts[2][cc->i[0]]);
		cc->v[3][1][3] = cc->i[1];
		if (ft_is_invisible(cc->obj, cc->i[1]))
			return (FLT_MAX);
		cc->v[2][1] =
			cc->pnts[1][cc->i[0]] + (t_vector){0, cc->pnts[0][cc->i[0]][3], 0};
		return (cc->t[cc->i[0]]);
	}
	return (FLT_MAX);
}

static float	get_caps_coll(t_list **objs, t_vector v[4][2], t_object *obj)
{
	t_cone_coll	cc;
	float		t[4];
	float		res;

	ft_init_pnts(obj, cc.pnts, v, t);
	if (t[0] <= 0 && t[1] <= 0)
		return (FLT_MAX);
	cc.objs = objs;
	cc.obj = obj;
	cc.v = v;
	cc.t = t;
	cc.pnts[1][0] = cc.pnts[0][0] + ft_3_vector_scale(v[0][1], t[0]);
	cc.pnts[1][1] = cc.pnts[0][1] + ft_3_vector_scale(v[0][1], t[1]);
	cc.i[0] = -1;
	while (++cc.i[0] < 2)
	{
		res = ft_check_caps_coll(&cc);
		if (res == FLT_MAX)
			continue ;
		return (res);
	}
	return (FLT_MAX);
}

static int		ft_handle_solve_qdr(
					t_object *obj, t_vector v[4][2], float res[2])
{
	t_cone		*con;

	con = (t_cone *)obj->fig;
	return (ft_solve_qdr(
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
	if (!ft_handle_solve_qdr(obj, v, res))
		return (FLT_MAX);
	res[0] = (res[0] <= 0 && res[1] <= 0)
		? FLT_MAX : get_cides_coll(objs, v, res, obj);
	res[1] = ((((t_cone *)obj->fig)->maxh == FLT_MAX
		&& ((t_cone *)obj->fig)->minh == -FLT_MAX)
		|| fabsf(v[0][1][1]) < 1e-6) ? FLT_MAX : get_caps_coll(objs, v, obj);
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

int			ft_is_inside_cone(t_object *o, t_vector point)
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

t_vector	ft_get_norm_cone(void *fig, t_matrix *inv_m, t_vector coll)
{
	t_cone		*con;

	con = (t_cone *)fig;
	return (ft_3_tounitvector(
		ft_3_norm_transform(
			inv_m,
			coll - ft_3_vector_scale((t_vector){ 0, coll[1], 0 },
			powf(con->tan, 2.0f) + 1))));
}
