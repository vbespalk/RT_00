/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                     :+:      :+:    :+:   */
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
	if ((*res)[0] > (*res)[1] || (*res)[0] < FLT_MIN)
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
		coll->norm = ft_3_tounitvector(ft_3_norm_transform(&(obj->inverse),
					(coll->ucoll_pnt - (t_vector){0, coll->ucoll_pnt[1], 0})));
		return (t[0]);
	}
	else
	{
		coll->ucoll_pnt = hit[1];
		coll->norm = ft_3_tounitvector(ft_3_norm_transform(&(obj->inverse), (t_vector) {0, 1, 0}));
		return (t[1]);
	}
}

/*
** ADD 1e-1 TO t TO AVOID MISSES BETW SIDES AND CAPS
*/

static float	get_cides_coll(const t_vector *od, float *t, t_vector *coll, t_cylinder *clnd)
{
	t_vector	hit[2];

	hit[0] = od[0] + ft_3_vector_scale(od[1], t[0]);
	hit[1] = od[0] + ft_3_vector_scale(od[1], t[1]);
	if (t[0] >= FLT_MIN && IN_RANGE(hit[0][1], -clnd->maxh, clnd->maxh))
	{
		*coll = hit[0];
		return (t[0]);
	}
	else if (t[1] >= FLT_MIN && IN_RANGE(hit[1][1], -clnd->maxh, clnd->maxh))
	{
		*coll = hit[1];
		return (t[1]);
	}
	return (-FLT_MAX);
}

static float	get_caps_coll(const t_vector *od, t_vector *coll, t_cylinder *clnd)
{
	float 		t[2];
	t_vector	ori[2];
	t_vector	hit[2];

	ori[0] = od[0] + (t_vector){FLT_MIN, clnd->maxh, FLT_MIN};
	ori[1] = od[0] - (t_vector){FLT_MIN, clnd->maxh, FLT_MIN};
	t[0] = -(ori[0][1]) / od[1][1];
	t[1] = -(ori[1][1]) / od[1][1];
	if (t[0] < FLT_MIN && t[1] < FLT_MIN)
		return (-FLT_MAX);
	t[0] > t[1] || t[0] < 0 ? ft_swap_float(&t[0], &t[1]),
			ft_swap(&ori[0], &ori[1], sizeof(t_vector)) : 1;
	hit[0] = ori[0] + ft_3_vector_scale(od[1], t[0]);
	hit[1] = ori[1] + ft_3_vector_scale(od[1], t[1]);
	if (t[0] > FLT_MIN && ft_3_vector_dot(hit[0], hit[0]) < 1)
	{
		*coll = hit[0] + clnd->maxh;
		return (t[0]);
	}
	else if (t[1] > FLT_MIN && ft_3_vector_dot(hit[1], hit[1]) < 1)
	{
		*coll = hit[1] - clnd->maxh;
		return (t[1]);
	}
	return (-FLT_MAX);
}

int					ft_is_reachable_cylinder(void *fig, t_vector origin, t_vector direct)
{
	return (1);
}

float			ft_collide_cylinder(t_list **objs, struct s_object *obj, t_coll *coll, t_vector untr_od[2])
{
	t_cylinder	*clnd;
	t_vector	hit[2];
	float		res[2];
	t_vector	od[2];

	clnd = (t_cylinder *)obj->fig;
	od[0] = ft_3_pnt_transform(&(obj->inverse), untr_od[0]);
	od[1] = ft_3_vec_transform(&(obj->inverse), untr_od[1]);
	if (!ft_solve_sqr_(od[1][0] * od[1][0] + od[1][2] * od[1][2],
		2.0f * (od[0][0] * od[1][0] + od[0][2] * od[1][2]),
		od[0][0] * od[0][0] + od[0][2] * od[0][2] - 1,
		&res))
		return (-FLT_MAX);
	res[0] = get_cides_coll(od, res, &hit[0], clnd);
	res[1] = (clnd->maxh == FLT_MAX || fabsf(od[1][1]) < 1e-6) ?
			-FLT_MAX : get_caps_coll(od, &hit[1], clnd);
	if (res[0] < 0 && res[1] < 0)
		return (-FLT_MAX);
	return (get_closer_pnt(res, hit, coll, obj));
}

int			ft_is_inside_cylinder(void *fig, t_vector point)
{
//	t_cylinder	*clnd;
//	float 		hei;
//	t_vector	pnt_r;
//
//	clnd = (t_cylinder *)fig;
//	hei = ft_3_vector_dot(clnd->v, point - clnd->o);
//	if (!IN_RANGE(hei, 0.0f, clnd->maxh) && clnd->maxh != FLT_MAX)
		return (0);
//	pnt_r = point - (clnd->o + ft_3_vector_scale(clnd->v, hei));
////	if (ft_3_vector_dot(pnt_r, pnt_r) < clnd->r * clnd->r)
////		printf("INSIDE\n");
//	return (ft_3_vector_dot(pnt_r, pnt_r) < clnd->r * clnd->r ? 1 : 0);
}

t_vector	ft_get_norm_cylinder(void *fig, t_vector coll)
{
//	t_cylinder *clnd;
//	float 		h;
//
//	clnd = (t_cylinder *)fig;
//	h = ft_3_vector_dot(clnd->v, coll - clnd->o);
//	if (clnd->maxh != FLT_MAX &&h >= clnd->maxh - 1e-2)
//		return (clnd->v);
//	if (clnd->maxh != FLT_MAX &&h <= 1e-2)
//		return (-clnd->v);
//	return (ft_3_tounitvector(coll - ((t_cylinder *)fig)->o
//	- ft_3_vector_scale(((t_cylinder *)fig)->v,h)));
	return (ft_3_nullpointnew());
}
