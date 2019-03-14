
#include "rt.h"
static int 	ft_inside_quad(void *fig, t_vector coll)
{
	t_plane 	*pln;
	float		proj[2];

	pln = (t_plane *)fig;
	proj[0] = ft_3_vector_dot(coll - pln->origin, pln->dir_wh[0]);
	proj[1] = ft_3_vector_dot(coll - pln->origin, pln->dir_wh[1]);
	if (IN_RANGE(proj[0], FLT_MIN, pln->len_wh[0])
		&& IN_RANGE(proj[1], FLT_MIN, pln->len_wh[1]))
		return (1);
	return (0);

}

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
	if (ft_3_isnullpoint(coll))
		return (coll);
	if (pln->len_wh[0] == FLT_MIN || pln->len_wh[1] == FLT_MIN)
		return (coll);
	return (!ft_inside_quad(fig, coll) ? ft_3_nullpointnew() : coll);
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
