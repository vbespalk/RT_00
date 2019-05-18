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
	t_vector	odh[3];
	int 		num;
	int			i[2];
	double 		t;

	trs = (t_torus *)obj->fig;
	odh[0] = ft_3_pnt_transform(&(obj->inverse), untr_od[0]);
	odh[1] = ft_3_vec_transform(&(obj->inverse), untr_od[1]);
	doxr[0] = ft_3_vector_dot(odh[1], odh[1]);
	doxr[1] = ft_3_vector_dot(odh[0], odh[0]);
	doxr[2] = ft_3_vector_dot(odh[0], odh[1]);
	doxr[3] = trs->r_inner * trs->r_inner + trs->r_outer * trs->r_outer;
	abcde[0] = doxr[0] * doxr[0];
	abcde[1] = 4 * doxr[0] * doxr[2];
	abcde[2] = 2 * doxr[0] * (doxr[1] - doxr[3]) + 4 * doxr[2] * doxr[2] +
			4 * trs->r_outer * trs->r_outer * odh[1][1] * odh[1][1];
	abcde[3] = 4 * (doxr[1] - doxr[3]) * doxr[2] + 8 * trs->r_outer *
			trs->r_outer * odh[0][1] * odh[1][1];
	abcde[4] = (doxr[1] - doxr[3]) * (doxr[1] - doxr[3]) - 4 * trs->r_outer *
			trs->r_outer * (trs->r_inner * trs->r_inner - odh[0][1] * odh[0][1]);
	if ((num = ft_solve_quartic(abcde, res)) == 0)
	{
//		printf("NO SOL\n");
		return (FLT_MAX);
	}
	i[0] = -1;
	t = FLT_MAX;
	while (++i[0] < num)
	{
		if (res[i[0]] < t && res[i[0]] > 0)
		{
			coll->ucoll_pnt = odh[0] + ft_3_vector_scale(odh[1], (float)t);
			coll->norm = obj->ft_get_norm(obj->fig, &(obj->inverse), coll->ucoll_pnt);
			odh[2] = untr_od[0] + ft_3_vector_scale(untr_od[1], (float)res[i[0]]);
			if (obj->is_neg)
				odh[2] += ft_3_vector_scale(coll->norm, SHIFT);
			i[1] = ft_inside_type(objs, odh[2]);
			if (i[1] < 0 || (obj->is_neg && i[1] == 0))
				continue ;
			t = res[i[0]];
		}
	}
	if (t == FLT_MAX)
	{
//		printf("NO SOL\n");
		return (FLT_MAX);
	}
	coll->ucoll_pnt = odh[0] + ft_3_vector_scale(odh[1], (float)t);
	coll->coll_pnt = untr_od[0] + ft_3_vector_scale(untr_od[1], (float)t);
	coll->norm = obj->ft_get_norm(obj->fig, &(obj->inverse), coll->ucoll_pnt);
//	coll->coll_pnt += ft_3_vector_scale(coll->norm, SHIFT);
	if (obj->is_neg)
		coll->coll_pnt += ft_3_vector_scale(coll->norm, SHIFT);
	ft_choose_object(objs, obj, coll);
	coll->tex_o = coll->o;
	if (obj->is_neg)
		coll->norm = ft_3_vector_invert(coll->norm);
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
		return (0);
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

t_vector	ft_get_norm_torus(void *fig, t_matrix *inv_m, t_vector coll)
{
	t_torus		*trs;
	t_vector	norm;
	float 		dot;
	float 		r;

	trs = (t_torus *)fig;
	dot = ft_3_vector_dot(coll, coll);
	r = trs->r_outer * trs->r_outer + trs->r_inner * trs->r_inner;
	norm = ZERO_PNT;
	norm[0] = 4.0 * coll[0] * (dot - r);
	norm[1] = 4.0 * coll[1] * (dot - r + 2.0 * trs->r_outer * trs->r_outer);
	norm[2] = 4.0 * coll[2] * (dot - r);
	return (ft_3_tounitvector(ft_3_norm_transform(inv_m, norm)));
//	return(ft_3_tounitvector(ft_3_norm_transform(inv_m,
//		ft_3_tounitvector(coll - ft_3_vector_scale(ft_3_tounitvector((t_vector)
//		{coll[0], 0, coll[2]}), trs->r_outer)))));
}
