
#include "rt.h"

int			ft_is_reachable_triangle(void *fig, t_vector origin, t_vector direct)
{
	(void)fig;
	(void)origin;
	(void)direct;
	return (1);
}

t_vector	ft_collide_triangle(void *fig, t_vector origin, t_vector direct)
{
	t_triangle	*trgl;
	t_vector	coll;
	t_vector	qvec;
	float		det;
	float		t;

	// printf("dir triangle %f,%f,%f\n", direct[0], direct[1], direct[2]);
	trgl = (t_triangle *)fig;
	direct = ft_3_vector_scale(direct, -1);
	det = ft_3_vector_dot(direct, trgl->unorm);
	// printf("det %f det2 %f\n", det, ft_3_vector_dot(pvec, trgl->v2 - trgl->v0));
	if (det < 1e-6)
		return (ft_3_nullpointnew());
	det = 1.0f / det;
	qvec = ft_3_vector_cross(direct, origin - trgl->v0);
	trgl->u = ft_3_vector_dot(qvec, trgl->v1 - trgl->v0) * det;
	if ((trgl->u < 0.0f || trgl->u > 1.0f))
		return (ft_3_nullpointnew());
	trgl->v = ft_3_vector_dot(qvec, trgl->v2 - trgl->v0) * det;
	// printf("u %f v %f\n", trgl->u, trgl->v);
	if (trgl->v < 0.0f || trgl->u + trgl->v > 1.0f)
		return (ft_3_nullpointnew());
	t = ft_3_vector_dot(trgl->unorm, origin - trgl->v0) * det;
	// printf("t %f\n", t);
	coll = origin + ft_3_vector_scale(direct, t);
	return (coll);
}

int			ft_is_inside_triangle(void *fig, t_vector point)
{
	(void)fig;
	(void)point;
	return (0);
}

t_vector	ft_get_norm_triangle(void *fig, t_vector coll)
{
	(void)coll;
	return (((t_triangle *)fig)->norm);
}


	// trgl = (t_triangle *)fig;
	// pvec = ft_3_vector_cross(direct, trgl->v2 - trgl->v0);
	// det = ft_3_vector_dot(pvec, trgl->v1 - trgl->v0);
	// if (det < 1e-6)
	// 	return ((t_vector){0, 0, 0});
	// det = 1.0f / det;
	// trgl->u = ft_3_vector_dot(pvec, origin - trgl->v0) * det;
	// if ((trgl->u < 0.0f || trgl->u > 1.0f))
	// 	return ((t_vector){0, 0, 0});
	// qvec = ft_3_vector_cross(origin - trgl->v0, trgl->v1 - trgl->v0);
	// trgl->v = ft_3_vector_dot(qvec, direct) * det;
	// if (trgl->v < 0.0f || trgl->u + trgl->v > 1.0f)
	// 	return ((t_vector){0, 0, 0});
	// t = ft_3_vector_dot(qvec, trgl->v2 - trgl->v0) * det;
	// if (t < 0.0f)
	// 	return ((t_vector){0, 0, 0});
	// coll = origin + ft_3_vector_scale(direct, t);
	// return (coll);

