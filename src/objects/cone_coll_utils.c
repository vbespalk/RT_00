/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_coll_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 18:54:31 by domelche          #+#    #+#             */
/*   Updated: 2019/05/25 18:54:33 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static float	ft_check_cides_coll(t_cone_coll *cc)
{
	t_cone		*cone;

	cone = (t_cone *)(cc->obj->fig);
	cc->i[1] = 0;
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

float			ft_get_cone_cides_coll(
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

float			ft_get_cone_caps_coll(
					t_list **objs, t_vector v[4][2], t_object *obj)
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
