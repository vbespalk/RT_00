/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 13:25:05 by domelche          #+#    #+#             */
/*   Updated: 2018/08/23 13:25:05 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_sphere	*ft_spherenew(void)
{
	t_sphere	*sph;

	sph = ft_smemalloc(sizeof(t_sphere), "ft_spherenew");
	sph->origin_ini = (t_vector){ 0.0f, 0.0f, 0.0f };
	sph->radius_ini = 100.0f;
	return (sph);
}

void		*ft_parse_sphere(char **content, t_object *o)
{
	t_sphere	*sph;

	o->ft_collide = ft_collide_sphere;
	o->ft_is_reachable = ft_is_reachable_sphere;
	o->ft_is_inside = ft_is_inside_sphere;
	o->ft_get_norm = ft_get_norm_sphere;
	o->ft_translate = ft_translate_sphere;
	o->ft_rotate = ft_rotate_sphere;
	o->ft_scale = ft_scale_sphere;
	sph = ft_spherenew();
	ft_get_attr(content, "origin", (void *)(&(sph->origin_ini)), DT_POINT);
	ft_get_attr(content, "radius", (void *)(&(sph->radius_ini)), DT_FLOAT);
	sph->radius_ini = (float)ft_limitf(0.0f, FLT_MAX, sph->radius_ini);
	sph->origin_ini += o->translate;
	sph->radius = sph->radius_ini;
	sph->origin = sph->origin_ini;
	sph->min_phi = 0.0f;
	sph->max_phi = (float)M_PI * 2.0f;
	sph->min_thcos = acosf(0);
	sph->max_thcos = acosf((float)M_PI);
	return ((void *)sph);
}

void		ft_translate_sphere(Uint32 key, void *fig, t_vector *transl)
{
	t_sphere	*sph;

	sph = (t_sphere *)fig;
	if (!fig)
		return ;
		if (key == SDLK_d)
		(*transl)[2] += TRANS_F;
	if (key == SDLK_a)
		(*transl)[2] -= TRANS_F;
	if (key == SDLK_w)
		(*transl)[1] += TRANS_F;
	if (key == SDLK_s)
		(*transl)[1] -= TRANS_F;
	if (key == SDLK_e)
		(*transl)[0] += TRANS_F;
	if (key == SDLK_q)
		(*transl)[0] -= TRANS_F;
	sph->origin = sph->origin_ini + *(transl);
}

void		ft_rotate_sphere(Uint32 key, void *fig, t_vector *rot)
{
	t_sphere *sph;

	sph = (t_sphere *)fig;
	(void)key;
	if (!fig)
		return ;
}

void		ft_scale_sphere(Uint32 key, void *fig, float *scale)
{
	t_sphere *sph;
	sph = (t_sphere *)fig;
	if (!fig)
		return ;
	if (key == SDLK_z)
		*scale += SCALE_F;
	else if (key == SDLK_x && *scale >= 0.0f)
		*scale -= SCALE_F;
	else
		*scale = 0;
	sph->radius = sph->radius_ini * *scale;
}
