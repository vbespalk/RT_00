//
// Created by ivoriik on 09.03.19.
//
#include "rt.h"

Uint32		ft_map_sphere(struct s_object *o, SDL_Surface *tex, t_vector hit)
{
	Uint32		col;
	float		theta;
	float		phi;
	int			xy[2];
	t_sphere	*sph;

	sph = (t_sphere *)o->fig;
	hit = ft_3_vector_rotate(hit, 0, -sph->phi, 0);
	hit = ft_3_tounitvector(ft_3_vector_rotate(hit, 0, 0, sph->theta));
	phi = atan2f(hit[2], hit[0]);
	if (!(IN_RANGE(phi, 0.0f, 2.0f * M_PI)))
		phi = phi < 0.0f ? phi + 2 * (float)M_PI : phi - 2 * (float)M_PI;
	theta = acosf(CLAMP(hit[1], -1.0f, 1.0f));
	if (!(IN_RANGE(theta, 0.0f, M_PI)))
		theta = theta < 0.0f ? theta + (float) M_PI : theta - (float) M_PI;
	xy[0] = (int)((tex->w - 1) * phi / 2.0f * (float)M_1_PI);
	xy[1] = (int)((tex->h - 1) * theta * (float)M_1_PI);
	if (!(IN_RANGE(xy[0], 0, tex->w) &&
		IN_RANGE(xy[1], 0, tex->h)))
		return (0xff);
	ft_memcpy(&col, (Uint32 *)tex->pixels + xy[1] * tex->w
			+ xy[0], sizeof(Uint32));
	return (col);
}

Uint32		ft_checker_sph(struct s_object *o, t_checkbrd *tex, t_vector coll)
{
	float		uv[2];
	t_sphere	*sph;
	float		theta;
	float		phi;
	int 		patt;

	sph = (t_sphere *)o->fig;
	phi = ((t_sphere *)o->fig)->phi + atan2f(coll[2], coll[0]);
	if (!(IN_RANGE(phi, 0.0f, 2.0f * M_PI)))
		phi = phi < 0.0f ? phi + 2 * (float)M_PI : phi - 2 * (float)M_PI;
	theta = acosf(coll[1]) + ((t_sphere *)o->fig)->theta;
	if (!(IN_RANGE(theta, 0.0f, M_PI)))
		theta = theta < 0.0f ? theta + (float) M_PI : theta - (float) M_PI;
	uv[0] = (1 + phi / (float)M_PI);
	uv[1] = theta / (float)M_PI;
	patt = (fmodf(uv[0] * tex->size, 1) > 0.5) ^ (fmodf(uv[1] * tex->size, 1) > 0.5);
	if (patt == 0)
		return (tex->noise[0] ? o->ft_procedural(o, tex->noise[0], coll) : tex->color[0]);
	return (tex->noise[1] ? o->ft_procedural(o, tex->noise[1], coll) : tex->color[1]);
}

Uint32		ft_procedural_sph(struct s_object *o, t_procedural *tex, t_vector coll)
{
	t_sphere	*sph;
	t_vector	point;
	t_vector	point2;
	float		theta;
	float 		phi;

	sph = (t_sphere *)o->fig;
	phi = sph->phi + atan2f(coll[2], coll[0]);
	if (!(IN_RANGE(phi, 0.0f, 2.0f * M_PI)))
		phi = phi < 0.0f ? phi + 2 * (float)M_PI : phi - 2 * (float)M_PI;
	theta = acosf(coll[1]) + sph->theta;
	if (!(IN_RANGE(theta, 0.0f, M_PI)))
		theta = theta < 0.0f ? theta + (float) M_PI : theta - (float) M_PI;
//	coll[0] = cosf(theta);
//	coll[1] = sinf(phi) * sinf(theta);
//	coll[2] = cosf(phi) * sinf(theta);
//	coll[1] = cosf(theta);
//	coll[2] = sinf(phi) * sinf(theta);
//	coll[0] = cosf(phi) * sinf(theta);
//    theta = sph->theta * 2.0f;
//	coll = ft_3_vector_turn_near(coll, (t_vector){0,0,1}, theta);
	coll = ft_3_vector_turn_near(coll, (t_vector){0,1,0}, -sph->phi);
	return (tex->ft_get_color(tex, NULL, ft_3_vector_scale(coll, tex->scale)));
//	return (tex->ft_get_color(tex, NULL, coll));

}