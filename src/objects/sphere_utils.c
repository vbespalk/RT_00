
#include "rt.h"

int			ft_is_reachable_sphere(void *fig, t_point3 origin, t_point3 direct)
{
	t_sphere	*sph;
	float		cos;

	sph = (t_sphere *)fig;
	if (ft_3_point_point_dist(origin, sph->origin) <= sph->radius)
		return (1);
	cos = ft_3_vector_cos(direct, ft_3_vectornew(origin, sph->origin));
	return ((cos > 0) ? 1 : 0);
}

t_point3	ft_collide_sphere(void *fig, t_point3 origin, t_point3 direct)
{
	t_sphere	*sph;
	float		res[3];
	t_point3	coll_points[2];

	sph = (t_sphere *)fig;
	if (ft_3_line_point_dist(origin, direct, sph->origin) > sph->radius)
		return (ft_3_nullpointnew());
	ft_solve_sqr((pow(direct.x, 2) + pow(direct.y, 2) + pow(direct.z, 2)), 2.0 *
		(direct.x * (origin.x - sph->origin.x) + direct.y * (origin.y -
			sph->origin.y) + direct.z * (origin.z - sph->origin.z)),
		(pow(origin.x - sph->origin.x, 2) + pow(origin.y - sph->origin.y, 2) +
		pow(origin.z - sph->origin.z, 2) - pow(sph->radius, 2)), &res);
	if (!res[0])
		return (ft_3_nullpointnew());
	coll_points[0] = (res[1] > 0) ? ft_3_vector_add(origin,
		ft_3_vector_scale(direct, res[1])) : ft_3_nullpointnew();
	coll_points[1] = (res[2] > 0) ? ft_3_vector_add(origin,
		ft_3_vector_scale(direct, res[2])) : ft_3_nullpointnew();
	coll_points[0] = (ft_3_isnullpoint(coll_points[0]) ||
		(res[1] > res[2] && res[2] > 0)) ? coll_points[1] : coll_points[0];
	return (coll_points[0]);
}

int			ft_is_inside_sphere(void *fig, t_point3 point)
{
	t_sphere	*sph;

	sph = (t_sphere *)fig;
	return ((ft_3_point_point_dist(sph->origin, point) < sph->radius) ? 1 : 0);
}

t_point3	ft_get_norm_sphere(void *fig, t_point3 coll)
{
	return (ft_3_unitvectornew(((t_sphere *)fig)->origin, coll));
}
