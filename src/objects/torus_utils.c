//
// Created by ivoriik on 19.03.19.
//


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

int			ft_is_reachable_torus(void *fig, t_vector origin, t_vector direct)
{
	(void)origin;
	(void)direct;
	(void)fig;
	return (1);
}

t_vector	ft_collide_torus(t_list **objs, t_object *obj, t_coll *coll, t_vector od[2])
{
	t_torus		*trs;
	t_vector	coll_pnt;
	float		res[2];
	float 		dots[6];
	float 		koef[5];

	trs = (t_torus *)(obj->fig);
	dots[0] = ft_3_vector_dot(od[1], od[1]);
	dots[1] = ft_3_vector_dot(od[1], od[0] - trs->o);
	dots[2] = ft_3_vector_dot(od[0] - trs->o, od[0] - trs->o);
	dots[3] = ft_3_vector_dot(od[1], trs->v);
	dots[4] = ft_3_vector_dot(od[0] - trs->o, trs->v);
	dots[5] = trs->r_outer * trs->r_outer + trs->r_inner * trs->r_inner;
	koef[0] = dots[0] * dots[0];
	koef[1] = 4.0f * dots[0] * dots[1];
	koef[2] = 4.0f * dots[0] * dots[0] + 2.0f * dots[0] * dots[2] - 2.0f * dots[0] * dots[5]
			+ 4.0f * trs->r_outer * trs->r_outer * dots[3] * dots[3];
	koef[3] = 4.0f * dots[0] * dots[2] - 4.0f * dots[1] * dots[5] + 8.f * trs->r_outer *
			trs->r_outer * dots[3] * dots[4];
	koef[4] = dots[2] * dots[2] - 2.f * dots[2] * dots[5] + 4.f * trs->r_outer *
			trs->r_outer * dots[4] * dots[4] + (trs->r_outer * trs->r_outer -
			trs->r_inner * trs->r_inner) * (trs->r_outer * trs->r_outer -
			trs->r_inner * trs->r_inner);
	return (ft_3_nullpointnew());
}

int			ft_is_inside_torus(void *fig, t_vector point)
{
	t_torus		*trs;

	trs = (t_torus *)fig;

	return (0);
}

t_vector	ft_get_norm_torus(void *fig, t_vector coll)
{
	t_torus		*trs;

	trs = (t_torus *)fig;
	return(ft_3_nullpointnew());
}
