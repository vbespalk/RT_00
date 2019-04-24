//
// Created by ivoriik on 09.03.19.
//
#include "rt.h"

Uint32		ft_map_plane(struct s_object *o, t_texture *tex, t_vector hit)
{
	t_plane		*pln;
	Uint32		col;
	int			xy[2];
	float 		s;
	float 		t;


	pln = (t_plane *)o->fig;
	if (pln->len_wh[0] == FLT_MIN || pln->len_wh[1] == FLT_MIN)
		return (UINT32_MAX);
	s = (ft_3_vector_dot(hit - (t_vector){-pln->ratio, 0, -1}, X_AXIS)) / 2;
	t = 1 - (ft_3_vector_dot(hit - (t_vector){-pln->ratio, 0, -1}, Z_AXIS)) /
			(pln->ratio * 2);
//	printf("LEN %f, s %f, WID %f, t %f\n", pln->len_wh[0], s, pln->len_wh[1], t);
	xy[0] = (int)((tex->surface->w - 1) * s);
	xy[1] = (int)((tex->surface->h - 1) * t);
	if (!(IN_RANGE(xy[0], 0, tex->surface->w) &&
		  IN_RANGE(xy[1], 0, tex->surface->h)))
		return (0xff);
	ft_memcpy(&col, (Uint32 *)tex->surface->pixels + xy[1] * tex->surface->w
					+ xy[0], sizeof(Uint32));
	return (col);
}

Uint32		ft_map_box(struct s_object *o, t_texture *tex, t_vector hit, t_vector tr_hit)
{
	return (UINT32_MAX);
}

Uint32		ft_checker_pln(struct s_object *o, t_checkbrd *tex, t_vector coll)
{
	t_plane		*pln;
	float 		x;
	float 		z;
	t_vector	pnt;

	pln = (t_plane *)o->fig;
	pnt = pln->len_wh[0] == FLT_MIN ? ft_3_vector_scale(coll, 1.0f / o->dist) : coll;
//	printf("coll %f, %f, %f\n", coll[0], coll[1], coll[2]);
	x = (sinf((float)M_PI * pnt[0] * tex->size));
	z = (sinf((float)M_PI * pnt[2] * tex->size));
	if ((x * z < 0))
//		return (tex->color[0]);
//	return (tex->color[1]);
		return (tex->noise[0] ? o->ft_procedural(o, tex->noise[0], pnt) : tex->color[0]);
	return (tex->noise[1] ? o->ft_procedural(o, tex->noise[1], pnt) : tex->color[1]);
}

Uint32		ft_checker_box(struct s_object *o, t_checkbrd *tex, t_vector coll)
{
	return (UINT_MAX);
}

Uint32		ft_procedural_dsk(struct s_object *o, t_procedural *tex, t_vector coll)
{
	coll = ((t_disk *)o->fig)->out_r == FLT_MAX ? ft_3_vector_scale(coll, 1.0f / o->dist) :
			ft_3_vector_scale(coll, 1.0f / ((t_disk *)o->fig)->out_r);
	return (tex->ft_get_color(tex, NULL, ft_3_vector_scale(coll, tex->scale)));
}

Uint32		ft_checker_dsk(struct s_object *o, t_checkbrd *tex, t_vector coll)
{
	t_disk		*dsk;
	float 		uv[2];
	t_vector	tmp;
	int 		patt;
	t_vector	pnt;

	dsk = (t_disk *)o->fig;
	pnt = coll;
	coll = dsk->out_r == FLT_MAX ? ft_3_vector_scale(coll, 1.0f / o->dist) :
			 ft_3_vector_scale(coll, 1.0f / (dsk->out_r));
	uv[0] = (atan2f(coll[2], coll[0]) * M_1_PI + 1);
	uv[1] = sqrtf(coll[2] * coll[2] + coll[0] * coll[0]);
//	printf("uv[1] %f, coll %f,%f,%f\n", pnt[0], pnt[1], pnt[2]);
	patt = (fmodf(uv[0] * tex->size, 1) > 0.5) ^ (fmodf(uv[1] * tex->size, 1) > 0.5);
	if (patt == 0)
		return (tex->noise[0] ? o->ft_procedural(o, tex->noise[0], pnt) : tex->color[0]);
	return (tex->noise[1] ? o->ft_procedural(o, tex->noise[1], pnt) : tex->color[1]);
}

Uint32		ft_procedural_pln(struct s_object *o, t_procedural *tex, t_vector coll)
{
	t_plane	*pln;

	pln = (t_plane *)o->fig;
	coll[0] = pln->len_wh[0] == FLT_MIN ? coll[0] : (coll[0] * pln->len_wh[0]) / pln->len_wh[1];
	return (tex->ft_get_color(tex, NULL, ft_3_vector_scale(coll, tex->scale)));
}