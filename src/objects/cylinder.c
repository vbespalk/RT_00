/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 13:25:05 by domelche          #+#    #+#             */
/*   Updated: 2018/08/23 13:26:05 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_cylinder	*ft_cylindernew(t_object *o)
{
	t_cylinder	*clnd;

	o->ft_collide = ft_collide_cylinder;
	o->ft_is_inside = ft_is_inside_cylinder;
	o->ft_get_norm = ft_get_norm_cylinder;
	o->ft_translate = ft_translate_cylinder;
	o->ft_rotate = ft_rotate_cylinder;
	o->ft_scale = ft_scale_cylinder;
	o->ft_scale_height = ft_scale_hei_cylinder;
	o->ft_mapping = ft_map_clndr;
	o->ft_checker = ft_checker_cyl;
	o->ft_procedural = ft_procedural_cyl;
	clnd = ft_smemalloc(sizeof(t_cylinder), "ft_cylindernew");
	clnd->r = 10.0f;
	clnd->maxh = FLT_MAX;
	return (clnd);
}

void		*ft_parse_cylinder(char **content, t_object *o)
{
	t_cylinder		*clnd;

	clnd = ft_cylindernew(o);
	ft_get_attr(content, "radius", (void *)(&(clnd->r)), DT_FLOAT);
	ft_get_attr(content, "height", (void *)(&(clnd->maxh)), DT_FLOAT);
	if (clnd->maxh != FLT_MAX)
		clnd->maxh /= clnd->r * 2.f;
	clnd->ratio = clnd->maxh / (clnd->maxh + 2.f);
	ft_3_transform_mat(&(o->transform), o->translate, o->rotate, clnd->r);
	ft_3_inv_trans_mat(&(o->inverse), -o->translate, -o->rotate,
			1.0f / clnd->r);
	return ((void *)clnd);
}
