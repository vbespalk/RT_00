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

float	ft_get_illumination(t_scene *scn, t_vector o, t_vector d, t_light *l)
{
	float		res;
	t_list		*o_node;
	t_object	*obj;
	t_vector	od[2];
	t_coll		coll;
	float 		t;

	res = 1.0f;
	o += ft_3_vector_scale(d, SHIFT);
	od[0] = o;
	od[1] = d;
	o_node = scn->objs;
	while (o_node)
	{
		obj = (t_object *)(o_node->content);
		ft_bzero(&coll, sizeof(t_coll));
		t = obj->ft_collide(&(scn->objs), obj, &coll, od);
		if (t == FLT_MAX || t <= 0)
		{
			o_node = o_node->next;
			continue ;
		}
		if (l->type != L_POINT
		|| ft_3_vector_cos(o - l->origin, coll.coll_pnt - l->origin) < 0)
			res *= obj->trans;
		if (res == 0.0f)
			return (res);
		o_node = o_node->next;
	}
	return (res);
}

void	ft_affect_phong(t_coll *coll, t_light *l, float phong_cos)
{
	if (phong_cos > 0.9)
	{
		coll->phong = (float)
			(pow(phong_cos - 0.9f, 2) * coll->o->phong * 100.0f);
		coll->phong_color = ft_add_colors(
			coll->phong_color, ft_scale_color(l->color, coll->phong));
	}
}

void	ft_affect_illumination
			(t_coll *coll, t_light *l, t_vector ldir, float bright_coef)
{
	float		phong_cos;
	int 		i;
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

void	ft_illuminate_with(t_thrarg *parg, t_coll *coll, t_light *l)
{
	float		nl_cos;
	float		bright_coef;
	float		illum;
	float		cl_len;
	t_vector	ldir;

	ldir = (l->type == L_POINT)
		? ft_3_tounitvector(l->origin - coll->coll_pnt)
		: ft_3_vector_invert(l->direct);
	nl_cos = ft_3_vector_cos(coll->norm, ldir);
	if (nl_cos >= 0)
	{
		illum = ft_get_illumination(
			parg->e->scn, coll->coll_pnt + ft_3_vector_scale(coll->norm, SHIFT),
			ldir, l);
		if (illum == 0.0f)
			return ;
		cl_len = (l->type == L_POINT)
			? ft_3_point_point_dist(coll->coll_pnt, l->origin)
			: 10000.0f;
		bright_coef = (cl_len == 0.0f)
			? l->bright
			: l->bright * illum * nl_cos / powf(cl_len / BRIGHT_UNIT, 2);
		ft_affect_illumination(coll, l, ldir, bright_coef);
	}
}

void	ft_illuminate(t_thrarg *parg, t_coll *coll)
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
