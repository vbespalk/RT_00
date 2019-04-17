/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paraboloid_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 18:12:51 by vbespalk          #+#    #+#             */
/*   Updated: 2019/02/19 18:12:54 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int			ft_solve_sqr_(double a, double b, double c, double (*res)[2])
{
	double d;

	d = pow(b, 2) - 4.0f * a * c;
	if (d < 0)
		return (0);
	d = sqrt(d);
	(*res)[0] = (float)((-b + d) / (2.0f * a));
	(*res)[1] = (float)((-b - d) / (2.0f * a));
	if (((*res)[0] > (*res)[1] && (*res)[1] > FLT_MIN) || (*res)[0] < FLT_MIN)
		ft_swap(&(*res)[0], &(*res)[1], sizeof(double));
	return (1);
}

static float	get_closer_pnt(const double *t, const t_vector *hit, t_coll *coll, t_object *obj)
{
	coll->o = obj;
	coll->tex_o = obj;
	if ((t[0] < t[1] || t[1] < 0) && t[0] > 0)
//	if ((t[0]  > FLT_MIN - 1e-06))
	{
		coll->ucoll_pnt = hit[0];
		coll->norm = ft_3_tounitvector(ft_3_norm_transform(&(obj->inverse),
				hit[0] - ((t_vector){0, hit[0][1] + ((t_prbld *)obj->fig)->r, 0})));
		return ((float)t[0]);
	}
	if (t[1] > 0)
	{
//		printf("HERE\n");
		coll->ucoll_pnt = hit[1];
		coll->norm = ft_3_tounitvector(ft_3_norm_transform(&(obj->inverse), (t_vector) {0, 1, 0}));
		return ((float)t[1]);
	}
	return (-FLT_MAX);
}

static float	get_caps_coll(t_vector od[2], t_vector *coll, t_prbld *par)
{
	float		t;
	t_vector 	o;

	od[0][1] -= par->maxh;
	t = par->maxh == FLT_MAX ? -FLT_MAX : -(od[0][1]) / od[1][1];
	if (t < FLT_MIN)
		return (-FLT_MAX);
	*coll = od[0] + ft_3_vector_scale(od[1], t);
	if (ft_3_vector_dot(*coll, *coll) > par->r * par->r)
	{
		*coll = ft_3_nullpointnew();
		return (-FLT_MAX);
	}
	return (t);
}

int			ft_is_reachable_prbld(void *fig, t_vector origin, t_vector direct)
{
	(void)origin;
	(void)direct;
	(void)fig;
	return (1);
}

static double	get_cides_coll(t_vector od[2], double *t, t_vector *coll, t_prbld *par)
{
	t_vector	hit[2];
	float 		m[2];

	hit[0] = od[0] + ft_3_vector_scale(od[1], (float)t[0]);
//	m[0] = ft_3_vector_dot(par->v, coll[0] - par->o);
	hit[1] = od[0] + ft_3_vector_scale(od[1], (float)t[1]);
//	m[1] = ft_3_vector_dot(par->v, coll[1] - par->o);
	if (par->maxh == FLT_MAX)
	{
		if (t[0] >= FLT_MIN)
		{
			coll[0] = hit[0];
			return (t[0]);
		}
		else if (t[1] >= FLT_MIN)
		{
			coll[0] = hit[1];
			return (t[1]);
		}
		return (-FLT_MAX);
	}
	if (t[0] >= (FLT_MIN - 1e-2) && IN_RANGE(hit[0][1], FLT_MIN - 1e-2, par->maxh))
	{
		*coll = hit[0];
		return (t[0]);
	}
	else if (t[1] >= (FLT_MIN - 1e-2) && IN_RANGE(hit[1][1], FLT_MIN - 1e-2, par->maxh))
	{
		*coll = hit[1];
		return (t[1]);
	}
//	printf("GET_SIDES COLL t[0] %f, t[1] %f\n", t[0], t[1]);
	return (-FLT_MAX);
}

float	ft_collide_prbld(t_list **objs, struct s_object *obj, t_coll *coll, t_vector untr_od[2])
{
	t_prbld		*par;
	t_vector	hit[2];
	double		res[2];
	float 		dot_dv;
	float 		dot_vx;
	t_vector	od[2];
	float 		k;

	par = (t_prbld *)obj->fig;
	od[0] = ft_3_pnt_transform(&(obj->inverse), untr_od[0]);
	od[1] = ft_3_vec_transform(&(obj->inverse), untr_od[1]);
	dot_dv = ft_3_vector_dot(od[1], (t_vector){0, 1, 0});
	dot_vx = ft_3_vector_dot(od[0], (t_vector){0, 1, 0});
	k = par->maxh / (par->r * par->r);
	if (!ft_solve_sqr_(k * (od[1][0] * od[1][0] + od[1][2] * od[1][2]),
		2.0f * k * (od[1][0] * od[0][0] + od[1][2] * od[0][2]) - od[1][1],
		k * (od[0][0] * od[0][0] + od[0][2] * od[0][2]) - od[0][1],
		&res) || (res[0] < FLT_MIN && res[1] < FLT_MIN))
		return (-FLT_MAX);
	if (res[0] < FLT_MIN && res[1] < FLT_MIN)
		printf("LOWER RES %f, %f\n", res[0], res[1]);
	res[0] = get_cides_coll(od, res, &hit[0], par);
//	if (res[0] > FLT_MIN - 1e-6)
//	if (res[0] > FLT_MIN - 1e-6 && (par->maxh == FLT_MAX || fabsf(dot_dv) < 1e-6))
//	{
//		printf("HERE res[0] %f\n", res[0]);
//		coll->ucoll_pnt = od[0] + ft_3_vector_scale(od[1], (float)res[0]);
//		coll->o = obj;
//		coll->tex_o = obj;
//		coll->norm = ft_3_tounitvector(ft_3_norm_transform(&(obj->inverse),
//				hit[0] - ((t_vector){0, hit[0][1] + 1, 0})));
//		return ((float)res[0]);
//	}
	res[1] = get_caps_coll(od, &hit[1], par);
	return (get_closer_pnt(res, hit, coll, obj));
	return (-FLT_MAX);
}

int			ft_is_inside_prbld(void *fig, t_vector point)
{
//	t_prbld		*par;
//	float 		hei;
//	t_vector	rad;
//
//	par = (t_prbld *)fig;
//	hei = ft_3_vector_dot(par->v, point - par->o);
//	if (!IN_RANGE(hei, -(1e-1), par->maxh) && par->maxh != FLT_MAX)
//	{
//		printf("HOORAY! OUTSIDE %f max %f\n", hei, par->maxh);
//		return (0);
//	}
//	rad = point - (par->o + ft_3_vector_scale(par->v, par->r));
//	printf("rad %f, dot %f\n", sqrtf(ft_3_vector_dot(rad, rad)), ft_3_vector_dot(point -
//	(par->o - ft_3_vector_scale(par->v, par->r)), par->v));
//	if (sqrtf(ft_3_vector_dot(rad, rad)) <= ft_3_vector_dot(point -
//	(par->o - ft_3_vector_scale(par->v, par->r)), par->v))
//	{
//		printf("INSIDE\n");
//		return (1);
//	}
//	printf("OUTSIDE\n");
	return (0);
}

t_vector	ft_get_norm_prbld(void *fig, t_vector coll)
{
//	t_prbld		*par;
//	float 		h;
//
//	par = (t_prbld *)fig;
//	h = ft_3_vector_dot(par->v, coll - par->o);
//	if (h >= par->maxh - 1e-2)
//		return(ft_3_tounitvector(par->v));
//	else
//		return (ft_3_tounitvector(coll - (par->o + ft_3_vector_scale(par->v, h + par->r))));
	return (ft_3_nullpointnew());
}
