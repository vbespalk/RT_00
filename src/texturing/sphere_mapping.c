//
// Created by ivoriik on 09.03.19.
//
#include "rt.h"

Uint32		ft_map_sphere(void *fig, t_texture *tex, t_vector hit)
{
	Uint32		col;
	float		theta;
	float		phi;
	int			xy[2];

	hit -= ((t_sphere *)fig)->origin;
	phi = ((t_sphere *)fig)->phi + atan2f(hit[2], hit[0]);
	if (!(IN_RANGE(phi, 0.0f, 2.0f * M_PI)))
		phi = phi < 0.0f ? phi + 2 * (float)M_PI : phi - 2 * (float)M_PI;
	theta = hit[1] / ((t_sphere *)fig)->radius;
	theta = IN_RANGE(theta, -1.0f, 1.0f) ? acosf(theta) : acosf((int)theta);
	theta += ((t_sphere *)fig)->theta;
	if (!(IN_RANGE(theta, 0.0f, M_PI)))
		theta = theta < 0.0f ? theta + (float) M_PI : theta - (float) M_PI;
	xy[0] = (int)((tex->surface->w - 1) * phi / 2.0f * (float)M_1_PI);
	xy[1] = (int)((tex->surface->h - 1) * theta * (float)M_1_PI);
	if (!(IN_RANGE(xy[0], 0, tex->surface->w) &&
		IN_RANGE(xy[1], 0, tex->surface->h)))
		return (0xff);
	ft_memcpy(&col, (Uint32 *)tex->surface->pixels + xy[1] * tex->surface->w
			+ xy[0], sizeof(Uint32));
	return (col);
}
