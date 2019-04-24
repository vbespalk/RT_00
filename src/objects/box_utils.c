
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
		if (IN_RANGE(t_cur, FLT_MIN, t_min))
		{
			t_min = t_cur;
			coll->ucoll_pnt = pln_coll.ucoll_pnt;
			coll->norm = ft_3_tounitvector(ft_3_norm_transform(&(obj->inverse), pln_coll.norm));
			coll->tex_o = pln_coll.o;
			coll->o = obj;
		}
	}
	return (t_min == FLT_MAX ? -FLT_MAX: t_min);
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
		printf("OUT BOX\n");
		return (0);
	}
	printf("IN BOX\n");
	return (1);
}

t_vector	ft_get_norm_box(void *fig, t_vector coll)
{
	(void)coll;
	return (ft_3_nullpointnew());
}
