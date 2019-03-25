//
// Created by ivoriik on 22.03.19.
//
#include "rt.h"

Uint32		ft_checker_mapping(t_vector hit_p, t_vector o)
{
	t_vector	eps;
	t_vector	xyz;
	Uint32		col;
	int 		size;

	eps = (t_vector){1e-6, 1e-6, 1e-6};
	size = 100;
	xyz = hit_p;
	col = ((int)floorf(xyz[0] / size) + (int)floorf(xyz[1] / size) + (int)floorf(xyz[2] / size)) % 2;
	col = col == 0 ? 0 : 0xffffff;
//	col = (sinf(M_PI * xyz[0] / size) + sinf(M_PI * xyz[1] / size) + sinf(M_PI * xyz[2] / size)) > 0;
//	col = col == 0 ? 0 : 0xffffff;
//	col = (cosf(M_PI * xyz[0] / size) + cosf(M_PI * xyz[1] / size) + cosf(M_PI * xyz[2] / size)) > 0;
//	col = col == 0 ? 0 : 0xffffff;
	return (col);
}

//Uint32		ft_checker_mapping(t_vector hit_p, t_vector o)
//{
//	t_vector	eps;
//	t_vector	xyz;
//	Uint32		col;
//	int 		ix;
//	int 		iz;
//	float 		x;
//	float 		z;
//	int 		size;
//
//	eps = (t_vector){1e-6, 1e-6, 1e-6};
//	size = 100;
////	ix = (int)(floorf(hit_p[0] / size));
////	iz = (int)(floorf(hit_p[2] / size));
//	x = (sinf(M_PI * hit_p[0] / size));
//	z = (sinf(M_PI * hit_p[2] / size));
////	if ((ix + iz) % 2 == 0)
////		return (0);
////	printf("x %d, y %d\n", ix, iz);
//	if ((x * z < 0))
//		return (0);
//	return (0xffffff);
//}

