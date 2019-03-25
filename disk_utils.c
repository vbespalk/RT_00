
#include "rt.h"

int			ft_is_reachable_disk(void *fig, t_vector origin, t_vector direct)
{
	(void)fig;
	(void)origin;
	(void)direct;
	return (1);
}

t_vector	ft_collide_disk(t_list **objs, t_object *obj, t_coll *coll, t_vector od[2])
{
	t_disk		*dsk;
	t_vector	coll_pnt;
	float		dis;

	dsk = (t_disk *)(obj->fig);
	coll_pnt = ft_3_line_plane_inter(dsk->origin, dsk->norm, od[0], od[1]);
	dis = ft_3_vector_dot(coll_pnt - dsk->origin, coll_pnt - dsk->origin);
	return ((!ft_3_pointcmp(ft_3_tounitvector(coll_pnt - od[0]), od[1], 1e-6))
		|| dis < dsk->in_r * dsk->in_r || dis > dsk->out_r * dsk->out_r
		? ft_3_nullpointnew() : coll_pnt);
}

int			ft_is_inside_disk(void *fig, t_vector point)
{
	(void)fig;
	(void)point;
	return (0);
}

t_vector	ft_get_norm_disk(void *fig, t_vector coll)
{
	(void)coll;
	return (((t_disk *)fig)->norm);
}
