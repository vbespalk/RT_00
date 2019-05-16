
#include "rt.h"

//static float	ft_collide_box_face(
//					t_list **objs, t_object *obj,
//					t_coll *coll, t_vector odhu[5])
//{
//	t_box		*bx;
//	t_coll		pln_coll;
//	float		t;
//
//	bx = (t_box *)obj->fig;
//	t = ft_collide_plane(objs, bx->face[(int)odhu[0][3]], &pln_coll, odhu);
//	if (IN_RANGE(t, 0, odhu[1][3]) && t != FLT_MAX)
//	{
//		odhu[2] = odhu[3] + ft_3_vector_scale(odhu[4], t);
//		if (obj->is_neg)
//			odhu[2] += ft_3_vector_scale(coll->norm, SHIFT);
//		if (pln_coll.inside_type < 0
//			|| (obj->is_neg && pln_coll.inside_type == 0))
//			return (FLT_MAX);
//		coll->norm = ft_3_tounitvector(
//			ft_3_norm_transform(&(obj->inverse), pln_coll.norm));
//		if (obj->is_neg && pln_coll.inside_type != 1)
//			coll->norm = ft_3_vector_invert(coll->norm);
//		coll->coll_pnt = odhu[2];
//		coll->ucoll_pnt = pln_coll.ucoll_pnt;
//		coll->tex_o = pln_coll.o;
//		coll->o = obj;
//		return (t);
//	}
//	return (FLT_MAX);
//}

//float			ft_collide_box(
//					t_list **objs, t_object *obj,
//					t_coll *coll, t_vector untr_od[2])
//{
//	int 		i;
//	float		t[2];
//	t_vector	odhu[5];
//
//	i = -1;
//	odhu[3] = untr_od[0];
//	odhu[4] = untr_od[1];
//	odhu[0] = ft_3_pnt_transform(&(obj->inverse), untr_od[0]);
//	odhu[1] = ft_3_vec_transform(&(obj->inverse), untr_od[1]);
//	t[0] = FLT_MAX;
//	while (++i < BOX_FACES)
//	{
//		odhu[0][3] = i;
//		odhu[1][3] = t[0];
//		t[1] = ft_collide_box_face(objs, obj, coll, odhu);
//		if (t[1] < t[0])
//			t[0] = t[1];
//	}
//	ft_choose_object(objs, obj, coll);
//	return (t[0]);
//}

float		ft_collide_box(t_list **objs, struct s_object *obj, t_coll *coll, t_vector untr_od[2])
{
	t_box		*bx;
	t_coll		pln_coll;
	float		t_min;
	float 		t_cur;
	int 		i;
	t_vector	od[2];

	bx = (t_box *)obj->fig;
	i = -1;
	od[0] = ft_3_pnt_transform(&(obj->inverse), untr_od[0]);
	od[1] = ft_3_vec_transform(&(obj->inverse), untr_od[1]);
	t_min = FLT_MAX;
	while (++i < BOX_FACES)
	{
		t_cur = ft_collide_plane(objs, bx->face[i], &pln_coll, od);
		if (IN_RANGE(t_cur, FLT_MIN, t_min))
		{
			coll->coll_pnt = untr_od[0] + ft_3_vector_scale(untr_od[1], t_cur);
			coll->inside_type = ft_inside_type(objs, coll->coll_pnt);
			if (coll->inside_type < 0)
				continue ;
			t_min = t_cur;
			coll->ucoll_pnt = pln_coll.ucoll_pnt;
			coll->norm = ft_3_tounitvector(ft_3_norm_transform(&(obj->inverse), pln_coll.norm));
			if (obj->is_neg)
				coll->norm = ft_3_vector_invert(coll->norm);
			coll->tex_o = pln_coll.o;
			coll->o = obj;
		}
	}
	return (t_min);
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
//		printf("NOT_INSIDE\n");
		return (0);
	}
//	printf("INSIDE\n");
	return (1);
}

//t_vector	ft_get_norm_box(void *fig, t_matrix *inv_m, t_vector coll)
//{
//	(void)coll;
//	return (ft_3_nullpointnew());
//}
//
