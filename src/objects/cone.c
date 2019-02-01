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
	cone->base = ft_3_pointnew(0.0, 0.0, -200.0);
	cone->base_rad = 100;
	cone->vert = ft_3_pointnew(0.0, 0.0, 200.0);
	cone->vert_rad = 100;
	return (cone);
}

void		ft_cone_init(t_object *obj, t_cone *cone)
{
	obj->fig = cone;
	cone->bv_dist = ft_3_point_point_dist(cone->base, cone->vert);
	cone->base = ft_3_vector_add(cone->base, obj->translate);
	cone->vert = ft_3_vector_add(cone->vert, obj->translate);
	cone->bv = ft_3_vector_rotate(ft_3_unitvectornew(cone->base, cone->vert),
		obj->rotate.x, obj->rotate.y, obj->rotate.z);
	cone->vert = ft_3_vector_add(cone->base,
		ft_3_vector_scale(cone->bv, cone->bv_dist));
	cone->side_norm_angle = acos((cone->bv_dist * sin(atan((cone->base_rad -
		cone->vert_rad) / cone->bv_dist))) / (cone->base_rad - cone->vert_rad));
	cone->main_vert = ft_3_vector_add(cone->base, ft_3_vector_scale(cone->bv,
		cone->base_rad * cone->bv_dist / (cone->base_rad - cone->vert_rad)));
}

char		*ft_parse_cone(char *attr, t_scene *scn)
{
	t_object	*obj;
	t_cone		*cone;

	obj = ft_parse_object(attr);
	obj->ft_collide = ft_collide_cone;
	obj->ft_is_reachable = ft_is_reachable_plane;
	obj->ft_is_inside = ft_is_inside_cone;
	obj->ft_get_norm = ft_get_norm_cone;
	cone = ft_conenew();
	attr = ft_get_curve(attr, '{');
	ft_get_attr_in_scope(attr, "base:", (void *)(&(cone->base)), PNT);
	ft_get_attr_in_scope(attr, "base_rad:", (void *)(&(cone->base_rad)), FLT);
	ft_get_attr_in_scope(attr, "vert:", (void *)(&(cone->vert)), PNT);
	ft_get_attr_in_scope(attr, "vert_rad:", (void *)(&(cone->vert_rad)), FLT);
	if (cone->base_rad < 0 && cone->vert_rad < 0)
	{
		cone->base_rad *= -1.0;
		cone->vert_rad *= -1.0;
	}
	ft_cone_init(obj, cone);
	ft_lstpush(&(scn->objs), ft_nodenew((void *)obj, sizeof(obj)));
	return (ft_get_curve(attr, '}'));
}

