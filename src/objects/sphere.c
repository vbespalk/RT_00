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

t_sphere	*ft_spherenew(t_object *o)
{
	t_sphere *sph;

	o->ft_collide = ft_collide_sphere;
	o->ft_is_inside = ft_is_inside_sphere;
	o->ft_get_norm = ft_get_norm_sphere;
	o->ft_translate = ft_translate_sphere;
	o->ft_rotate = ft_rotate_sphere;
	o->ft_scale = ft_scale_sphere;
	o->ft_scale_height = ft_scale_sphere;
	o->ft_mapping = ft_map_sphere;
	o->ft_checker = ft_checker_sph;
	o->ft_procedural = ft_procedural_sph;
	sph = ft_smemalloc(sizeof(t_sphere), "ft_spherenew");
	sph->radius = 100.0f;
	sph->phi = 0.0f;
	sph->theta = 0.0f;
	return (sph);
}

void		*ft_parse_sphere(char **content, t_object *o)
{
	t_sphere	*sph;

	sph = ft_spherenew(o);
	ft_get_attr(content, "radius", (void *)(&(sph->radius)), DT_FLOAT);
	ft_3_transform_mat(&(o->transform), o->translate, ft_3_nullpointnew(),
			sph->radius);
	ft_3_inv_trans_mat(&(o->inverse), -o->translate, ft_3_nullpointnew(),
			1.0f / sph->radius);
	return ((void *)sph);
}

int			ft_translate_sphere(Uint32 key, t_object *o, t_matrix *tr_m,
														t_matrix *inv_m)
{
	t_sphere	*sph;

	if (!o)
		return (0);
	sph = (t_sphere *)o->fig;
	if (key == SDLK_d)
		o->translate[2] += TRANS_F;
	if (key == SDLK_a)
		o->translate[2] -= TRANS_F;
	if (key == SDLK_w)
		o->translate[1] += TRANS_F;
	if (key == SDLK_s)
		o->translate[1] -= TRANS_F;
	if (key == SDLK_e)
		o->translate[0] += TRANS_F;
	if (key == SDLK_q)
		o->translate[0] -= TRANS_F;
	ft_3_transform_mat(tr_m, o->translate, ft_3_nullpointnew(),
			sph->radius);
	ft_3_inv_trans_mat(inv_m, -o->translate, ft_3_nullpointnew(),
			1.f / sph->radius);
	return (1);
}

int			ft_rotate_sphere(Uint32 key, t_object *o, t_matrix *tr_m,
													t_matrix *inv_m)
{
	t_sphere *sph;

	if (!o)
		return (0);
	(void)tr_m;
	(void)inv_m;
	sph = (t_sphere *)o->fig;
	if (key == SDLK_DOWN || key == SDLK_UP)
		o->rotate[2] += key == SDLK_UP ? ROTAT_F : -ROTAT_F;
	else if (key == SDLK_LEFT || key == SDLK_RIGHT)
		o->rotate[1] += key == SDLK_LEFT ? ROTAT_F : -ROTAT_F;
	else if (key == SDLK_PAGEDOWN || key == SDLK_PAGEUP)
		o->rotate[0] += key == SDLK_PAGEUP ? -0.5f * ROTAT_F : 0.5f * ROTAT_F;
	return (1);
}

int			ft_scale_sphere(Uint32 key, t_object *o, t_matrix *tr_m,
													t_matrix *inv_m)
{
	t_sphere	*sph;
	float		scale;

	if (!o)
		return (0);
	sph = (t_sphere *)o->fig;
	scale = (key == SDLK_z || key == SDLK_r) ? 1.f + SCALE_F : 1.f - SCALE_F;
	sph->radius *= scale;
	ft_3_transform_mat(tr_m, o->translate, ft_3_nullpointnew(), sph->radius);
	ft_3_inv_trans_mat(inv_m, -o->translate, ft_3_nullpointnew(),
			1.f / sph->radius);
	return (1);
}
