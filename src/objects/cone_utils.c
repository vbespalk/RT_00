/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:33:06 by vbespalk          #+#    #+#             */
/*   Updated: 2019/02/20 12:33:12 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int			ft_solve_sqr_(float a, float b, float c, float (*res)[2])
{
	float	d;

	d = (float)pow(b, 2) - 4.0f * a * c;
	if (d < 0)
		return (0);
	d = sqrtf(d);
	(*res)[0] = (-b + d) / (2.0f * a);
	(*res)[1] = (-b - d) / (2.0f * a);
	if (((*res)[0] > (*res)[1] && (*res)[1] > FLT_MIN) || (*res)[0] < FLT_MIN)
		ft_swap_float(&(*res)[0], &(*res)[1]);
	return (1);
}

static float	get_closer_pnt(const float *t, const t_vector *hit, t_coll *coll, t_object *obj)
{
	coll->o = obj;
	coll->tex_o = obj;
	if ((t[0] < t[1] || t[1] < 0) && t[0] > 0)
	{
		coll->ucoll_pnt = hit[0];
		coll->norm = ft_3_tounitvector(ft_3_norm_transform(&(obj->inverse), coll->ucoll_pnt -
			ft_3_vector_scale((t_vector){0, coll->ucoll_pnt[1], 0},
			(((t_cone *)obj->fig)->tan) * (((t_cone *)obj->fig)->tan) + 1)));
		return (t[0]);
	}
	else if (t[1] > 0)
	{
		coll->ucoll_pnt = hit[1];
		coll->norm = ft_3_tounitvector(ft_3_norm_transform(&(obj->inverse), (t_vector) {0, 1, 0}));
		return (t[1]);
	}
	return (-FLT_MAX);
}
//
///*
//** ADD 1e-1 TO t TO AVOID MISSES BETW SIDES AND CAPS
//*/
//
static float	get_cides_coll(const t_vector *od, float *t, t_vector *coll, t_cone *cone)
{
	t_vector	hit[2];

	if (t[0] < FLT_MIN && t[1] < FLT_MIN)
		return (-FLT_MAX);
	hit[0] = od[0] + ft_3_vector_scale(od[1], t[0]);
	if (cone->maxh == FLT_MAX && cone->minh == FLT_MIN)
	{
		*coll = hit[0];
		return (t[0]);
	}
	hit[1] = od[0] + ft_3_vector_scale(od[1], t[1]);
	if (t[0] >= FLT_MIN && IN_RANGE(hit[0][1], cone->minh, cone->maxh))
	{
		*coll = hit[0];
		return (t[0]);
	}
	else if (t[1] >= FLT_MIN && IN_RANGE(hit[1][1], cone->minh, cone->maxh))
	{
		*coll = hit[1];
		return (t[1]);
	}
	return (-FLT_MAX);
}

static float	get_caps_coll(const t_vector *od, t_vector *coll, t_cone *cone)
{
	float 		t[2];
	t_vector	ori[2];
	t_vector	hit[2];
	float 		sq_r[2];

	ori[0] = od[0] - (t_vector){FLT_MIN, cone->minh, FLT_MIN};
	ori[1] = od[0] - (t_vector){FLT_MIN, cone->maxh, FLT_MIN};
	t[0] = cone->minh == -FLT_MAX ? -FLT_MAX : -(ori[0][1]) / od[1][1];
	t[1] = cone->maxh == FLT_MAX ? -FLT_MAX : -(ori[1][1]) / od[1][1];
	sq_r[0] = cone->r[0] * cone->r[0];
	sq_r[1] = cone->r[1] * cone->r[1];
	if (t[0] < FLT_MIN && t[1] < FLT_MIN)
		return (-FLT_MAX);
	(t[0] > t[1] && t[1] > FLT_MIN) || t[0] < FLT_MIN ? ft_swap_float(&t[0], &t[1]),
			ft_swap(&ori[0], &ori[1], sizeof(t_vector)),
			ft_swap_float(&sq_r[0], &sq_r[1]): 1;
	hit[0] = ori[0] + ft_3_vector_scale(od[1], t[0]);
	hit[1] = ori[1] + ft_3_vector_scale(od[1], t[1]);
//	printf("1. T %f, r %f, sq_r %f, 2. T %f, r %f, sq_r %f\n",
//			t[0], ft_3_vector_dot(hit[0], hit[0]), sq_r[0],
//			t[1], ft_3_vector_dot(hit[1], hit[1]), sq_r[1]);
	if (t[0] > FLT_MIN && ft_3_vector_dot(hit[0], hit[0]) < sq_r[0])
	{
		*coll = hit[0];
		return (t[0]);
	}
	else if (t[1] > FLT_MIN && ft_3_vector_dot(hit[1], hit[1]) < sq_r[1])
	{
//		*coll = hit[1] - cone->maxh;
		*coll = hit[1];
		return (t[1]);
	}
//	printf("MINH %f, R %f, MAXH %f, R %f\n", cone->minh, sq_r[0], cone->maxh, sq_r[1]);
	return (-FLT_MAX);
}

