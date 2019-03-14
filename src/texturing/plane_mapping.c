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
	s = (ft_3_vector_dot(hit - pln->origin, pln->dir_wh[0])) / pln->len_wh[0];
	t = 1 - (ft_3_vector_dot(hit - pln->origin, pln->dir_wh[1])) / pln->len_wh[1];
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

Uint32		ft_map_box(void *fig, t_texture *tex, t_vector hit)
{
	t_box		*bx;

	bx = (t_box *)fig;
	if (bx->fcoll != NULL)
		return (ft_map_plane(bx->fcoll, tex, hit));
	return (UINT32_MAX);
}