/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_coll_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 18:54:47 by domelche          #+#    #+#             */
/*   Updated: 2019/05/25 18:54:49 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float			ft_get_clnd_closer_pnt(
					const float *t, const t_vector *hit,
					t_coll *coll, t_vector *norms)
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

float			ft_get_clnd_cides_coll(
					t_list **objs, t_vector v[4][2], float *t, t_object *obj)
{
	int			i[2];
	t_vector	hit[4];

	i[0] = -1;
	while (++i[0] < 2)
	{
		hit[i[0]] = v[0][0] + ft_3_vector_scale(v[0][1], t[i[0]]);
		if (t[i[0]] >= 0 && IN_RANGE(hit[i[0]][1],
		-((t_cylinder *)(obj->fig))->maxh, ((t_cylinder *)(obj->fig))->maxh))
		{
			hit[i[0] + 2] = v[1][0] + ft_3_vector_scale(v[1][1], t[i[0]]);
			v[3][0] = obj->ft_get_norm(obj->fig, &(obj->inverse), hit[i[0]]);
			if (obj->is_neg)
				hit[i[0] + 2] += ft_3_vector_scale(v[3][0], SHIFT);
			if (obj->react_neg || obj->is_neg)
				i[1] = ft_inside_type(objs, hit[i[0] + 2]);
			v[3][0][3] = i[1];
			if (ft_is_invisible(obj, i[1]))
				continue ;
			v[2][0] = hit[i[0]];
			return (t[i[0]]);
		}
	}
	return (FLT_MAX);
}

static void		ft_init_pnts(
					t_vector v[4][2], t_vector pnts[3][2],
					float t[2], t_object *obj)
{
	t_cylinder	*clnd;

	clnd = (t_cylinder *)(obj->fig);
	pnts[0][0] = (t_vector) {
		v[0][0][0], v[0][0][1] + clnd->maxh, v[0][0][2], clnd->maxh };
	pnts[0][1] = (t_vector) {
		v[0][0][0], v[0][0][1] - clnd->maxh, v[0][0][2], -clnd->maxh };
	t[0] = -(pnts[0][0][1]) / v[0][1][1];
	t[1] = -(pnts[0][1][1]) / v[0][1][1];
	if (t[0] <= 0 && t[1] <= 0)
		return ;
	if (t[0] > t[1] || t[0] < 0)
	{
		ft_swap_float(&t[0], &t[1]);
		ft_swap(&pnts[0][0], &pnts[0][1], sizeof(t_vector));
	}
	pnts[1][0] = pnts[0][0] + ft_3_vector_scale(v[0][1], t[0]);
	pnts[1][1] = pnts[0][1] + ft_3_vector_scale(v[0][1], t[1]);
}

static float	ft_check_caps_coll(t_clnd_coll *cc)
{
	if (cc->t[cc->i[0]] >= 0
		&& ft_3_vector_dot(cc->pnts[1][cc->i[0]], cc->pnts[1][cc->i[0]]) < 1)
	{
		cc->pnts[1][cc->i[0]] += (t_vector) { 0, cc->pnts[0][cc->i[0]][3], 0 };
		cc->pnts[2][cc->i[0]] =
			cc->v[1][0] + ft_3_vector_scale(cc->v[1][1], cc->t[cc->i[0]]);
		cc->v[3][1] = ft_get_norm_plane(
			cc->obj->fig, &(cc->obj->inverse), cc->pnts[1][cc->i[0]]);
		if (ft_3_vector_cos(
			cc->v[3][1], cc->pnts[2][cc->i[0]] - cc->obj->translate) < 0)
			cc->v[3][1] = ft_3_vector_invert(cc->v[3][1]);
		if (cc->obj->is_neg)
			cc->pnts[2][cc->i[0]] += ft_3_vector_scale(cc->v[3][1], SHIFT);
		if (cc->obj->react_neg || cc->obj->is_neg)
			cc->i[1] = ft_inside_type(cc->objs, cc->pnts[2][cc->i[0]]);
		cc->v[3][1][3] = cc->i[1];
		if (ft_is_invisible(cc->obj, cc->i[1]))
			return (FLT_MAX);
		cc->v[2][1] = cc->pnts[1][cc->i[0]];
		return (cc->t[cc->i[0]]);
	}
	return (FLT_MAX);
}

float			ft_get_clnd_caps_coll(
					t_list **objs, t_vector v[4][2], t_object *obj)
{
	float		res;
	t_clnd_coll	cc;

	cc.objs = objs;
	cc.obj = obj;
	cc.v = v;
	ft_init_pnts(v, cc.pnts, cc.t, obj);
	if (cc.t[0] <= 0 && cc.t[1] <= 0)
		return (FLT_MAX);
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
