//
// Created by ivoriik on 09.03.19.
//
#include "rt.h"
static Uint32		ft_map_caps(t_cylinder *clnd, t_texture *tex, t_vector hit, float hei)
{
	return (UINT32_MAX);
}

Uint32		ft_map_clndr(void *fig, t_texture *tex, t_vector hit)
{
	Uint32		col;
	float 		hei;
	float		phi;
	int			xy[2];
	t_cylinder	*clnd;

	clnd = ((t_cylinder *)fig);
	if (((t_cylinder *)fig)->maxh == FLT_MAX)
		return (UINT32_MAX);
	if (!IN_RANGE(hit[1], -clnd->maxh + 1e-4, clnd->maxh - 1e-4))
		return (ft_map_caps(((t_cylinder *)fig), tex, hit, hei));
	hei = (hit[1] + clnd->maxh) / 2.0f;
	phi = atan2f(hit[0], hit[2]);
	if (!(IN_RANGE(phi, 0.0f, 2 * M_PI)))
		phi = phi < 0 ? phi + 2 * (float)M_PI : phi;
	xy[0] = (int)((tex->surface->w - 1) * phi * 0.5f * (float)M_1_PI);
	xy[1] = (int)((tex->surface->h - 1) * (1.0f - hei / ((t_cylinder *)fig)->maxh));
	if (!(IN_RANGE(xy[0], 0, tex->surface->w) &&
		  IN_RANGE(xy[1], 0, tex->surface->h)))
		return (0xff);
	ft_memcpy(&col, (Uint32 *)tex->surface->pixels + xy[1] * tex->surface->w
					+ xy[0], sizeof(Uint32));
	return (col);
}

Uint32		ft_checker_cyl(void *fig, t_chess *tex, t_vector coll)
{
    float		uv[2];
    t_cylinder	*clnd;
    float		hei;
    float		phi;
    int 		patt;

    clnd = (t_cylinder *)fig;
    phi = atan2f(coll[2], coll[0]);
    if (!(IN_RANGE(phi, 0.0f, 2.0f * M_PI)))
        phi = phi < 0.0f ? phi + 2 * (float)M_PI : phi - 2 * (float)M_PI;
    hei = (coll[1] + clnd->maxh) / 2.0f;
    uv[0] = (1 + phi / (float)M_PI);
    uv[1] = hei * 0.6f;
    patt = L_N((fmodf(uv[0] * tex->size, 1) > 0.5) ^ (fmodf(uv[1] * tex->size, 1) > 0.5), 0);
    return (patt == 0 ? tex->color[0] : tex->color[1]);
}

Uint32		ft_procedural_cyl(void *fig, t_procedural *tex, t_vector coll)
{
	t_cylinder	*cyl;
	t_vector	point;

	point = coll;
	return (tex->ft_get_color(tex, NULL, ft_3_vector_scale(point, 1.5)));
}
