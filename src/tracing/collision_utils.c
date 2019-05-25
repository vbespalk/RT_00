/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 18:55:25 by domelche          #+#    #+#             */
/*   Updated: 2019/05/25 18:55:27 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ft_free_list(t_list **head)
{
	t_list	*node;
	t_list	*prev;

	node = *head;
	while (node)
	{
		prev = node;
		node = node->next;
		free(prev);
	}
}

t_object	*ft_inside_obj(
				t_list **objs,
				t_vector point,
				t_object *(*ft_choose)(t_list **objs, t_vector point))
{
	t_list		*res_objs;
	t_list		*node;
	t_object	*o;
	t_object	*res;
	int			len;

	res_objs = NULL;
	node = *objs;
	len = 0;
	while (node)
	{
		o = (t_object *)(node->content);
		if (o->ft_is_inside(o, point))
		{
			ft_lstpush(&res_objs, ft_nodenew((void *)o, sizeof(t_object)));
			++len;
		}
		node = node->next;
	}
	res = (len == 0) ? NULL : (t_object *)(res_objs->content);
	if (len > 1)
		res = ft_choose(&res_objs, point);
	ft_free_list(&res_objs);
	return (res);
}

void		ft_choose_object(t_list **objs, t_object *obj, t_coll *coll)
{
	if (obj->is_neg)
	{
		coll->o = ft_inside_obj(objs, coll->coll_pnt, ft_get_inner_object);
		coll->coll_pnt -= ft_3_vector_scale(coll->norm, SHIFT);
	}
	else
		coll->o = obj;
}

int			ft_is_invisible(t_object *obj, int inside_type)
{
	return (
		(obj->react_neg && inside_type == IT_NEG)
		|| (obj->is_neg && inside_type != IT_POS_RT));
}
