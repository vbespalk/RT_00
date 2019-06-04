/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 17:56:13 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/22 18:03:16 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static float	ft_collide_sphere_half(
					t_list **objs, t_object *obj,
					t_coll *coll, t_vector pnts[4])
{
	float	t;
	int		i;

	i = 0;
	t = (pnts[0][3] == FLT_MAX) ? pnts[1][3] : pnts[0][3];
	pnts[0][3] = FLT_MAX;
	if (t > 0)
	{
		coll->ucoll_pnt = pnts[2] + ft_3_vector_scale(pnts[3], t);
		coll->norm = obj->ft_get_norm(obj->fig, &(obj->inverse),
				coll->ucoll_pnt);
		coll->coll_pnt = pnts[0] + ft_3_vector_scale(pnts[1], t);
		if (obj->is_neg)
			coll->coll_pnt += ft_3_vector_scale(coll->norm, SHIFT);
		if (obj->react_neg || obj->is_neg)
			i = ft_inside_type(objs, coll->coll_pnt);
		if (ft_is_invisible(obj, i))
			return (0);
		return (t);
	}
	return (0);
}

float			ft_collide_sphere(
					t_list **objs, t_object *obj,
					t_coll *coll, t_vector uod[2])
{
	float		t[2];
	int			i;
	t_vector	pnts[4];

	pnts[0] = uod[0];
	pnts[1] = uod[1];
	pnts[2] = ft_3_pnt_transform(&(obj->inverse), uod[0]);
	pnts[3] = ft_3_vec_transform(&(obj->inverse), uod[1]);
	if (!ft_solve_qdr(ft_3_vector_dot(pnts[3], pnts[3]),
		2.0f * ft_3_vector_dot(pnts[3], pnts[2]),
		ft_3_vector_dot(pnts[2], pnts[2]) - 1, t) || (t[0] <= 0 && t[1] <= 0))
		return (FLT_MAX);
	i = -1;
	pnts[0][3] = t[0];
	pnts[1][3] = t[1];
	while (++i < 2)
		if ((t[i] = ft_collide_sphere_half(objs, obj, coll, pnts)) > 0)
			break ;
	if (t[0] <= 0 && t[1] <= 0)
		return (FLT_MAX);
	coll->tex_o = obj;
	ft_choose_object(objs, obj, coll);
	if (obj->is_neg)
		coll->norm = ft_3_vector_invert(coll->norm);
	return ((t[i] > 0) ? t[i] : FLT_MAX);
}

int				ft_is_inside_sphere(t_object *o, t_vector point)
{
	point = ft_3_pnt_transform(&(o->inverse), point);
	return ((ft_3_vector_len(point) < 1) ? 1 : 0);
}

t_vector		ft_get_norm_sphere(void *fig, t_matrix *inv_m, t_vector coll)
{
	(void)fig;
	return (ft_3_tounitvector(ft_3_norm_transform(
					inv_m, ft_3_tounitvector(coll))));
}
