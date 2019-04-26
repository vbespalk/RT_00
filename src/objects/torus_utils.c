//
// Created by ivoriik on 19.03.19.
//


#include "rt.h"

int			ft_is_reachable_torus(void *fig, t_vector origin, t_vector direct)
{
	(void)origin;
	(void)direct;
	(void)fig;
	return (1);
}

float		ft_collide_torus(t_list **objs, struct s_object *obj, t_coll *coll, t_vector untr_od[2])
{
	t_torus		*trs;
	double		res[4];
	double 		doxr[4];
	double 		abcde[5];
	t_vector	od[2];
	int 		num;
	int			i;
	double 		t;

	trs = (t_torus *)obj->fig;
	od[0] = ft_3_pnt_transform(&(obj->inverse), untr_od[0]);
	od[1] = ft_3_vec_transform(&(obj->inverse), untr_od[1]);
	doxr[0] = ft_3_vector_dot(od[1], od[1]);
	doxr[1] = ft_3_vector_dot(od[0], od[0]);
	doxr[2] = ft_3_vector_dot(od[0], od[1]);
	doxr[3] = trs->r_inner * trs->r_inner + trs->r_outer * trs->r_outer;
	abcde[0] = doxr[0] * doxr[0];
	abcde[1] = 4 * doxr[0] * doxr[2];
	abcde[2] = 2 * doxr[0] * (doxr[1] - doxr[3]) + 4 * doxr[2] * doxr[2] +
			4 * trs->r_outer * trs->r_outer * od[1][1] * od[1][1];
	abcde[3] = 4 * (doxr[1] - doxr[3]) * doxr[2] + 8 * trs->r_outer *
			trs->r_outer * od[0][1] * od[1][1];
	abcde[4] = (doxr[1] - doxr[3]) * (doxr[1] - doxr[3]) - 4 * trs->r_outer *
			trs->r_outer * (trs->r_inner * trs->r_inner - od[0][1] * od[0][1]);
	if ((num = ft_solve_quartic(abcde, res)) == 0)
	{
//		printf("NO SOL\n");
		return (-FLT_MAX);
	}
	i = -1;
	t = FLT_MAX;
	while (++i < num)
		if (res[i] < t && res[i] > 0)
			t = res[i];
	if (t == FLT_MAX)
	{
//		printf("NO SOL\n");
		return (-FLT_MAX);
	}
	coll->ucoll_pnt = od[0] + ft_3_vector_scale(od[1], (float)t);
	coll->o = obj;
	coll->tex_o = obj;
	coll->norm = ft_3_tounitvector(ft_3_norm_transform(&(obj->inverse),
			coll->ucoll_pnt - ft_3_vector_scale(ft_3_tounitvector((t_vector)
			{coll->ucoll_pnt[0], FLT_MIN, coll->ucoll_pnt[2]}), trs->r_outer)));
//	printf("HERE\n");
	return ((float)t);
}

int			ft_is_inside_torus(t_object *o, t_vector point)
{
	t_torus		*trs;
	double		k;
	double		r_outer;
	double		r_inner;
	t_vector	a;

	trs = (t_torus *)o->fig;
	point = ft_3_pnt_transform(&(o->inverse), point);
	k = point[1];
	if (fabs(k) > trs->r_inner)
	{
//		printf("OUT HEI\n");
		return (0);
	}
//	a = point - ft_3_vector_scale(trs->v, (float)k);
	a = (t_vector){point[0], FLT_MIN, point[2]};
	r_outer = ft_3_vector_dot(a, a);
	a = point - ft_3_vector_scale(ft_3_tounitvector(a), trs->r_outer);
	r_inner = ft_3_vector_dot(a, a);
	if (r_outer > (trs->r_outer + trs->r_inner) * (trs->r_outer + trs->r_inner) ||
		r_inner > trs->r_inner * trs->r_inner)
	{
//		printf("OUT r_outer %f inn %f or %f, %f\n", r_outer, r_inner, (trs->r_outer + trs->r_inner) *
//		(trs->r_outer + trs->r_inner), trs->r_inner * trs->r_inner);
		return (0);
	}
//	printf("IN\n");
	return (1);
}

t_vector	ft_get_norm_torus(void *fig, t_vector coll)
{
//	t_torus		*trs;
//	double		k;
////	float 		m;
//	t_vector	a;
//	t_vector	norm;
//
//	trs = (t_torus *)fig;
//	k = ft_3_vector_dot(coll - trs->o, trs->v);
//	if (fabs(k) > trs->r_inner)
//		k = k > 0 ? trs->r_inner : -trs->r_inner;
//	a = coll - ft_3_vector_scale(trs->v, (float)k);
//	if (trs->r_inner * trs->r_inner - k * k < -0.1f)
//	{
////		printf("here r %f, k %f, dif %f, coll %f,%f,%f\n", trs->r_inner, k, trs->r_inner * trs->r_inner - k * k,
////				coll[0], coll[1], coll[2]);
		return (ft_3_nullpointnew());
//	}
////	m = sqrtf(fabsf(trs->r_inner * trs->r_inner - k * k));
////	norm = ft_3_tounitvector(coll - a - ft_3_vector_scale(trs->o - a, m / trs->r_outer + m));
//	norm = ft_3_tounitvector(coll - (trs->o + ft_3_vector_scale(ft_3_tounitvector(a - trs->o),
//			trs->r_outer)));
//	return(norm);
}
