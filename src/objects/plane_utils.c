
#include "rt.h"

int			ft_is_reachable_plane(void *fig, t_point3 origin, t_point3 direct)
{
	(void)fig;
	(void)origin;
	(void)direct;
	return (1);
}

t_point3	ft_collide_plane(void *fig, t_point3 origin, t_point3 direct)
{
	t_plane		*pln;
	t_point3	coll;

	pln = (t_plane *)fig;
	coll = ft_3_line_plane_inter(pln->origin, pln->norm, origin, direct);
	return ((!ft_3_pointcmp(ft_3_unitvectornew(origin, coll), direct, 1e-6)) ?
			ft_3_nullpointnew() : coll);
}

int			ft_is_inside_plane(void *fig, t_point3 point)
{
	(void)fig;
	(void)point;
	return (0);
}

t_point3	ft_get_norm_plane(void *fig, t_point3 coll)
{
	(void)coll;
	return (((t_plane *)fig)->norm);
}
