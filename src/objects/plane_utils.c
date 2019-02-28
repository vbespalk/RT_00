
#include "rt.h"
static int 	ft_inside_quad(void *fig, t_vector coll)
{
	t_plane *pln;
	t_vector	c0;
	t_vector	c1;
	t_vector	c2;
	t_vector	c3;
	t_vector	v3;

	pln = (t_plane *)fig;
	// printf("INS QU %f,%f,%f\n", pln->norm[0], pln->norm[1], pln->norm[2]);
	v3 = pln->w + pln->h - pln->origin;
	c0 = coll - pln->origin;
	c1 = coll - pln->h;
	c2 = coll - v3;
	c3 = coll - pln->w;
	if (ft_3_vector_dot(ft_3_vector_cross(pln->origin - pln->h, c0), pln->norm) > 0 &&
		ft_3_vector_dot(ft_3_vector_cross(pln->h - v3, c1), pln->norm) > 0 &&
		ft_3_vector_dot(ft_3_vector_cross(v3 - pln->w, c2), pln->norm) > 0 &&
		ft_3_vector_dot(ft_3_vector_cross(pln->w - pln->origin, c3), pln->norm) > 0)
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
	if ((!ft_3_pointcmp(ft_3_unitvectornew(origin, coll), direct, 1e-6)))
		return (ft_3_nullpointnew());
	if (ft_3_isnullpoint(pln->w) && ft_3_isnullpoint(pln->h))
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
