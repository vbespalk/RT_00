
#include "rt.h"

int			ft_is_reachable_box(void *fig, t_vector origin, t_vector direct)
{
	(void)fig;
	(void)origin;
	(void)direct;
	return (1);
}

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
//		printf("T_CUR %f\n", t_cur);
		if (IN_RANGE(t_cur, FLT_MIN, t_min))
		{
//			printf("here\n");
			t_min = t_cur;
			coll->ucoll_pnt = pln_coll.ucoll_pnt;
			coll->norm = ft_3_tounitvector(ft_3_norm_transform(&(obj->inverse), pln_coll.norm));
			coll->tex_o = pln_coll.o;
			coll->o = obj;
		}
	}
	return (t_min == FLT_MAX ? -FLT_MAX: t_min);
}

int			ft_is_inside_box(void *fig, t_vector point)
{
//	t_box		*bx;
//	t_vector	hit_vec;
//	float		proj[3];
//
//	if (!fig)
//		return (0);
//	bx = (t_box *)fig;
//	hit_vec = point - bx->o;
//	proj[0] = ft_3_vector_dot(ft_3_tounitvector(bx->lwh[0]),  hit_vec);
//	proj[1] = ft_3_vector_dot(ft_3_tounitvector(bx->lwh[1]),  hit_vec);
//	proj[2] = ft_3_vector_dot(ft_3_tounitvector(bx->lwh[2]),  hit_vec);
//	if (!IN_RANGE(proj[0], 0, ft_3_vector_len(bx->lwh[0])) ||
//		!IN_RANGE(proj[1], 0, ft_3_vector_len(bx->lwh[1])) ||
//		!IN_RANGE(proj[2], 0, ft_3_vector_len(bx->lwh[2])))
//	{
//		printf("OUT BOX\n");
//		return (0);
//	}
//	printf("IN BOX\n");
	return (1);
}

t_vector	ft_get_norm_box(void *fig, t_vector coll)
{
	(void)coll;
	return (ft_3_nullpointnew());
}
