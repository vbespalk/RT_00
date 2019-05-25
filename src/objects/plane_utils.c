/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 18:10:40 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/22 18:11:09 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	ft_inside_quad(void *fig, t_vector coll)
{
	t_plane		*pln;
	float		proj[2];

	pln = (t_plane *)fig;
	proj[0] = ft_3_vector_dot(coll - (t_vector){-pln->ratio, 0, -1},
			(t_vector){0, 0, 1});
	proj[1] = ft_3_vector_dot(coll - (t_vector){-pln->ratio, 0, -1},
			(t_vector){1, 0, 0});
	if (IN_RANGE(proj[0], FLT_MIN, 2)
		&& IN_RANGE(proj[1], FLT_MIN, pln->ratio * 2))
		return (1);
	return (0);
}

float		ft_collide_plane(
				t_list **objs, t_object *obj,
				t_coll *coll, t_vector untr_od[2])
{
	t_plane		*pln;
	t_vector	od[2];
	float		t;

	pln = (t_plane *)(obj->fig);
	od[0] = ft_3_pnt_transform(&(obj->inverse), untr_od[0]);
	od[1] = ft_3_vec_transform(&(obj->inverse), untr_od[1]);
	if (!od[1][1])
		return (FLT_MAX);
	t = -od[0][1] / od[1][1];
	if (t < 1e-6)
		return (FLT_MAX);
	coll->coll_pnt = untr_od[0] + ft_3_vector_scale(untr_od[1], t);
	if (!pln->is_in_box && obj->react_neg
		&& (coll->inside_type = ft_inside_type(objs, coll->coll_pnt)) == IT_NEG)
		return (FLT_MAX);
	coll->ucoll_pnt = od[0] + ft_3_vector_scale(od[1], t);
	if (!(pln->len_wh[0] == FLT_MIN || pln->len_wh[1] == FLT_MIN) &&
		!ft_inside_quad(pln, coll->ucoll_pnt))
		return (FLT_MAX);
	coll->norm = obj->ft_get_norm(obj->fig, &(obj->inverse), coll->ucoll_pnt);
	coll->o = obj;
	coll->tex_o = obj;
	return (t);
}

int			ft_is_inside_plane(t_object *o, t_vector point)
{
	(void)o;
	(void)point;
	return (0);
}

t_vector	ft_get_norm_plane(void *fig, t_matrix *inv_m, t_vector coll)
{
	(void)fig;
	(void)coll;
	return (ft_3_tounitvector(
			ft_3_norm_transform(inv_m, Y_AXIS)));
}
