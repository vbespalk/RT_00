/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 13:20:16 by domelche          #+#    #+#             */
/*   Updated: 2018/09/21 13:20:28 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_set_coll_pnts_null(t_point3 *pnt1, t_point3 *pnt2)
{
	*pnt1 = ft_3_nullpointnew();
	*pnt2 = *pnt1;
}

void		ft_get_coll_pnts_cyl(t_cone *cone, t_point3 (*pnt)[4])
{
	t_point3	a;
	float		s;
	float		dist;

	a = ft_3_line_line_inter((*pnt)[0], (*pnt)[1], cone->base, cone->bv);
	if ((dist = ft_3_line_point_dist(cone->base, cone->bv, a)) >
		cone->base_rad ||
		ft_3_vector_cos((*pnt)[1], ft_3_vectornew((*pnt)[0], a)) < 0)
		return (ft_set_coll_pnts_null(&((*pnt)[0]), &((*pnt)[1])));
	s = (float)(cone->base_rad * sqrt(1 - pow(dist / cone->base_rad, 2)) /
		sqrt(1 - pow(ft_3_vector_cos(cone->bv, (*pnt)[1]), 2)));
	(*pnt)[0] = ft_3_vector_add(a, ft_3_vector_scale((*pnt)[1], -s));
	(*pnt)[1] = ft_3_vector_add(a, ft_3_vector_scale((*pnt)[1], s));
}

void		ft_is_between_planes
				(t_point3 (*pnt)[4], t_point3 base, t_point3 vert)
{
	t_point3	bv;
	t_point3	vb;

	bv = ft_3_vectornew(base, vert);
	vb = ft_3_vector_scale(bv, -1);
	if (ft_3_isnullpoint((*pnt)[0]) ||
		ft_3_vector_cos(bv, ft_3_vectornew(base, (*pnt)[0])) < 0 ||
		ft_3_vector_cos(vb, ft_3_vectornew(vert, (*pnt)[0])) < 0)
		(*pnt)[0] = ft_3_nullpointnew();
	if (ft_3_isnullpoint((*pnt)[1]) ||
		ft_3_vector_cos(bv, ft_3_vectornew(base, (*pnt)[1])) < 0 ||
		ft_3_vector_cos(vb, ft_3_vectornew(vert, (*pnt)[1])) < 0)
		(*pnt)[1] = ft_3_nullpointnew();
}

void		ft_collide_cone_planes
				(t_cone *cone, t_point3 origin,
				t_point3 direct, t_point3 (*pnt)[4])
{
	(*pnt)[2] = ft_3_line_plane_inter(cone->base, cone->bv, origin, direct);
	if (ft_3_vector_cos(direct, ft_3_vectornew(origin, (*pnt)[2])) < 0 ||
		ft_3_point_point_dist(cone->base, (*pnt)[2]) > fabs(cone->base_rad))
		(*pnt)[2] = ft_3_nullpointnew();
	(*pnt)[3] = ft_3_line_plane_inter(cone->vert, cone->bv, origin, direct);
	if (ft_3_vector_cos(direct, ft_3_vectornew(origin, (*pnt)[3])) < 0 ||
		ft_3_point_point_dist(cone->vert, (*pnt)[3]) > fabs(cone->vert_rad))
		(*pnt)[3] = ft_3_nullpointnew();
}

t_point3	ft_get_closest(t_point3 cam, t_point3 pnt[4])
{
	float		dist;
	float		tmp;
	t_point3	res;
	int			i;

	dist = -1;
	res = ft_3_nullpointnew();
	i = -1;
	while (++i < 4)
	{
		if (ft_3_isnullpoint(pnt[i]))
			continue ;
		tmp = ft_3_point_point_dist(cam, pnt[i]);
		if (dist < 0 || tmp < dist)
		{
			dist = tmp;
			res = pnt[i];
		}
	}
	return (res);
}
