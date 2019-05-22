/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 23:19:56 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/21 23:19:58 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	ft_check_side(t_list **objs, t_object *obj, t_coll *coll,
		t_coll *pln_coll)
{
	pln_coll->norm = ft_3_tounitvector(
			ft_3_norm_transform(&(obj->inverse), pln_coll->norm));
	if (ft_3_vector_cos(
			pln_coll->norm, pln_coll->coll_pnt - obj->translate) < 0)
		pln_coll->norm = ft_3_vector_invert(pln_coll->norm);
	if (obj->is_neg)
		pln_coll->coll_pnt += ft_3_vector_scale(pln_coll->norm, SHIFT);
	if (obj->react_neg || obj->is_neg)
		coll->inside_type = ft_inside_type(objs, pln_coll->coll_pnt);
	if (ft_is_invisible(obj, coll->inside_type))
		return (0);
	coll->coll_pnt = pln_coll->coll_pnt;
	coll->ucoll_pnt = pln_coll->ucoll_pnt;
	coll->norm = pln_coll->norm;
	coll->tex_o = pln_coll->o;
	return (1);
}

float		ft_collide_box(
				t_list **objs, t_object *obj, t_coll *coll, t_vector untr_od[2])
{
	t_box		*bx;
	t_coll		pln_coll;
	float		t[2];
	int			i;
	t_vector	od[2];

	bx = (t_box *)obj->fig;
	i = -1;
	od[0] = ft_3_pnt_transform(&(obj->inverse), untr_od[0]);
	od[1] = ft_3_vec_transform(&(obj->inverse), untr_od[1]);
	t[0] = FLT_MAX;
	while (++i < BOX_FACES)
	{
		t[1] = ft_collide_plane(objs, bx->face[i], &pln_coll, od);
		if (t[1] > FLT_MIN && t[1] < t[0])
		{
			pln_coll.coll_pnt =
				untr_od[0] + ft_3_vector_scale(untr_od[1], t[1]);
			if (ft_check_side(objs, obj, coll, &pln_coll) == 0)
				continue ;
			t[0] = t[1];
		}
	}
	t[0] < FLT_MAX ? ft_choose_object(objs, obj, coll) : 1;
	return (t[0]);
}

int			ft_is_inside_box(t_object *o, t_vector point)
{
	t_box		*bx;
	float		proj[3];

	if (!o->fig)
		return (0);
	bx = (t_box *)o->fig;
	point = ft_3_pnt_transform(&(o->inverse), point);
	proj[0] = fabsf(ft_3_vector_dot(Z_AXIS, point));
	proj[1] = fabsf(ft_3_vector_dot(Y_AXIS, point));
	proj[2] = fabsf(ft_3_vector_dot(X_AXIS, point));
	if (!IN_RANGE(proj[0], 0, bx->whl[0]) ||
		!IN_RANGE(proj[1], 0, bx->whl[1]) ||
		!IN_RANGE(proj[2], 0, bx->whl[2]))
		return (0);
	return (1);
}
