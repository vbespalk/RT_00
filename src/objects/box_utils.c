
#include "rt.h"

static float	ft_collide_box_face(
					t_list **objs, t_object *obj,
					t_coll *coll, t_vector untr_od[2])
{
	t_vector	od[2];
	t_box		*bx;
	t_coll		pln_coll;
	float		t;

	bx = (t_box *)obj->fig;
	od[0] = ft_3_pnt_transform(&(obj->inverse), untr_od[0]);
	od[1] = ft_3_vec_transform(&(obj->inverse), untr_od[1]);
	t = ft_collide_plane(objs, bx->face[(int)untr_od[0][3]], &pln_coll, od);
	if (IN_RANGE(t, 0, untr_od[1][3]) && t != FLT_MAX)
	{
//		coll->coll_pnt = pln_coll.coll_pnt;
		coll->coll_pnt = untr_od[0] + ft_3_vector_scale(untr_od[1], t);

//		ft_3_vector_print("coll_pnt: ", coll->coll_pnt);

		coll->norm = ft_3_tounitvector(
			ft_3_norm_transform(&(obj->inverse), pln_coll.norm));
		if (obj->is_neg)
			coll->coll_pnt += ft_3_vector_scale(coll->norm, SHIFT);
		if (pln_coll.inside_type < 0
			|| (obj->is_neg && pln_coll.inside_type == 0))
			return (FLT_MAX);
//		if (obj->is_neg && pln_coll.inside_type != 1)
//			coll->norm = ft_3_vector_invert(coll->norm);
//		coll->coll_pnt = untr_od[2];
		coll->ucoll_pnt = pln_coll.ucoll_pnt;
		coll->tex_o = pln_coll.o;
		return (t);
	}
	return (FLT_MAX);
}

float			ft_collide_box(
					t_list **objs, t_object *obj,
					t_coll *coll, t_vector untr_od[2])
{
	int 		i;
	float		t[2];

	i = -1;
	t[0] = FLT_MAX;
	while (++i < BOX_FACES)
	{
		untr_od[0][3] = i;
		untr_od[1][3] = t[0];
		t[1] = ft_collide_box_face(objs, obj, coll, untr_od);
		if (t[1] < t[0])
			t[0] = t[1];
	}
//	coll->coll_pnt += ft_3_vector_scale(coll->norm, SHIFT);
	ft_choose_object(objs, obj, coll);
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
		return (0);
	return (1);
}

//t_vector	ft_get_norm_box(void *fig, t_matrix *inv_m, t_vector coll)
//{
//	(void)coll;
//	return (ft_3_nullpointnew());
//}
//
