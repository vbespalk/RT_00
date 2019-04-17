//
// Created by ivoriik on 09.03.19.
//
#include "rt.h"
static Uint32		ft_map_caps(t_cone *cone, t_texture *tex, t_vector hit, float hei)
{
	return (UINT32_MAX);
}

Uint32		ft_map_cone(void *fig, t_texture *tex, t_vector hit)
{
	Uint32		col;
	Uint32 		*ptr;
	float 		hei;
	float		phi;
	int			xy[2];
	float 		p_xy[2];
	t_vector	cross;

	t_cone *cone = ((t_cone *)fig);
	if (((t_cone *)fig)->maxh == FLT_MAX)
		return (UINT32_MAX);
//	printf("Y %f, MIH %f MAXH %f\n", hit[1], -(((t_cone *)fig)->maxh), (((t_cone *)fig)->maxh));
	if (IN_RANGE(hit[1], -1e-4, 1e-4))
	{
//		printf("COORD %f,%f,%f\n", hit[0], hit[1], hit[2]);
		return (ft_map_caps(((t_cone *)fig), tex, hit, hei));
	}
	hei = fabsf(cone->maxh) > fabsf(cone->minh) ?
			fabsf((hit[1]) / cone->maxh) : fabsf((hit[1]) / cone->minh);
//	hit = ft_3_tounitvector(hit - ((t_cone *)fig)->o - ft_3_vector_scale(((t_cone *)fig)->v, hei));
	hit = ft_3_tounitvector(hit);
	phi = atan2f(hit[0], hit[2]);
	if (!(IN_RANGE(phi, 0.0f, 2 * M_PI)))
		phi = phi < 0 ? phi + 2 * (float)M_PI : phi;
	xy[0] = (int)((tex->surface->w - 1) * phi * 0.5f * (float)M_1_PI);
	xy[1] = (int)((tex->surface->h - 1) * (hei));
	ptr = (Uint32 *)tex->surface->pixels;
	if (!(IN_RANGE(xy[0], 0, tex->surface->w) &&
		  IN_RANGE(xy[1], 0, tex->surface->h)))
		return (0xff);
	ft_memcpy(&col, (Uint32 *)tex->surface->pixels + xy[1] * tex->surface->w
					+ xy[0], sizeof(Uint32));
	return (col);
}

Uint32		ft_checker_cone(void *fig, t_chess *tex, t_vector coll)
{
	return (UINT_MAX);
}

Uint32		ft_procedural_cone(void *fig, t_procedural *tex, t_vector coll)
{
	t_cone		*cone;
	t_vector	point;

	cone = (t_cone *)fig;
	if (IN_RANGE(coll[1], -1e-4, 1e-4))
		point = ft_3_vector_scale(coll, 1 / ((cone->minh < cone->maxh &&
		cone->minh > -FLT_MAX ? cone->minh : cone->maxh) * cone->tan));
	else
	{
		point = ft_3_vector_scale(coll, 1 / (150 * cone->tan));
		point[1] = coll[1] / 100;
	}
	return (tex->ft_get_color(tex, NULL, ft_3_vector_scale(point, 1)));
}