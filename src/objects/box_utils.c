
#include "rt.h"

int			ft_is_reachable_box(void *fig, t_vector origin, t_vector direct)
{
	(void)fig;
	(void)origin;
	(void)direct;
	return (1);
}

t_vector	ft_collide_box(void *fig, t_vector origin, t_vector direct)
{
	t_box		*bx;
	t_vector	coll;
	float		t_min[3];
	float		t_max[3];
	float		t[2];
	
	bx = (t_box *)fig;
	t_min[0] = (bx->bounds[0][0] - origin[0]) / direct[0];
	t_max[0] = (bx->bounds[1][0] - origin[0]) / direct[0];
	t_min[1] = (bx->bounds[0][1] - origin[0]) / direct[0];
	t_max[1] = (bx->bounds[1][1] - origin[0]) / direct[0];

	if (t_min[0] > t_max[0])
		ft_swap_float(&t_min[0], &t_max[0]);
	if (t_min[1] > t_max[1])
		ft_swap_float(&t_min[1], &t_max[1]);
	if (t_min[0] > t_max[1] || t_max[0] < t_min[1])
		return (ft_3_nullpointnew());
	t[0] = t_min[0] > t_min[1] ? t_min[0] : t_min[1];
	t[1] = t_max[0] < t_max[1] ? t_min[0] : t_min[1];
	t_min[2] = (bx->bounds[0][2] - origin[0]) / direct[2];
	t_max[2] = (bx->bounds[1][2] - origin[0]) / direct[2];
	if (t_min[2] > t_max[2])
		ft_swap_float(&t_min[2], &t_max[2]);
	if (t_min[2] > t[1] || t_max[2] < t[0])
		return (ft_3_nullpointnew());
	t[0] = t[0] > t_min[2] ? t[0] : t_min[2];
	t[1] = t[1] < t_max[2] ? t[1] : t_max[2];
	if (t[0] < 0 || t[0] > t[1])
		ft_swap_float(&t[0], &t[1]);
	return (t[0] > 0 ? origin + ft_3_vector_scale(direct, t[0]) : ft_3_nullpointnew());
}

int			ft_is_inside_box(void *fig, t_vector point)
{
	(void)fig;
	(void)point;
	return (0);
}

t_vector	ft_get_norm_box(void *fig, t_vector coll)
{
	(void)coll;
	return (((t_box *)fig)->norm);
}
