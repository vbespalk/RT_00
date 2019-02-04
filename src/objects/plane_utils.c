
#include "rt.h"

int			ft_is_reachable_plane(void *fig, t_vector origin, t_vector direct)
{
	(void)fig;
	(void)origin;
	(void)direct;
	return (1);
}

t_vector	ft_collide_plane(void *fig, t_vector origin, t_vector direct)
{
	t_plane		*pln;
	t_vector	coll;

	pln = (t_plane *)fig;
	coll = ft_3_line_plane_inter(pln->origin, pln->norm, origin, direct);
	return ((!ft_3_pointcmp(ft_3_unitvectornew(origin, coll), direct, 1e-6)) ?
			ft_3_nullpointnew() : coll);
}

int			ft_is_inside_plane(void *fig, t_vector point)
{
	(void)fig;
	(void)point;
	return (0);
}

t_vector	ft_get_norm_plane(void *fig, t_vector coll)
{
	(void)coll;
	return (((t_plane *)fig)->norm);
}
