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

t_cone		*ft_conenew(t_object *o)
{
	t_cone	*cone;

	o->ft_collide = ft_collide_cone;
	o->ft_is_inside = ft_is_inside_cone;
	o->ft_get_norm = ft_get_norm_cone;
	o->ft_translate = ft_translate_cone;
	o->ft_rotate = ft_rotate_cone;
	o->ft_scale = ft_scale_cone;
	o->ft_scale_height = ft_scale_hei_cone;
	o->ft_mapping = ft_map_cone;
	o->ft_checker = ft_checker_cone;
	o->ft_procedural = ft_procedural_cone;
	cone = ft_smemalloc(sizeof(t_cone), "ft_conenew");
	cone->tan = 90;
	cone->minh = -FLT_MAX;
	cone->maxh = FLT_MAX;
	cone->r[0] = FLT_MIN;
	cone->r[1] = FLT_MIN;
	return (cone);
}

void		*ft_parse_cone(char **content, t_object *o)
{
	t_cone		*cone;

	cone = ft_conenew(o);
	ft_get_attr(content, "minh", (void *)(&(cone->minh)), DT_FLOAT);
	ft_get_attr(content, "maxh", (void *)(&(cone->maxh)), DT_FLOAT);
	ft_get_attr(content, "angle", (void *)(&(cone->tan)), DT_FLOAT);
	if (cone->minh > cone->maxh)
		ft_swap_float(&cone->minh, &cone->maxh);
	cone->minh = cone->minh == cone->maxh ? -FLT_MAX : cone->minh;
	cone->maxh = cone->minh == cone->maxh ? FLT_MAX : cone->maxh;
	if ((cone->tan = fabsf(cone->tan)) >= 175)
		cone->tan = (int)cone->tan % 175;
	cone->tan = cone->tan < 1 ? tanf(DEG_TO_RAD(1)) :
			tanf(DEG_TO_RAD(cone->tan / 2.0f));
	cone->sq_tan = cone->tan * cone->tan + 1;
	cone->r[0] = (cone->minh == -FLT_MAX || cone->minh == 0) ?
				FLT_MIN : fabsf(cone->minh * cone->tan);
	cone->r[1] = (cone->maxh == FLT_MAX || cone->maxh == 0) ?
				FLT_MIN : fabsf(cone->maxh * cone->tan);
	if (!(cone->minh == -FLT_MAX || cone->maxh == FLT_MAX))
		cone->texh = sqrtf(powf(cone->maxh - cone->minh, 2) +
			powf(cone->r[1] - cone->r[0], 2)) + cone->r[0] + cone->r[1];
	ft_3_transform_mat(&(o->transform), o->translate, o->rotate, FLT_MIN);
	ft_3_inv_trans_mat(&(o->inverse), -o->translate, -o->rotate, FLT_MIN);
	return ((void *)cone);
}
