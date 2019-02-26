
#include "rt.h"

int			ft_is_reachable_quad(void *fig, t_vector origin, t_vector direct)
{
	(void)fig;
	(void)origin;
	(void)direct;
	return (1);
}

t_vector	ft_collide_quad(void *fig, t_vector origin, t_vector direct)
{
	t_quad		*qd;
	t_vector	coll;
	
	t_vector	c0;
	t_vector	c1;
	t_vector	c2;
	t_vector	c3;
	t_vector	v3;

	qd = (t_quad *)fig;
	v3 = qd->v2 + qd->v1 - qd->v0;
	coll = ft_3_line_plane_inter(qd->v0, qd->norm, origin, direct);
	if (ft_3_isnullpoint(coll) && !ft_3_pointcmp(ft_3_tounitvector(coll - origin), direct, 1e-6))
		return (ft_3_nullpointnew());
	c0 = coll - qd->v0;
	c1 = coll - qd->v1;
	c2 = coll - v3;
	c3 = coll - qd->v2;
	if (ft_3_vector_dot(ft_3_vector_cross(qd->v0 - qd->v1, c0), qd->norm) > 0 &&
		ft_3_vector_dot(ft_3_vector_cross(qd->v1 - v3, c1), qd->norm) > 0 &&
		ft_3_vector_dot(ft_3_vector_cross(v3 - qd->v2, c2), qd->norm) > 0 &&
		ft_3_vector_dot(ft_3_vector_cross(qd->v2 - qd->v0, c3), qd->norm) > 0)
		return (coll);
	return (ft_3_nullpointnew());
}

int			ft_is_inside_quad(void *fig, t_vector point)
{
	(void)fig;
	(void)point;
	return (0);
}

t_vector	ft_get_norm_quad(void *fig, t_vector coll)
{
	(void)coll;
	return (((t_quad *)fig)->norm);
}



// t_vector	ft_collide_quad(void *fig, t_vector origin, t_vector direct)
// {
// 	t_quad		*qd;
// 	t_vector	coll;
// 	float		cosa;
// 	float		cosb;
// 	static int 	fl;

// 	qd = (t_quad *)fig;
// 	coll = ft_3_line_plane_inter(qd->v0, qd->norm, origin, direct);
// 	if (ft_3_isnullpoint(coll) && !ft_3_pointcmp(ft_3_tounitvector(coll - origin), direct, 1e-6))
// 		return (ft_3_nullpointnew());
// 	cosa = ft_3_vector_dot(ft_3_tounitvector(qd->v1 - qd->v0), ft_3_tounitvector(coll - qd->v0));
// 	cosb = ft_3_vector_dot(ft_3_tounitvector(qd->v2 - qd->v0), ft_3_tounitvector(coll - qd->v0));
// 	if (RANGE_STRICT(ft_3_vector_len(coll - qd->v0) * (cosa), 0, ft_3_vector_len(qd->v0 - qd->v1)) &&
// 		RANGE_STRICT(ft_3_vector_len(coll - qd->v0) * (cosb), 0, ft_3_vector_len(qd->v0 - qd->v2)))
// 		return (coll);
// 	return (ft_3_nullpointnew());