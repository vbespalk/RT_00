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
	sph->origin = ft_3_pointnew(0.0, 0.0, 0.0);
	sph->radius = 100.0;
	return (sph);
}

char		*ft_parse_sphere(char *attr, t_scene *scn)
{
	t_object	*obj;
	t_sphere	*sph;

	obj = ft_parse_object(attr);
	obj->ft_collide = ft_collide_sphere;
	obj->ft_is_reachable = ft_is_reachable_sphere;
	obj->ft_is_inside = ft_is_inside_sphere;
	obj->ft_get_norm = ft_get_norm_sphere;
	sph = ft_spherenew();
	attr = ft_get_curve(attr, '{');
	ft_get_attr_in_scope(attr, "origin:", (void *)(&(sph->origin)), PNT);
	ft_get_attr_in_scope(attr, "radius:", (void *)(&(sph->radius)), FLT);
	sph->radius = (float)ft_limitf(0.0f, FLT_MAX, sph->radius);
	sph->origin = ft_3_vector_add(sph->origin, obj->translate);
	obj->fig = sph;
	ft_lstpush(&(scn->objs), ft_nodenew((void *)obj, sizeof(obj)));
	return (ft_get_curve(attr, '}'));
}

