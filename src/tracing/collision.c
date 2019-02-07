/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 13:21:02 by domelche          #+#    #+#             */
/*   Updated: 2018/08/23 13:25:52 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_vector		ft_get_collision_point
						(t_list *objs, t_object **obj, t_vector od[2])
{
	t_list		*node;
	t_vector	pnt[2];
	float		dist[2];
	t_object	*o;

	node = objs;
	pnt[0] = ft_3_nullpointnew();
	dist[0] = FLT_MAX;
	while (node)
	{
		o = (t_object *)(node->content);
		if (o->ft_is_reachable(o->fig, od[0], od[1]) &&
			!ft_3_isnullpoint(pnt[1] = o->ft_collide(o->fig, od[0], od[1])) &&
			(dist[1] = ft_3_point_point_dist(od[0], pnt[1])) < dist[0])
		{
			pnt[0] = pnt[1];
			dist[0] = dist[1];
			*obj = o;
		}
		node = node->next;
	}
	return (pnt[0]);
}

static void			ft_refract(t_thrarg *arg, t_coll *coll, t_vector direct)
{
	float		refr[2];
	float		cos[2];

	ft_handle_hit(arg->e->scn->hits[arg->i], coll->o, &refr);
	coll->trans_vec = ft_3_vector_refract(coll->norm, direct, refr[0], refr[1]);
	if (ft_3_isnullpoint(coll->trans_vec))
	{
		coll->fresnel = 1.0f;
		return ;
	}
	cos[0] = fabsf(ft_3_vector_cos(direct, coll->norm));
	cos[1] = fabsf(ft_3_vector_cos(coll->trans_vec, coll->norm));

//	printf("norm: (%f, %f, %f); trans: (%f, %f, %f)\n",
//		coll->norm[0], coll->norm[1], coll->norm[2],
//		coll->trans_vec[0], coll->trans_vec[1], coll->trans_vec[2]);

	if (coll->o->spclr)
	{
		coll->fresnel = (powf(
			(refr[1] * cos[0] - refr[0] * cos[1]) /
			(refr[1] * cos[0] + refr[0] * cos[1]),
			2.0f) + powf(
			(refr[0] * cos[1] - refr[1] * cos[0]) /
			(refr[0] * cos[1] + refr[1] * cos[0]),
			2.0f)) / 2.0f;

		//printf("%f\n", coll->fresnel);
	}
}

t_coll				ft_get_collision
						(t_thrarg *arg, t_vector origin, t_vector direct)
{
	t_coll		coll;
	t_vector	od[2];

	coll.o = NULL;
	od[0] = origin + ft_3_vector_scale(direct, 0.5f);
	od[1] = direct;
	if (ft_3_isnullpoint(coll.coll_pnt =
		ft_get_collision_point(arg->e->scn->objs, &(coll.o), od)))
		return (coll);
	coll.norm = coll.o->ft_get_norm(coll.o->fig, coll.coll_pnt);
	coll.fresnel = coll.o->spclr;
	if (ft_3_vector_cos(coll.norm, direct) > 0)
		coll.norm = ft_3_vector_scale(coll.norm, -1);
	if (coll.o->spclr)
		coll.spclr_vec = ft_3_vector_reflect(origin, coll.coll_pnt, coll.norm);
	if (coll.o->trans)
		ft_refract(arg, &coll, direct);
	ft_illuminate(arg, &coll);
	return (coll);
}
