//
// Created by ivoriik on 09.03.19.
//
#include "rt.h"

Uint32		ft_map_plane(void *fig, t_texture *tex, t_vector hit)
{
	t_plane		*pln;
	Uint32		col;
	int			xy[2];
	float 		s;
	float 		t;


	pln = (t_plane *)fig;
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

Uint32		ft_map_box(void *fig, t_texture *tex, t_vector hit, t_vector tr_hit)
{
//	t_box		*bx;
//	t_plane		*pln;
//
//	bx = (t_box *)fig;
//	t_vector pnt = (tr_hit - bx->o);
//	float dot[3];
//	dot[0] = fabsf(ft_3_vector_dot(pnt, pnt));
////	dot[1] = fabsf(ft_3_vector_dot(pnt, (t_vector){0, 1, 0}));
////	dot[2] = fabsf(ft_3_vector_dot(pnt, (t_vector){0, 0, 1}));
//	printf("HIT %f,%f,%f, OR %f,%f,%f VEC %f,%f,%f DOT %f\n", tr_hit[0], tr_hit[1],
//			tr_hit[2], bx->o[0], bx->o[1], bx->o[2], pnt[0], pnt[1], pnt[2], dot[0]);
//	if (dot[0] > dot[1] && dot[0] > dot[2])
//	{
////		printf("NUM 1\n");
//		pln = (t_plane *)bx->face[0]->fig;
//	}
//	else if (dot[0] > dot[1])
//		{
////		printf("NUM 2\n");
//		pln = (t_plane *)bx->face[2]->fig;
//		}
//
//	else
//			{
////		printf("NUM 3\n");
//		pln = (t_plane *)bx->face[1]->fig;
//			}
////	else
////	{
////		printf("NO_COLOR_IN_DA_HOUSE\n");
////		return (UINT32_MAX);
////	}
//	return (ft_map_plane(pln, tex, hit));
}

Uint32		ft_checker_pln(void *fig, t_chess *tex, t_vector coll)
{
	t_plane		*pln;
	t_vector	eps;
	int 		ix;
	int 		iz;
	float 		x;
	float 		z;
	t_vector	tmp;

	if (tex->size == 0)
		tex->size = 1;
	pln = (t_plane *)fig;
//	coll[0] /= (pln->len_wh[1] / pln->len_wh[0]);

//	eps = (t_vector){1e-6, 1e-6, 1e-6};
//	ix = (int)(floorf(coll[1] / tex->size));
//	iz = (int)(floorf(coll[2] / tex->size));
//	if ((ix + iz) % 2 == 0)
//		return (tex->color[0]);
//	printf("COLL %f,%f,%f\n");
	x = (sinf((float)M_PI * coll[0] * tex->size));
	z = (sinf((float)M_PI * coll[2] * tex->size));
	if ((x * z < 0))
		return (tex->color[0]);
	return (tex->color[1]);
}

Uint32		ft_checker_box(void *fig, t_chess *tex, t_vector coll)
{
	return (UINT_MAX);
}

Uint32		ft_procedural_dsc(void *fig, t_procedural *tex, t_vector coll)
{
	t_vector pnt;

	pnt = ft_3_vector_scale(coll, 1.0f / ((t_disk *)fig)->out_r);
	return (tex->ft_get_color(tex, NULL, ft_3_vector_scale(pnt, 10)));
}


Uint32		ft_procedural_pln(void *fig, t_procedural *tex, t_vector coll)
{
	t_plane	*pln;

	pln = (t_plane *)fig;
	coll[0] = (coll[0] * pln->len_wh[0]) / pln->len_wh[1];
	return (tex->ft_get_color(tex, NULL, ft_3_vector_scale(coll, 10)));
}