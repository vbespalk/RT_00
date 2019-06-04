/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 18:25:28 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/22 18:25:31 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float		ft_collide_disk(
				t_list **objs, t_object *obj, t_coll *coll, t_vector untr_od[2])
{
	t_disk		*dsk;
	float		t;
	float		dis;
	t_vector	od[2];

	dsk = (t_disk *)obj->fig;
	od[0] = ft_3_pnt_transform(&(obj->inverse), untr_od[0]);
	od[1] = ft_3_vec_transform(&(obj->inverse), untr_od[1]);
	if (!od[1][1])
		return (FLT_MAX);
	t = -od[0][1] / od[1][1];
	if (t < 0)
		return (FLT_MAX);
	coll->coll_pnt = untr_od[0] + ft_3_vector_scale(untr_od[1], t);
	if (obj->react_neg && ft_inside_type(objs, coll->coll_pnt) == IT_NEG)
		return (FLT_MAX);
	coll->ucoll_pnt = od[0] + ft_3_vector_scale(od[1], t);
	coll->o = obj;
	coll->tex_o = obj;
	coll->norm = obj->ft_get_norm(obj->fig, &(obj->inverse), coll->ucoll_pnt);
	dis = ft_3_vector_dot(coll->ucoll_pnt, coll->ucoll_pnt);
	return (IN_RANGE(dis, dsk->sq_in_r, dsk->sq_out_r) ? t : FLT_MAX);
}

int			ft_is_inside_disk(t_object *o, t_vector point)
{
	(void)o;
	(void)point;
	return (0);
}

t_vector	ft_get_norm_disk(void *fig, t_matrix *inv_m, t_vector coll)
{
	(void)fig;
	(void)coll;
	return (ft_3_tounitvector(
			ft_3_norm_transform(inv_m, (Y_AXIS))));
}
