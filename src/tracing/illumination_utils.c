/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   illumination_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 18:56:09 by domelche          #+#    #+#             */
/*   Updated: 2019/05/25 18:56:11 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static float	ft_affect_transparency(
					t_scene *scn, t_light *l, t_list *o_node, t_vector od[2])
{
	float		t;
	t_object	*obj;
	t_coll		coll;

	obj = (t_object *)(o_node->content);
	ft_bzero(&coll, sizeof(t_coll));
	t = obj->ft_collide(&(scn->objs), obj, &coll, od);
	if (t == FLT_MAX || t <= 0)
		return (1.0f);
	if (l->type != L_POINT
	|| ft_3_vector_cos(od[0] - l->origin, coll.coll_pnt - l->origin) < 0)
		return (obj->trans);
	return (1.0f);
}

float			ft_get_illumination(
					t_scene *scn, t_vector o, t_vector d, t_light *l)
{
	float		res;
	t_list		*o_node;
	t_vector	od[2];

	res = 1.0f;
	o += ft_3_vector_scale(d, SHIFT);
	od[0] = o;
	od[1] = d;
	o_node = scn->objs;
	while (o_node)
	{
		res *= ft_affect_transparency(scn, l, o_node, od);
		if (res == 0.0f)
			return (res);
		o_node = o_node->next;
	}
	return (res);
}

static void		ft_affect_phong(t_coll *coll, t_light *l, float phong_cos)
{
	if (phong_cos > 0.9)
	{
		coll->phong = (float)
			(pow(phong_cos - 0.9f, 2) * coll->o->phong * 100.0f);
		coll->phong_color = ft_add_colors(
			coll->phong_color, ft_scale_color(l->color, coll->phong));
	}
}

void			ft_affect_illumination(
					t_coll *coll, t_light *l, t_vector ldir, float bright_coef)
{
	float		phong_cos;
	int			i;
	t_byte		color_part;

	phong_cos = ft_3_vector_cos(coll->spclr_vec, ldir);
	i = -1;
	while (++i < 3)
	{
		color_part = (t_byte)ft_limit(
			0, 255, (int)(bright_coef * l->color.argb[i]));
		coll->illum_color.argb[i] =
			(255 - coll->illum_color.argb[i] < color_part)
			? (t_byte)(255) : coll->illum_color.argb[i] + color_part;
	}
	ft_affect_phong(coll, l, phong_cos);
}
