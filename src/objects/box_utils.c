
#include "rt.h"

int			ft_is_reachable_box(void *fig, t_vector origin, t_vector direct)
{
	(void)fig;
	(void)origin;
	(void)direct;
	return (1);
}

float		ft_collide_box(
				t_list **objs, struct s_object *obj,
				t_coll *coll, t_vector untr_od[2])
{
	t_box		*bx;
	t_coll		pln_coll;
	float		t[2];
	int 		i;
	t_vector	odh[3];

	bx = (t_box *)obj->fig;
	i = -1;
	odh[0] = ft_3_pnt_transform(&(obj->inverse), untr_od[0]);
	odh[1] = ft_3_vec_transform(&(obj->inverse), untr_od[1]);
	t[0] = FLT_MAX;
	while (++i < BOX_FACES)
	{
		t[1] = ft_collide_plane(objs, bx->face[i], &pln_coll, odh);
		if (IN_RANGE(t[1], 0, t[0]) && t[1] != FLT_MAX)
		{
			odh[2] = untr_od[0] + ft_3_vector_scale(untr_od[1], t[1]);
			if (pln_coll.inside_type < 0
			|| (obj->is_neg && pln_coll.inside_type == 0))
				continue ;
			coll->norm = ft_3_tounitvector(
				ft_3_norm_transform(&(obj->inverse), pln_coll.norm));
			if (obj->is_neg)
				odh[2] += ft_3_vector_scale(coll->norm, SHIFT);
			if (obj->is_neg && pln_coll.inside_type != 1)
				coll->norm = ft_3_vector_invert(coll->norm);
			coll->coll_pnt = odh[2];
			coll->ucoll_pnt = pln_coll.ucoll_pnt;
			coll->tex_o = pln_coll.o;
			coll->o = obj;
			t[0] = t[1];
		}
	}
	if (obj->is_neg)
	{
		coll->coll_pnt += ft_3_vector_scale(
			coll->norm, (coll->norm[3] != 1) ? -SHIFT : SHIFT);
		coll->o = ft_inside_obj(objs, coll->coll_pnt, ft_get_inner_object);
		coll->coll_pnt -= ft_3_vector_scale(
			coll->norm, (coll->norm[3] != 1) ? -SHIFT : SHIFT);
	}
	return (t[0]);
}

int			ft_is_inside_box(t_object *o, t_vector point)
{
	t_box		*bx;
	float		proj[3];

	if (!o->fig)
		return (0);
	bx = (t_box *)o->fig;
	point = ft_3_pnt_transform(&(o->inverse), point);
	proj[0] = fabsf(ft_3_vector_dot(Z_AXIS,  point));
	proj[1] = fabsf(ft_3_vector_dot(Y_AXIS,  point));
	proj[2] = fabsf(ft_3_vector_dot(X_AXIS,  point));
	if (!IN_RANGE(proj[0], 0, bx->whl[0]) ||
		!IN_RANGE(proj[1], 0, bx->whl[1]) ||
		!IN_RANGE(proj[2], 0, bx->whl[2]))
	{
//		printf("OUT BOX\n");
		return (0);
	}
//	printf("IN BOX\n");
	return (1);
}

t_vector	ft_get_norm_box(void *fig, t_vector coll)
{
	(void)coll;
	return (ft_3_nullpointnew());
}
