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

char		*ft_parse_sphere(char *attr, t_scene *scn, unsigned int id)
{
	t_object	*obj;
	t_sphere	*sph;

	obj = ft_parse_object(attr);
	obj->id = id;
	obj->ft_collide = ft_collide_sphere;
	obj->ft_is_reachable = ft_is_reachable_sphere;
	obj->ft_is_inside = ft_is_inside_sphere;
	obj->ft_get_norm = ft_get_norm_sphere;
	obj->ft_translate = ft_translate_sphere;
	obj->ft_rotate = ft_rotate_sphere;
	obj->ft_scale = ft_scale_sphere;
	sph = ft_spherenew();
	attr = ft_get_curve(attr, '{');
	ft_get_attr_in_scope(attr, "origin:", (void *)(&(sph->origin_ini)), PNT);
	ft_get_attr_in_scope(attr, "radius:", (void *)(&(sph->radius_ini)), FLT);
	sph->radius_ini = (float)ft_limitf(0.0f, FLT_MAX, sph->radius_ini);
	sph->origin_ini += obj->translate;
	sph->radius = sph->radius_ini;
	sph->origin = sph->origin_ini;
	obj->fig = sph;
	ft_lstpush(&(scn->objs), ft_nodenew((void *)obj, sizeof(obj)));
	return (ft_get_curve(attr, '}'));
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
