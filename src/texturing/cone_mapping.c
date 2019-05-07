//
// Created by ivoriik on 09.03.19.
//
#include "rt.h"
static Uint32		ft_map_caps(t_cone *cone, SDL_Surface *tex, t_vector hit, float hei)
{
	return (UINT32_MAX);
}

Uint32		ft_map_cone(struct s_object *o, SDL_Surface *tex, t_vector hit)
{
	Uint32		col;
	Uint32 		*ptr;
	float 		hei;
	float		phi;
	int			xy[2];
	float 		p_xy[2];
	t_vector	cross;

	t_cone *cone = ((t_cone *)o->fig);
	if (((t_cone *)o->fig)->maxh == FLT_MAX)
		return (UINT32_MAX);
//	printf("Y %f, MIH %f MAXH %f\n", hit[1], -(((t_cone *)o->fig)->maxh), (((t_cone *)o->fig)->maxh));
	if (IN_RANGE(hit[1], -1e-1, 1e-1))
	{
//		printf("COORD %f,%f,%f\n", hit[0], hit[1], hit[2]);
		return (ft_map_caps(((t_cone *)o->fig), tex, hit, hei));
	}
	hei = fabsf(cone->maxh) > fabsf(cone->minh) ?
			fabsf((hit[1]) / cone->maxh) : fabsf((hit[1]) / cone->minh);
	hit = ft_3_tounitvector(hit);
	phi = atan2f(hit[0], hit[2]);
	if (!(IN_RANGE(phi, 0.0f, 2 * M_PI)))
		phi = phi < 0 ? phi + 2 * (float)M_PI : phi;
	xy[0] = (int)((tex->w - 1) * phi * 0.5f * (float)M_1_PI);
	xy[1] = (int)((tex->h - 1) * (hei));
	ptr = (Uint32 *)tex->pixels;
	if (!(IN_RANGE(xy[0], 0, tex->w) &&
		  IN_RANGE(xy[1], 0, tex->h)))
		return (0xff);
	ft_memcpy(&col, (Uint32 *)tex->pixels + xy[1] * tex->w
					+ xy[0], sizeof(Uint32));
	return (col);
}

Uint32		ft_checker_cone(struct s_object *o, t_checkbrd *tex, t_vector coll)
{
	float		uv[2];
	t_cone		*cone;
	float		phi;
	int 		patt;
	float 		r;

	cone = (t_cone *)o->fig;
	phi = atan2f(coll[2] / cone->tan, coll[0] / cone->tan);
	if (!(IN_RANGE(phi, 0.0f, 2.0f * M_PI)))
		phi = phi < 0.0f ? phi + 2 * (float) M_PI : phi - 2 * (float) M_PI;
	uv[0] = (phi / (float) M_PI + 1);
	r = cone->r[0] < cone->r[1] && cone->r[1] != FLT_MIN ? cone->r[1] : cone->r[0];
    if (cone->minh != -FLT_MAX || cone->maxh != FLT_MAX)
	{
		if (IN_RANGE(coll[1], -1e-1, 1e-1))
			uv[1] = sqrtf(powf(coll[2] / r, 2) + powf(coll[0] / r, 2));
		else
			uv[1] = cone->minh < cone->maxh && cone->maxh != FLT_MAX ?
					fabsf(coll[1] / cone->maxh) : fabsf(coll[1] / cone->minh);
	}
	else
		uv[1] =  fabsf(coll[1] / o->dist);
	patt = (fmodf(uv[0] * tex->size, 1) > 0.5) ^ (fmodf(uv[1] * tex->size, 1) > 0.5);
	if (patt == 0)
		return (tex->noise[0] ? o->ft_procedural(o, tex->noise[0], coll) : tex->color[0]);
	return (tex->noise[1] ? o->ft_procedural(o, tex->noise[1], coll) : tex->color[1]);
}

Uint32		ft_procedural_cone(struct s_object *o, t_procedural *tex, t_vector coll)
{
	t_cone		*cone;
	t_vector	point;
	float 		r;

	cone = (t_cone *)o->fig;
	r = cone->r[0] < cone->r[1] &&
		 cone->r[1] != FLT_MIN ? cone->r[1] : cone->r[0];
//	printf("R %f, 0 %f, 1 %f\n", r, cone->r[0], cone->r[1]);
	if ((cone->minh != -FLT_MAX || cone->maxh != FLT_MAX) && IN_RANGE(coll[1], -1e-1, 1e-1))
		point = ft_3_vector_scale(coll, 1.f / r);
	else if (cone->minh == -FLT_MAX && cone->maxh == FLT_MAX)
	{
		point = ft_3_vector_scale(coll, 1 / (o->dist * 1.5f * cone->tan));
		point[1] = coll[1] / o->dist;
	}
	else
	{
		point = ft_3_vector_scale(coll, 1 / r);
		point[1] = coll[1] / (cone->minh < cone->maxh &&
				cone->minh > -FLT_MAX ? cone->maxh : cone->minh);
	}
	return (tex->ft_get_color(tex, NULL, ft_3_vector_scale(point, tex->scale)));
}