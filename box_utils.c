
#include "rt.h"

int			ft_is_reachable_box(void *fig, t_vector origin, t_vector direct)
{
	(void)fig;
	(void)origin;
	(void)direct;
	return (1);
}

t_vector	ft_collide_box(t_list **objs, t_object *obj, t_coll *coll, t_vector od[2])
{
	t_box		*bx;
	t_vector	coll_pnt;
	float		t_min;
	float 		t_cur;
	int 		i;

	bx = (t_box *)(obj->fig);
	i = -1;

	t_min = FLT_MAX;
	while (++i < BOX_FACES)
	{

		coll_pnt = ft_3_nullpointnew(); //ft_collide_plane(objs, bx->face[i], od); <--

		if (ft_3_isnullpoint(coll_pnt))
			continue ;
		t_cur = ft_3_vector_len(coll_pnt - od[0]);
		if (t_cur < t_min)
		{
			t_min = t_cur;
			bx->fcoll = bx->face[i];
		}
	}
	return (t_min == FLT_MAX
		? ft_3_nullpointnew() : od[0] + ft_3_vector_scale(od[1], t_min));
}

int			ft_is_inside_box(void *fig, t_vector point)
{
	t_box		*bx;
	t_vector	hit_vec;
	float		proj[3];

	if (!fig)
		return (0);
	bx = (t_box *)fig;
	hit_vec = point - bx->o;
	proj[0] = ft_3_vector_dot(ft_3_tounitvector(bx->lwh[0]),  hit_vec);
	proj[1] = ft_3_vector_dot(ft_3_tounitvector(bx->lwh[1]),  hit_vec);
	proj[2] = ft_3_vector_dot(ft_3_tounitvector(bx->lwh[2]),  hit_vec);
	if (!IN_RANGE(proj[0], 0, ft_3_vector_len(bx->lwh[0])) ||
		!IN_RANGE(proj[1], 0, ft_3_vector_len(bx->lwh[1])) ||
		!IN_RANGE(proj[2], 0, ft_3_vector_len(bx->lwh[2])))
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
	if (((t_box *)fig)->fcoll != NULL)
		return (((t_box *)fig)->fcoll->norm);
	return (ft_3_nullpointnew());
}
