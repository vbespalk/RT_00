/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 13:25:05 by domelche          #+#    #+#             */
/*   Updated: 2018/08/23 13:26:14 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_point3	ft_collide_cone(void *fig, t_point3 origin, t_point3 direct)
{
	t_cone		*cone;
	t_point3	pnt[4];

	cone = (t_cone *)fig;
	pnt[0] = origin;
	pnt[1] = direct;
	ft_get_coll_pnts(cone, &pnt, cone->base_rad == cone->vert_rad);
	ft_is_between_planes(&pnt, cone->base, cone->vert);
	ft_collide_cone_planes(cone, origin, direct, &pnt);
	return (ft_get_closest(origin, pnt));
}

void		ft_get_coll_pnts(t_cone *cone, t_point3 (*pnt)[4], int is_cyl)
{
	float		cos_t_2;
	t_point3	v_co[2];
	float		dv_dot;
	float		cov_dot;
	float		res[3];

	if (is_cyl)
		return (ft_get_coll_pnts_cyl(cone, pnt));
	v_co[0] = ft_3_vector_scale(cone->bv, -1.0);
	cos_t_2 = (float)pow(cone->bv_dist / sqrt(
		pow(cone->base_rad - cone->vert_rad, 2) + pow(cone->bv_dist, 2)), 2);
	v_co[1] = ft_3_vectornew(cone->main_vert, (*pnt)[0]);
	dv_dot = ft_3_vector_dot((*pnt)[1], v_co[0]);
	cov_dot = ft_3_vector_dot(v_co[1], v_co[0]);
	ft_solve_sqr(pow(dv_dot, 2) - cos_t_2,
		2 * (dv_dot * cov_dot - ft_3_vector_dot((*pnt)[1], v_co[1]) * cos_t_2),
		pow(cov_dot, 2) - ft_3_vector_dot(v_co[1], v_co[1]) * cos_t_2, &res);
	if (res[0] == 0.0)
		return (ft_set_coll_pnts_null(&((*pnt)[0]), &((*pnt)[1])));
	v_co[0] = (*pnt)[0];
	(*pnt)[0] = (res[1] < 0.0) ? ft_3_nullpointnew() :
				ft_3_vector_add(v_co[0], ft_3_vector_scale((*pnt)[1], res[1]));
	(*pnt)[1] = (res[2] < 0.0) ? ft_3_nullpointnew() :
				ft_3_vector_add(v_co[0], ft_3_vector_scale((*pnt)[1], res[2]));
}

int			ft_is_inside_cone(void *fig, t_point3 point)
{
	t_cone		*cone;
	t_point3	bv;
	t_point3	vb;
	t_point3	proj;
	float		rad;

	cone = (t_cone *)fig;
	bv = ft_3_vectornew(cone->base, cone->vert);
	vb = ft_3_vector_scale(bv, -1);
	if (ft_3_vector_cos(bv, ft_3_vectornew(cone->base, point)) < 0 ||
		ft_3_vector_cos(vb, ft_3_vectornew(cone->vert, point)) < 0)
		return (0);
	proj = ft_3_line_point_proj(cone->base, ft_3_tounitvector(bv), point);
	rad = cone->base_rad + (cone->vert_rad - cone->base_rad) *
		(ft_3_point_point_dist(cone->base, proj) /
		ft_3_point_point_dist(cone->vert, proj));
	return ((ft_3_point_point_dist(proj, point) < rad) ? 1 : 0);
}

t_point3	ft_get_norm_cone(void *fig, t_point3 coll)
{
	t_cone		*cone;
	t_point3	proj;
	float		sign;

	cone = (t_cone *)fig;
	proj = ft_3_line_point_proj(cone->base, cone->bv, coll);
	if (ft_3_pointcmp(proj, cone->base, 1e-3))
		return (ft_3_vector_scale(cone->bv, -1));
	if (ft_3_pointcmp(proj, cone->vert, 1e-3))
		return (cone->bv);
	if (cone->base_rad == cone->vert_rad)
		return (ft_3_unitvectornew(proj, coll));
	sign = (cone->base_rad > cone->vert_rad) ? 1.0f : -1.0f;
	sign *= (ft_3_vector_cos(ft_3_vectornew(cone->main_vert, cone->base),
		ft_3_vectornew(cone->main_vert, proj)) < 0) ? -1.0f : 1.0f;
	return (ft_3_tounitvector(ft_3_vector_turn(cone->bv,
		ft_3_unitvectornew(proj, coll), sign * cone->side_norm_angle)));
}

