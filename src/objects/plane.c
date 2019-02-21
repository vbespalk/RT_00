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
	pln->origin = (t_vector){ 0.0, -1000.0, 0.0 };
	pln->norm = (t_vector){ 0.0, 1.0, 0.0 };
	return (pln);
}


void		*ft_parse_plane(char *content, t_object *o)
{
	t_plane		*pln;

	o->ft_collide = ft_collide_plane;
	o->ft_is_reachable = ft_is_reachable_plane;
	o->ft_is_inside = ft_is_inside_plane;
	o->ft_get_norm = ft_get_norm_plane;
	pln = ft_planenew();
	ft_get_attr(content, "origin", (void *)(&(pln->origin)), DT_POINT);
	ft_get_attr(content, "norm", (void *)(&(pln->norm)), DT_POINT);
	if (ft_3_vector_len(pln->norm) == 0.0)
		pln->norm = (t_vector){ 0.0, 1.0, 0.0 };
	pln->norm = ft_3_tounitvector(pln->norm);
	pln->norm = ft_3_tounitvector(
		ft_3_vector_rotate(
			pln->norm, o->rotate[0], o->rotate[1], o->rotate[2]));
	pln->origin += o->translate;
	return ((void *)pln);
}
