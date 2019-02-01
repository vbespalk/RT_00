/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 13:25:05 by domelche          #+#    #+#             */
/*   Updated: 2018/08/23 13:27:24 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_plane		*ft_planenew(void)
{
	t_plane	*pln;

	pln = ft_smemalloc(sizeof(t_plane), "ft_planenew");
	pln->origin = ft_3_pointnew(0.0, -1000.0, 0.0);
	pln->norm = ft_3_pointnew(0.0, 1.0, 0.0);
	return (pln);
}


char		*ft_parse_plane(char *attr, t_scene *scn)
{
	t_object	*obj;
	t_plane		*pln;

	obj = ft_parse_object(attr);
	obj->refr = 1.0;
	obj->ft_collide = ft_collide_plane;
	obj->ft_is_reachable = ft_is_reachable_plane;
	obj->ft_is_inside = ft_is_inside_plane;
	obj->ft_get_norm = ft_get_norm_plane;
	pln = ft_planenew();
	attr = ft_get_curve(attr, '{');
	ft_get_attr_in_scope(attr, "origin:", (void *)(&(pln->origin)), PNT);
	ft_get_attr_in_scope(attr, "norm:", (void *)(&(pln->norm)), PNT);
	if (ft_3_vector_len(pln->norm) == 0.0)
		pln->norm = ft_3_pointnew(0.0, 1.0, 0.0);
	pln->norm = ft_3_tounitvector(pln->norm);
	pln->norm = ft_3_tounitvector(ft_3_vector_rotate(pln->norm,
													 obj->rotate.x,
													 obj->rotate.y,
													 obj->rotate.z));
	pln->origin = ft_3_vector_add(pln->origin, obj->translate);
	obj->fig = pln;
	ft_lstpush(&(scn->objs), ft_nodenew((void *)obj, sizeof(obj)));
	return (ft_get_curve(attr, '}'));
}
