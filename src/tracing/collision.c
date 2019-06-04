/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 13:21:02 by domelche          #+#    #+#             */
/*   Updated: 2019/05/24 15:15:07 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ft_init_collision(t_coll *coll, t_list **objs, t_vector *od)
{
	t_list		*node;
	t_coll		tmp_coll;
	float		dist[2];
	t_object	*o;

	node = *objs;
	coll->o = NULL;
	dist[0] = FLT_MAX;
	tmp_coll = *coll;
	while (node)
	{
		o = (t_object *)(node->content);
		dist[1] = o->ft_collide(objs, o, coll, od);
		if (dist[1] < dist[0])
		{
			dist[0] = dist[1];
			tmp_coll = *coll;
		}
		node = node->next;
	}
	*coll = tmp_coll;
}

static void	ft_refract(t_ray *ray)
{
	float		refr[2];
	float		cos[2];

	ft_get_refrs(ray, &refr);
	ray->coll->trans_vec =
		ft_3_vector_refract(ray->coll->norm, ray->d, refr[0], refr[1]);
	if (ft_3_isnullpoint(ray->coll->trans_vec))
	{
		ray->coll->fresnel = 1.0f;
		return ;
	}
	cos[0] = fabsf(ft_3_vector_cos(ray->d, ray->coll->norm));
	cos[1] = fabsf(ft_3_vector_cos(ray->coll->trans_vec, ray->coll->norm));
	if (ray->coll->o->spclr)
	{
		ray->coll->fresnel = (powf(
			(refr[1] * cos[0] - refr[0] * cos[1]) /
			(refr[1] * cos[0] + refr[0] * cos[1]),
			2.0f) + powf(
			(refr[0] * cos[1] - refr[1] * cos[0]) /
			(refr[0] * cos[1] + refr[1] * cos[0]),
			2.0f)) / 2.0f;
	}
}

t_coll		ft_get_collision(t_thrarg *arg, t_ray *ray)
{
	t_coll		coll;
	t_vector	od[2];
	t_fun_tab	func;

	od[0] = ray->o;
	od[1] = ray->d;
	ray->coll = &coll;
	ft_init_collision(&coll, &(arg->e->scn->objs), od);
	if (!(coll.o))
		return (coll);
	if (ft_3_vector_cos(coll.norm, ray->d) > 0)
		coll.norm = ft_3_vector_invert(coll.norm);
	if (coll.o->trans)
		ft_refract(ray);
	if (coll.o->spclr)
		coll.spclr_vec = ft_3_vector_reflect(ray->o, coll.coll_pnt, coll.norm);
	func[1] = coll.tex_o->ft_mapping;
	func[2] = coll.tex_o->ft_checker;
	func[3] = coll.tex_o->ft_procedural;
	coll.px_color.val = (coll.o->exposure == 0) ? coll.o->color.val :
		func[coll.o->exposure](coll.tex_o, coll.o->tex_pnt, coll.ucoll_pnt);
	ft_illuminate(arg, &coll);
	return (coll);
}

int			ft_inside_type(t_list **objs, t_vector point)
{
	int			res;
	t_list		*node;
	t_object	*o;

	res = IT_VOID;
	node = *objs;
	while (node)
	{
		o = (t_object *)(node->content);
		if (o->ft_is_inside(o, point))
		{
			if (o->is_neg)
				return (IT_NEG);
			res = (o->react_neg) ? IT_POS_RT : IT_POS_RF;
		}
		node = node->next;
	}
	return (res);
}

t_object	*ft_get_inner_object(t_list **objs, t_vector point)
{
	t_list		*node;
	t_vector	od[2];
	float		dist[2];
	t_object	*o[2];
	t_coll		coll;

	node = *objs;
	od[0] = point;
	od[1] = (t_vector) { 1.0f, 0.0f, 0.0f };
	dist[0] = FLT_MAX;
	o[1] = NULL;
	while (node)
	{
		o[0] = (t_object *)(node->content);
		o[0]->ft_collide(objs, o[0], &coll, od);
		dist[1] = ft_3_point_point_dist(point, coll.coll_pnt);
		if (dist[1] < dist[0])
		{
			dist[0] = dist[1];
			o[1] = o[0];
		}
		node = node->next;
	}
	return (o[1]);
}
