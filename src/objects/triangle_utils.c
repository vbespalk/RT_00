
#include "rt.h"

int			ft_is_reachable_triangle(void *fig, t_vector origin, t_vector direct)
{
	(void)fig;
	(void)origin;
	(void)direct;
	return (1);
}

float	ft_collide_triangle(t_list **objs, struct s_object *obj, t_coll *coll, t_vector od[2])
{
//	t_triangle	*trgl;
//	t_vector	coll;
//	t_vector	c0;
//	t_vector	c1;
//	t_vector	c2;
//
//	trgl = (t_triangle *)fig;
//	coll = ft_3_line_plane_inter(trgl->v0, trgl->norm, origin, direct);
//	if (ft_3_isnullpoint(coll) || !ft_3_pointcmp(ft_3_tounitvector(coll - origin), direct, 1e-6))
//		return (ft_3_nullpointnew());
//	c0 = coll - trgl->v0;
//	c1 = coll - trgl->v1;
//	c2 = coll - trgl->v2;
//	if (ft_3_vector_dot(ft_3_vector_cross(trgl->v0 - trgl->v1, c0), trgl->norm) > 0 &&
//		ft_3_vector_dot(ft_3_vector_cross(trgl->v1 - trgl->v2, c1), trgl->norm) > 0 &&
//		ft_3_vector_dot(ft_3_vector_cross(trgl->v2 - trgl->v0, c2), trgl->norm) > 0)
//		return (coll);
//	return (ft_3_nullpointnew());
	return (1);
}

int			ft_is_inside_triangle(t_object *o, t_vector point)
{
	(void)o;
	(void)point;
	return (0);
}

t_vector	ft_get_norm_triangle(void *fig, t_vector coll)
{
	(void)coll;
	return (((t_triangle *)fig)->norm);
}



