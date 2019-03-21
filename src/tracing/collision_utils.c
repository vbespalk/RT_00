
#include "rt.h"

int			ft_inside_type(t_list **objs, t_vector point)
{
	t_list		*node;
	t_object	*o;

	node = *objs;
	while (node)
	{
		o = (t_object *)(node->content);
		if (o->ft_is_inside(o->fig, point))
			return ((o->is_neg) ? -1 : 1);
		node = node->next;
	}
	return (0);
}

t_object	*ft_get_inner_object(t_list *objs, t_vector point)
{
	t_vector	od[2];
	float		dist;
	float		min_dist;
	t_object	*o;
	t_object	*res;

	t_coll		*coll;

	od[0] = point;
	od[1] = (t_vector) { 1.0f, 0.0f, 0.0f };
	min_dist = FLT_MAX;
	res = NULL;
	while (objs)
	{
		o = (t_object *)(objs->content);
		dist = ft_3_point_point_dist(
			point, o->ft_collide(&objs, o, coll, od));
		if (dist < min_dist)
		{
			min_dist = dist;
			res = o;
		}
		objs = objs->next;
	}
	return (res);
}

t_object	*ft_inside_obj(
				t_list **objs,
				t_vector point,
				t_object *(*ft_choose)(t_list *objs, t_vector point))
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
			ft_lstpush(&res_objs, ft_nodenew((void *)o, sizeof(o)));
			++len;
		}
		node = node->next;
	}
	if (len == 0)
		return (NULL);
	else if (len == 1)
		return ((t_object *)(res_objs->content));
	else
		return (ft_choose(res_objs, point));
}
