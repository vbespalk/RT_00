
#include "rt.h"

int			ft_is_reachable_disk(void *fig, t_vector origin, t_vector direct)
{
	(void)fig;
	(void)origin;
	(void)direct;
	return (1);
}

t_vector	ft_collide_disk(void *fig, t_vector origin, t_vector direct)
{
	t_disk		*dsk;
	t_vector	coll;
	float		dis;

	dsk = (t_disk *)fig;
	coll = ft_3_line_plane_inter(dsk->origin, dsk->norm, origin, direct);
	dis = ft_3_vector_dot(coll - dsk->origin, coll - dsk->origin);
	return ((!ft_3_pointcmp(ft_3_tounitvector(coll - origin), direct, 1e-6)) 
		|| (dis > dsk->radius * dsk->radius) ? ft_3_nullpointnew() : coll);
}

int			ft_is_inside_disk(void *fig, t_vector point)
{
	(void)fig;
	(void)point;
	return (0);
}

t_vector	ft_get_norm_disk(void *fig, t_vector coll)
{
	(void)coll;
	return (((t_disk *)fig)->norm);
}
