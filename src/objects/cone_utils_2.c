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

void		ft_set_coll_pnts_null(t_vector *pnt1, t_vector *pnt2)
{
	*pnt1 = ft_3_nullpointnew();
	*pnt2 = *pnt1;
}

void		ft_get_coll_pnts_cyl(t_cone *cone, t_vector (*pnt)[4])
{
	t_vector	a;
	float		s;
	float		dist;

	a = ft_3_line_line_inter((*pnt)[0], (*pnt)[1], cone->base, cone->bv);
	dist = ft_3_line_point_dist(cone->base, cone->bv, a);
	if (dist > cone->base_rad ||
		ft_3_vector_cos((*pnt)[1], a - (*pnt)[0]) < 0)
		return (ft_set_coll_pnts_null(&((*pnt)[0]), &((*pnt)[1])));
	s = cone->base_rad * (float)sqrt(1 - pow(dist / cone->base_rad, 2)) /
		(float)sqrt(1 - pow(ft_3_vector_cos(cone->bv, (*pnt)[1]), 2));
	(*pnt)[0] = a + ft_3_vector_scale((*pnt)[1], -s);
	(*pnt)[1] = a + ft_3_vector_scale((*pnt)[1], s);
}

void		ft_is_between_planes
				(t_vector (*pnt)[4], t_vector base, t_vector vert)
{
	t_vector	bv;
	t_vector	vb;

	bv = vert - base;
	vb = ft_3_vector_scale(bv, -1);
	if (ft_3_isnullpoint((*pnt)[0]) ||
		ft_3_vector_cos(bv, (*pnt)[0] - base) < 0 ||
		ft_3_vector_cos(vb, (*pnt)[0] - vert) < 0)
		(*pnt)[0] = ft_3_nullpointnew();
	if (ft_3_isnullpoint((*pnt)[1]) ||
		ft_3_vector_cos(bv, (*pnt)[1] - base) < 0 ||
		ft_3_vector_cos(vb, (*pnt)[1] - vert) < 0)
		(*pnt)[1] = ft_3_nullpointnew();
}

void		ft_collide_cone_planes
				(t_cone *cone, t_vector origin,
				t_vector direct, t_vector (*pnt)[4])
{
	(*pnt)[2] = ft_3_line_plane_inter(cone->base, cone->bv, origin, direct);
	if (ft_3_vector_cos(direct, (*pnt)[2] - origin) < 0 ||
		ft_3_point_point_dist(cone->base, (*pnt)[2]) > fabs(cone->base_rad))
		(*pnt)[2] = ft_3_nullpointnew();
	(*pnt)[3] = ft_3_line_plane_inter(cone->vert, cone->bv, origin, direct);
	if (ft_3_vector_cos(direct, (*pnt)[3] - origin) < 0 ||
		ft_3_point_point_dist(cone->vert, (*pnt)[3]) > fabs(cone->vert_rad))
		(*pnt)[3] = ft_3_nullpointnew();
}

t_vector	ft_get_closest(t_vector cam, t_vector pnt[4])
{
	float		dist;
	float		tmp;
	t_vector	res;
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
