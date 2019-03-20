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

t_vector	ft_collide_torus(void *fig, t_vector origin, t_vector direct)
{
	t_torus		*trs;
	double		res[4];
	double 		mnopq[6];
	double 		abcde[5];
	int 		num;
	int			i;
	double 		t;

	trs = (t_torus *)fig;
	mnopq[0] = ft_3_vector_dot(direct, direct);
	mnopq[1] = ft_3_vector_dot(direct, origin - trs->o);
	mnopq[2] = ft_3_vector_dot(origin - trs->o, origin - trs->o);
	mnopq[3] = ft_3_vector_dot(direct, trs->v);
	mnopq[4] = ft_3_vector_dot(origin - trs->o, trs->v);
	mnopq[5] = trs->r_outer * trs->r_outer + trs->r_inner * trs->r_inner;
	abcde[0] = mnopq[0] * mnopq[0];
	abcde[1] = 4.0f * mnopq[0] * mnopq[1];
	abcde[2] = 4.0f * mnopq[1] * mnopq[1] + 2.0f * mnopq[0] * mnopq[2] - 2.0f * mnopq[0] * mnopq[5]
			   + 4.0f * trs->r_outer * trs->r_outer * mnopq[3] * mnopq[3];
	abcde[3] = 4.0f * mnopq[1] * mnopq[2] - 4.0f * mnopq[1] * mnopq[5] + 8.f * trs->r_outer *
				trs->r_outer * mnopq[3] * mnopq[4];
	abcde[4] = mnopq[2] * mnopq[2] - 2.f * mnopq[2] * mnopq[5] + 4.f * trs->r_outer *
				trs->r_outer * mnopq[4] * mnopq[4] + ((trs->r_outer * trs->r_outer -
				trs->r_inner * trs->r_inner) * (trs->r_outer * trs->r_outer -
				trs->r_inner * trs->r_inner));
	if ((num = ft_solve_quartic(abcde, res)) == 0)
		return (ft_3_nullpointnew());
	i = -1;
	t = FLT_MAX;
	while (++i < num)
		if (res[i] < t && res[i] > 0)
			t = res[i];
	return (t == FLT_MAX ? ft_3_nullpointnew() : origin + ft_3_vector_scale(direct, t));
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
	float 		k;
//	float 		m;
	t_vector	a;
	t_vector	norm;

	trs = (t_torus *)fig;
	k = ft_3_vector_dot(coll - trs->o, trs->v);
	if (fabsf(k) > trs->r_inner)
		k = k > 0 ? trs->r_inner : -trs->r_inner;
	a = coll - ft_3_vector_scale(trs->v, k);
	if (trs->r_inner * trs->r_inner - k * k < -0.1f)
	{
//		printf("here r %f, k %f, dif %f, coll %f,%f,%f\n", trs->r_inner, k, trs->r_inner * trs->r_inner - k * k,
//				coll[0], coll[1], coll[2]);
		return (ft_3_nullpointnew());
	}
//	m = sqrtf(fabsf(trs->r_inner * trs->r_inner - k * k));
//	norm = ft_3_tounitvector(coll - a - ft_3_vector_scale(trs->o - a, m / trs->r_outer + m));
	norm = ft_3_tounitvector(coll - (trs->o + ft_3_vector_scale(ft_3_tounitvector(a - trs->o),
			trs->r_outer)));
	return(norm);
}