int					ft_is_reachable_cone(void *fig, t_vector origin, t_vector direct)
{
	return (1);
}

float			ft_collide_cone(t_list **objs, struct s_object *obj, t_coll *coll, t_vector untr_od[2])
{
	t_cone	*con;
	t_vector	hit[2];
	float		res[2];
	float		sq_tan;
	t_vector	od[2];

	con = (t_cone *)obj->fig;
	od[0] = ft_3_pnt_transform(&(obj->inverse), untr_od[0]);
	od[1] = ft_3_vec_transform(&(obj->inverse), untr_od[1]);
	sq_tan = 1 + con->tan * con->tan;
	if (!ft_solve_sqr_(ft_3_vector_dot(od[1], od[1]) - sq_tan * od[1][1] * od[1][1],
		2.0f * (ft_3_vector_dot(od[0], od[1]) - sq_tan * od[1][1] * od[0][1]),
		ft_3_vector_dot(od[0], od[0]) - sq_tan * od[0][1] * od[0][1],
		&res))
	{
		if ((res[1] = get_caps_coll(od, &hit[1], con)) > FLT_MIN)
		{
			coll->o = obj;
			coll->tex_o = obj;
			coll->ucoll_pnt = hit[1];
			return (res[1]);
		}
		return (-FLT_MAX);
	}
	res[0] = get_cides_coll(od, res, &hit[0], con);
	res[1] = ((con->maxh == FLT_MAX && con->minh == -FLT_MAX) || fabsf(od[1][1]) < 1e-6) ?
			 -FLT_MAX : get_caps_coll(od, &hit[1], con);
	if (res[0] < 0 && res[1] < 0)
	{
//		printf("HERE res %f, %f\n", res[0], res[1]);
		return (-FLT_MAX);
	}
	return (get_closer_pnt(res, hit, coll, obj));
//	return (res[0] > FLT_MIN ? res[0] : -FLT_MAX);
}

int			ft_is_inside_cone(void *fig, t_vector point)
{
	t_cone		*cone;
	float 		hei;
	float		rad;

	cone = (t_cone *)fig;
//	hei = ft_3_vector_dot(cone->v, point - cone->o);
//	if (!IN_RANGE(hei, cone->minh, cone->maxh) && cone->maxh != FLT_MAX)
//		return (0);
//	rad = hei * cone->tan;
//	if ((ft_3_vector_dot(point - cone->o, point - cone->o) < hei * hei + rad * rad))
//	{
////		printf("INSIDE\n");
//		return (1);
//	}
////	printf("OUTSIDE\n");
	return (1);
}

t_vector	ft_get_norm_cone(void *fig, t_vector coll)
{
//	t_cone 		*con;
//
//	con = (t_cone *)fig;
//	con->h = ft_3_vector_dot(con->v, coll - con->o);
//	if (con->maxh != FLT_MAX && con->h >= con->maxh - 1e-2)
//		return (con->v);
//	if (con->minh != FLT_MIN && con->h <= con->minh + 1e-2)
//		return (-con->v);
//	return (ft_3_tounitvector(coll - ((t_cone *)fig)->o - ft_3_vector_scale(con->v,
//			(1.0f + con->tan * con->tan) * con->h)));
	return (ft_3_nullpointnew());
}
