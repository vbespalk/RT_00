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

static void			ft_update(
		t_coll *coll,
		t_object **res_o,
		float (*dist)[2],
		t_vector (*pnt)[3])
{
	(*pnt)[0] = coll->ucoll_pnt;
	(*pnt)[1] = coll->coll_pnt;
	(*pnt)[2] = coll->norm;
	(*dist)[0] = (*dist)[1];
	*res_o = coll->o;
}

static void			ft_init(t_coll *coll, t_object *res_o, t_vector pnt[2])
{
	coll->o = res_o;
	coll->ucoll_pnt = pnt[0];
	coll->coll_pnt = pnt[1];
	coll->norm = pnt[2];
}
//static t_vector		ft_get_collision_point
//						(t_list *objs, t_object **obj, t_vector od[2])
static void			ft_init_collision(t_coll *coll, t_list **objs, t_vector *od)
{
	t_list		*node;
	t_vector	pnt[3];
	float		dist[2];
	t_object	*o;
	t_object	*res_o;
	t_object	*tex_o;
//	t_vector	tmp_od[2];

	node = *objs;
	pnt[0] = ft_3_nullpointnew();
	pnt[1] = ft_3_nullpointnew();
	pnt[2] = ft_3_nullpointnew();
	dist[0] = FLT_MAX;
	res_o = NULL;
	tex_o = NULL;
	while (node)
	{
		o = (t_object *)(node->content);
		if (o->ft_is_reachable(o->fig, od[0], od[1]))
		{
			dist[1] = o->ft_collide(objs, o, coll, od);
			if (dist[1] > FLT_MIN && dist[1] < dist[0])
			{
				coll->coll_pnt = od[0] + ft_3_vector_scale(od[1], dist[1]);
				tex_o = coll->tex_o;
				ft_update(coll, &res_o, &dist, &pnt);
			}
		}
		node = node->next;
	}
	ft_init(coll, res_o, pnt);
	coll->tex_o = tex_o;
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
//	if (cos[0] < 0)
//		cos[0] = -cos[0];
//	else
//		ft_swap_float(&refr[0], &refr[1]);
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

//		printf("%f\n", ray->coll->fresnel);
	}
}

t_coll				ft_get_collision(t_thrarg *arg, t_ray *ray)
{
	t_coll		coll;
	t_vector	od[2];
	Uint32		tex_col;

	coll.o = NULL;
	od[0] = ray->o; // + ft_3_vector_scale(ray->d, 0.5f);
	od[1] = ray->d;
	ray->coll = &coll;
	ft_init_collision(&coll, &(arg->e->scn->objs), od);
//	if (ft_3_isnullpoint(coll.coll_pnt =
//		ft_get_collision_point(arg->e->scn->objs, &(coll.o), od)))
//		return (coll);
	if (!(coll.o))
		return (coll);
//	printf("HERE_0\n");
//	coll.norm = coll.o->ft_get_norm(coll.o->fig, coll.coll_pnt);
	if (coll.o->trans)
		ft_refract(arg, ray);
	if (ft_3_vector_cos(coll.norm, ray->d) > 0)
		coll.norm = ft_3_vector_scale(coll.norm, -1.0f);
	if (coll.o->spclr)
		coll.spclr_vec = ft_3_vector_reflect(ray->o, coll.coll_pnt, coll.norm);
	tex_col = coll.tex_o->ft_mapping && coll.o->texture ? coll.tex_o->ft_mapping(coll.tex_o,
			coll.o->texture, coll.ucoll_pnt) : UINT32_MAX;
	if (tex_col != UINT32_MAX)
		coll.px_color.val = tex_col;
	else if (coll.o->checker != NULL)
	{
		coll.px_color.val = coll.tex_o->ft_checker(coll.tex_o, coll.tex_o->checker, coll.ucoll_pnt);
	}
	else if (coll.o->noise != NULL)
	{
		coll.px_color.val = coll.tex_o->ft_procedural(coll.tex_o, coll.o->noise, coll.ucoll_pnt);
	}
	else
        coll.px_color.val = coll.o->color.val;
//	printf("HERE_1\n");
	ft_illuminate(arg, &coll);
	return (coll);
}