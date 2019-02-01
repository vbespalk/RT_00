/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   illumination.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 13:25:05 by domelche          #+#    #+#             */
/*   Updated: 2018/08/23 13:26:31 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**	by now, the searching ray would stop if any object will be found
**	(specularity and transparency will be taken into account latter)
*/

int		ft_iscollide
			(t_scene *scn, t_point3 origin, t_point3 direct, t_light *l)
{
	t_list		*o_node;
	t_object	*o;
	t_point3	coll;

	origin = ft_3_vector_add(origin, direct);
	o_node = scn->objs;
	while (o_node)
	{
		o = (t_object *)(o_node->content);
		coll = o->ft_collide(o->fig, origin, direct);
		if (!ft_3_isnullpoint(coll) &&
			(l->type != POINT ||
				ft_3_pointcmp(
					ft_3_unitvectornew(coll, origin),
					ft_3_unitvectornew(l->origin, coll),
					1e-6
				)))
			return (1);
		o_node = o_node->next;
	}
	return (0);
}

void	ft_affect_phong(t_coll *coll, t_light *l, float phong_cos)
{
	if (phong_cos > 0.9)
	{
		coll->phong = (float)
			(pow(phong_cos - 0.9f, 2) * coll->o->phong * 100.0f);
		coll->phong_color = ft_add_colors(coll->phong_color,
			ft_scale_color(l->color, coll->phong));
	}
}

void	ft_affect_illumination
			(t_coll *coll, t_light *l, t_point3 ldir, float norm_light_cos)
{
	float		phong_cos;
	float		cl_len;
	int 		i;
	t_byte		color_part;
	float		bright_koef;

	phong_cos = ft_3_vector_cos(coll->spclr_vec, ldir);
	cl_len = (l->type == POINT) ?
		ft_3_point_point_dist(coll->coll_pnt, l->origin) : 10000.0f;
	bright_koef = (!cl_len) ? l->bright :
		l->bright * norm_light_cos / (float)(pow(cl_len / BRIGHT_UNIT, 2));
	i = -1;
	while (++i < 3)
	{
		color_part = (t_byte)ft_limit(0, 255,
			(int)(bright_koef * l->color.argb[i]));
		coll->illum_color.argb[i] =
			(255 - coll->illum_color.argb[i] < color_part) ? (t_byte)(255) :
				coll->illum_color.argb[i] + color_part;
	}
	ft_affect_phong(coll, l, phong_cos);
}

void	ft_illuminate_with(t_parg *parg, t_coll *coll, t_light *l)
{
	float		norm_light_cos;
	t_point3	ldir;

	ldir = (l->type == POINT) ? ft_3_vectornew(coll->coll_pnt, l->origin) :
		ft_3_vector_scale(l->direct, -1.0);
	norm_light_cos = ft_3_vector_cos(coll->norm, ldir);
	if (norm_light_cos >= 0 &&
		!ft_iscollide(parg->e->scn, coll->coll_pnt, ldir, l))
		ft_affect_illumination(coll, l, ldir, norm_light_cos);
}

void	ft_illuminate(t_parg *parg, t_coll *coll)
{
	t_list		*node;
	t_light		*l;

	coll->illum_color.val = 0;
	coll->phong_color.val = 0;
	coll->phong = 0.0;
	node = parg->e->scn->lights;
	while (node)
	{
		l = (t_light *)(node->content);
		ft_illuminate_with(parg, coll, l);
		node = node->next;
	}
}
