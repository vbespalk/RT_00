/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 13:25:05 by domelche          #+#    #+#             */
/*   Updated: 2018/08/23 13:26:05 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_cone		*ft_conenew(void)
{
	t_cone	*cone;

	cone = ft_smemalloc(sizeof(t_cone), "ft_conenew");
	cone->base = (t_vector){ 0.0f, 0.0f, -200.0f };
	cone->base_rad = 100;
	cone->vert = (t_vector){ 0.0f, 0.0f, 200.0f };
	cone->vert_rad = 100;
	return (cone);
}

void		ft_cone_init(t_object *o, t_cone *cone)
{
	cone->bv_dist = ft_3_point_point_dist(cone->base, cone->vert);
	cone->base += o->translate;
	cone->vert += o->translate;
	cone->bv = ft_3_vector_rotate(
		ft_3_unitvectornew(cone->base, cone->vert),
		o->rotate[0], o->rotate[1], o->rotate[2]);
	cone->vert = cone->base + ft_3_vector_scale(cone->bv, cone->bv_dist);
	cone->side_norm_angle = acosf(
		(cone->bv_dist * sinf(atanf((cone->base_rad - cone->vert_rad) /
			cone->bv_dist))) / (cone->base_rad - cone->vert_rad));
	cone->main_vert = cone->base + ft_3_vector_scale(
		cone->bv,
		cone->base_rad * cone->bv_dist / (cone->base_rad - cone->vert_rad));
}

void		*ft_parse_cone(char **content, t_object *o)
{
	t_cone		*cone;

	o->ft_collide = ft_collide_cone;
	o->ft_is_reachable = ft_is_reachable_plane;
	o->ft_is_inside = ft_is_inside_cone;
	o->ft_get_norm = ft_get_norm_cone;
	cone = ft_conenew();
	ft_get_attr(content, "base", (void *)(&(cone->base)), DT_POINT);
	ft_get_attr(content, "base_rad", (void *)(&(cone->base_rad)), DT_FLOAT);
	ft_get_attr(content, "vert", (void *)(&(cone->vert)), DT_POINT);
	ft_get_attr(content, "vert_rad", (void *)(&(cone->vert_rad)), DT_FLOAT);
	if (cone->base_rad < 0 && cone->vert_rad < 0)
	{
		cone->base_rad *= -1.0f;
		cone->vert_rad *= -1.0f;
	}
	ft_cone_init(o, cone);
	return ((void *)cone);
}

