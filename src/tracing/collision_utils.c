
#include "rt.h"

int			ft_inside_type(t_list **objs, t_vector point)
{
	int			res;
	t_list		*node;
	t_object	*o;

	res = 0;
	node = *objs;
	while (node)
	{
		o = (t_object *)(node->content);
		if (o->ft_is_inside(o->fig, point))
		{
			if (o->is_neg)
				return (-1);
			res = 1;
		}
		node = node->next;
	}
	return (res);
}

t_object	*ft_get_inner_object(t_list **objs, t_vector point)
{
	t_list		*node;
	t_vector	od[2];
	float		dist[2];
	t_object	*o;
	t_object	*res;
	t_coll		coll;

	node = *objs;
	od[0] = point;
	od[1] = (t_vector) { 1.0f, 0.0f, 0.0f };
	dist[0] = FLT_MAX;
	res = NULL;
	while (node)
	{
		o = (t_object *)(node->content);
		o->ft_collide(objs, o, &coll, od);
		dist[1] = ft_3_point_point_dist(point, coll.coll_pnt);
		if (dist[1] < dist[0])
		{
			dist[0] = dist[1];
			res = o;
		}
		node = node->next;
	}
	return (res);
}

t_object	*ft_inside_obj(
				t_list **objs,
				t_vector point,
				t_object *(*ft_choose)(t_list **objs, t_vector point))
{
	t_list		*res_objs;
	t_list		*node;
	t_object	*o;
	int 		len;

	res_objs = NULL;
	node = *objs;
	len = 0;
	while (node)
	{
		o = (t_object *)(node->content);
		if (o->ft_is_inside(o->fig, point))
		{
			ft_lstpush(&res_objs, ft_nodenew((void *)o, sizeof(t_object)));
			++len;
		}
		node = node->next;
	}
	if (len == 0)
		return (NULL);
	else if (len == 1)
		return ((t_object *)(res_objs->content));
	else
		return (ft_choose(&res_objs, point));
}
