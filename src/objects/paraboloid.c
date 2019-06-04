/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paraboloid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 18:12:39 by vbespalk          #+#    #+#             */
/*   Updated: 2019/02/19 18:12:42 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_prbld		*ft_prbldnew(t_object *o)
{
	t_prbld	*prbl;

	o->ft_collide = ft_collide_prbld;
	o->ft_is_inside = ft_is_inside_prbld;
	o->ft_get_norm = ft_get_norm_prbld;
	o->ft_translate = ft_translate_prbld;
	o->ft_rotate = ft_rotate_prbld;
	o->ft_scale = ft_scale_prbld;
	o->ft_scale_height = ft_scale_hei_prbld;
	o->ft_mapping = ft_map_prbld;
	o->ft_checker = ft_checker_prbld;
	o->ft_procedural = ft_procedural_prbld;
	prbl = ft_smemalloc(sizeof(t_prbld), "ft_prbldnew");
	prbl->r = 1.f;
	prbl->maxh = FLT_MAX;
	return (prbl);
}

char		*ft_parse_prbld(char **content, t_object *o)
{
	t_prbld		*prbl;

	prbl = ft_prbldnew(o);
	ft_get_attr(content, "radius", (void *)(&(prbl->r)), DT_FLOAT);
	ft_get_attr(content, "height", (void *)(&(prbl->maxh)), DT_FLOAT);
	prbl->maxh = prbl->maxh == FLT_MAX ? FLT_MAX : prbl->maxh / prbl->r;
	prbl->ratio = prbl->maxh == FLT_MAX ? FLT_MAX :
			prbl->maxh / ((sqrtf(4.f * prbl->maxh)) + prbl->maxh);
	ft_3_transform_mat(&(o->transform), o->translate, o->rotate, prbl->r);
	ft_3_inv_trans_mat(&(o->inverse), -o->translate, -o->rotate, 1.f / prbl->r);
	return ((void *)prbl);
}
