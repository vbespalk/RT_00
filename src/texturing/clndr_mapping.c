//
// Created by ivoriik on 09.03.19.
//
#include "rt.h"
Uint32		ft_map_caps(t_cylinder *clnd, t_texture *tex, t_vector hit, float hei)
{
	return (UINT32_MAX);
}

Uint32		ft_map_clndr(void *fig, t_texture *tex, t_vector hit)
{
	Uint32		col;
	Uint32 		*ptr;
	float 		hei;
	float		phi;
	int			xy[2];
	float 		p_xy[2];
	t_vector	cross;

	if (((t_cylinder *)fig)->maxh == FLT_MAX)
		return (UINT32_MAX);
	hei = fabsf(ft_3_vector_dot(hit - ((t_cylinder *)fig)->o, ((t_cylinder *)fig)->v));
	if (((t_cylinder *)fig)->maxh != FLT_MAX
		&& !IN_RANGE(hei, 1e-2, ((t_cylinder *)fig)->maxh - 1e-2))
		return (ft_map_caps(((t_cylinder *)fig), tex, hit, hei));
	hit -= (((t_cylinder *)fig)->o + ft_3_vector_scale(((t_cylinder *)fig)->v, hei));
	phi = atan2f(hit[0], hit[2]);
	if (!(IN_RANGE(phi, 0.0f, 2 * M_PI)))
		phi = phi < 0 ? phi + 2 * (float)M_PI : phi;
	xy[0] = (int)((tex->surface->w - 1) * phi * 0.5f * (float)M_1_PI);
	xy[1] = (int)((tex->surface->h - 1) * (1.0f - hei / ((t_cylinder *)fig)->maxh));
	ptr = (Uint32 *)tex->surface->pixels;
	if (!(IN_RANGE(xy[0], 0, tex->surface->w) &&
		  IN_RANGE(xy[1], 0, tex->surface->h)))
		return (0xff);
	ft_memcpy(&col, (Uint32 *)tex->surface->pixels + xy[1] * tex->surface->w
					+ xy[0], sizeof(Uint32));
	return (col);
}

Uint32		ft_checker_cyl(void *fig, t_chess *tex, t_vector coll)
{
	return (UINT_MAX);
}

Uint32		ft_procedural_cyl(void *fig, t_procedural *tex, t_vector coll)
{
	t_cylinder	*cyl;
	float 		hei;
	t_vector	point;
	t_vector	vec;
	float		theta;

	cyl = (t_cylinder *)fig;
	hei = fabsf(ft_3_vector_dot(coll - ((t_cylinder *)fig)->o, ((t_cylinder *)fig)->v));
	point = ft_3_vector_scale(coll - cyl->o, 1.0f / cyl->r);
//	printf("point %f,%f,%f\n", point[0], point[1], point[2]);
//	theta = cyl->theta * 2.0f;
//	point = ft_3_vector_rotate(point, 0, -cyl->phi, theta);
	return (tex->ft_get_color(tex, NULL, point));
}