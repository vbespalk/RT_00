//
// Created by Viktoriia BESPALKO on 2019-04-17.
//
#include "rt.h"

static Uint32		ft_map_caps(t_prbld *prbl, t_texture *tex, t_vector hit, float hei)
{
	return (UINT32_MAX);
}

Uint32				ft_map_prbld(struct s_object *o, t_texture *tex, t_vector hit)
{
	Uint32		col;
	Uint32 		*ptr;
	float 		hei;
	float		phi;
	int			xy[2];
	float 		p_xy[2];
	t_vector	cross;

	t_prbld *prbl = ((t_prbld *)o->fig);
	if (((t_prbld *)o->fig)->maxh == FLT_MAX)
		return (UINT32_MAX);
	if (IN_RANGE(hit[1], -1e-6, 1e-6))
		return (ft_map_caps(((t_prbld *)o->fig), tex, hit, hei));
	hei = sqrtf(hit[1] / prbl->maxh);
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

Uint32		ft_procedural_prbld(struct s_object *o, t_procedural *tex, t_vector coll)
{
    t_prbld		*prbl;
    float 		hei;
    t_vector	point;
    t_vector	vec;
    float		theta;

    prbl = (t_prbld *)o->fig;
    float r = coll[1] + prbl->r;
    point = prbl->maxh == FLT_MAX ? ft_3_vector_scale(coll, (1 / sqrtf(o->dist))) :
    		ft_3_vector_scale(coll, (1 / sqrtf(4.0f * prbl->maxh)));
    point[1] = prbl->maxh == FLT_MAX ? coll[1] / sqrtf(o->dist) : coll[1] / (prbl->maxh);
    return (tex->ft_get_color(tex, NULL, ft_3_vector_scale(point, tex->scale)));
}

Uint32		ft_checker_prbld(struct s_object *o, t_checkbrd *tex, t_vector coll)
{
    float		uv[2];
    t_prbld		*prbl;
    float		phi;
    int 		patt;

    prbl = (t_prbld *)o->fig;
	phi = atan2f(coll[2], coll[0]);
	if (!(IN_RANGE(phi, 0.0f, 2.0f * M_PI)))
		phi = phi < 0.0f ? phi + 2 * (float) M_PI : phi - 2 * (float) M_PI;
	if (prbl->maxh != FLT_MAX && IN_RANGE(coll[1], -1e-6, 1e-6))
    {
        uv[0] = (phi / (float) M_PI + 1);
		t_vector pnt = ft_3_vector_scale(coll, (1 / sqrtf(4.0f * prbl->maxh)));
        uv[1] = sqrtf(powf(pnt[2], 2) + powf(pnt[0], 2));
        patt = (fmodf(uv[0] * tex->size, 1) > 0.5) ^ (fmodf(uv[1] * tex->size, 1) > 0.5);
//      return (patt == 0 ? tex->color[0] : tex->color[1]);
		if (patt == 0)
			return (tex->noise[0] ? o->ft_procedural(o, tex->noise[0], coll) : tex->color[0]);
		return (tex->noise[1] ? o->ft_procedural(o, tex->noise[1], coll) : tex->color[1]);
    }
	uv[0] = (phi / (float) M_PI + 1);
	uv[1] = prbl->maxh == FLT_MAX ? coll[1] / sqrtf(o->dist) : sqrtf(coll[1] / prbl->maxh);
	patt = (fmodf(uv[0] * tex->size, 1) > 0.5) ^ (fmodf(uv[1] * tex->size, 1) > 0.5);
	if (patt == 0)
		return (tex->noise[0] ? o->ft_procedural(o, tex->noise[0], coll) : tex->color[0]);
	return (tex->noise[1] ? o->ft_procedural(o, tex->noise[1], coll) : tex->color[1]);
//    return (patt == 0 ? tex->color[0] : tex->color[1]);
}