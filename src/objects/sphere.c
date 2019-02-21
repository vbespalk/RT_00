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
	sph->origin = (t_vector){ 0.0f, 0.0f, 0.0f };
	sph->radius = 100.0f;
	return (sph);
}

void		*ft_parse_sphere(char *content, t_object *o)
{
	t_sphere	*sph;

	o->ft_collide = ft_collide_sphere;
	o->ft_is_reachable = ft_is_reachable_sphere;
	o->ft_is_inside = ft_is_inside_sphere;
	o->ft_get_norm = ft_get_norm_sphere;
	sph = ft_spherenew();
	ft_get_attr(content, "origin:", (void *)(&(sph->origin)), DT_POINT);
	ft_get_attr(content, "radius:", (void *)(&(sph->radius)), DT_FLOAT);
	sph->radius = (float)ft_limitf(0.0f, FLT_MAX, sph->radius);
	sph->origin += o->translate;
	return ((void *)sph);
}

