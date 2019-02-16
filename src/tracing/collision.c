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

static void			ft_refract(t_thrarg *arg, t_ray *ray)
{
	float		refr[2];
	float		cos[2];

	ft_get_refrs(ray, &refr);
	ray->coll->trans_vec =
		ft_3_vector_refract(ray->coll->norm, ray->d, refr[0], refr[1]);
	if (ft_3_isnullpoint(ray->coll->trans_vec))
	{
//		printf("full reflection\n");
		ray->coll->fresnel = 1.0f;
		return ;
	}
	cos[0] = fabsf(ft_3_vector_cos(ray->d, ray->coll->norm));
	cos[1] = fabsf(ft_3_vector_cos(ray->coll->trans_vec, ray->coll->norm));

//	printf("norm: (%f, %f, %f); trans: (%f, %f, %f)\n",
//		coll->norm[0], coll->norm[1], coll->norm[2],
//		coll->trans_vec[0], coll->trans_vec[1], coll->trans_vec[2]);

	if (ray->coll->o->spclr)
	{
		ray->coll->fresnel = (powf(
			(refr[1] * cos[0] - refr[0] * cos[1]) /
			(refr[1] * cos[0] + refr[0] * cos[1]),
			2.0f) + powf(
			(refr[0] * cos[1] - refr[1] * cos[0]) /
			(refr[0] * cos[1] + refr[1] * cos[0]),
			2.0f)) / 2.0f;

		//printf("%f\n", coll->fresnel);
	}
}

t_coll				ft_get_collision(t_thrarg *arg, t_ray *ray)
{
	t_coll		coll;
	t_vector	od[2];

	coll.o = NULL;
	od[0] = ray->o + ft_3_vector_scale(ray->d, 0.5f);
	od[1] = ray->d;
	if (ft_3_isnullpoint(coll.coll_pnt =
		ft_get_collision_point(arg->e->scn->objs, &(coll.o), od)))
		return (coll);
	coll.norm = coll.o->ft_get_norm(coll.o->fig, coll.coll_pnt);
	if (ft_3_vector_cos(coll.norm, ray->d) > 0)
		coll.norm = ft_3_vector_scale(coll.norm, -1.0f);
	if (coll.o->spclr)
		coll.spclr_vec = ft_3_vector_reflect(ray->o, coll.coll_pnt, coll.norm);
	if (coll.o->trans)
		ft_refract(arg, ray);
	ft_illuminate(arg, &coll);
	return (coll);
}
