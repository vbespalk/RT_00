//
// Created by ivoriik on 12.04.19.
//
#include "rt.h"

Uint32		ft_map_torus(struct s_object *o, t_texture *tex, t_vector coll)
{
	Uint32		col;
	float		theta;
	float		phi;
	int			xy[2];
	t_vector  	cnt;

	coll = ft_3_vector_scale(coll, 1 / ((t_torus *)o->fig)->r_inner);
	phi = atan2f(coll[2], coll[0]);
	if (!(IN_RANGE(phi, 0.0f, 2.0f * M_PI)))
		phi = phi < 0.0f ? phi + 2 * (float)M_PI : phi - 2 * (float)M_PI;
	cnt = coll - ft_3_tounitvector((t_vector)
				{coll[0], FLT_MIN, coll[2]});
	theta = 0.5f * acosf(CLAMP(coll[1], -1, 1));
	if (!(IN_RANGE(theta, 0.0f, M_PI)))
		theta = theta < 0.0f ? theta + (float)M_PI : theta - (float)M_PI;
	if (IN_RANGE(cnt[0] * cnt[0] + cnt[2] * cnt[2], 0, 1))
		theta = (float)M_PI - theta;
	xy[0] = (int)((tex->surface->w - 1) * phi * 0.5f * (float)M_1_PI);
	xy[1] = (int)((tex->surface->h - 1) * theta * (float)M_1_PI);
	if (!(IN_RANGE(xy[0], 0, tex->surface->w) &&
		  IN_RANGE(xy[1], 0, tex->surface->h)))
		return (0xff);
	ft_memcpy(&col, (Uint32 *)tex->surface->pixels + xy[1] * tex->surface->w
					+ xy[0], sizeof(Uint32));
	return (col);
}

Uint32		ft_checker_tor(struct s_object *o, t_checkbrd *tex, t_vector coll)
{
	float		uv[2];
	float		theta;
	float		phi;
	int 		patt;
	t_vector  	cnt;
	t_vector	hit;

	phi = atan2f(coll[2], coll[0]);
	hit = coll;
	coll = ft_3_vector_scale(coll, 1 / ((t_torus *)o->fig)->r_inner);
	cnt = coll - ft_3_tounitvector((t_vector)
		{coll[0], FLT_MIN, coll[2]});
	if (cnt[0] * cnt[0] + cnt[2] * cnt[2] <= 1)
		theta = acosf(-CLAMP(coll[1], -1, 1));
	else
		theta = acosf(CLAMP(coll[1], -1, 1));
	if (!(IN_RANGE(phi, 0.0f, 2.0f * M_PI)))
		phi = phi < 0.0f ? phi + 2 * (float)M_PI : phi - 2 * (float)M_PI;
	uv[0] = (1 + phi * (float)M_1_PI);
	uv[1] = theta * (float)M_1_PI;
	patt = (fmodf(uv[0] * tex->size, 1) > 0.5) ^ (fmodf(uv[1] * tex->size, 1) > 0.5);
	if (patt == 0)
		return (tex->noise[0] ? o->ft_procedural(o, tex->noise[0], hit) : tex->color[0]);
	return (tex->noise[1] ? o->ft_procedural(o, tex->noise[1], hit) : tex->color[1]);
}

Uint32		ft_procedural_tor(struct s_object *o, t_procedural *tex, t_vector coll)
{
	t_torus		*trs;
	t_vector	point;

	trs = (t_torus *)o->fig;
	point = ft_3_vector_scale(coll, 1 / trs->r_inner);
	return (tex->ft_get_color(tex, NULL, ft_3_vector_scale(point, tex->scale)));
}