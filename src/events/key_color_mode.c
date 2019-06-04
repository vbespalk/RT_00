/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_color_mode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 19:35:57 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/17 19:35:59 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_mode	*ft_new_node(int id)
{
	t_mode	*node;

	node = ft_smemalloc(sizeof(t_mode), "ft_add_node");
	node->id = id;
	node->next = NULL;
	return (node);
}

t_bool	ft_iter_lst(t_mode **nods, int id)
{
	t_mode *ptr[2];

	ptr[0] = *nods;
	ptr[1] = *nods;
	while (ptr[0])
	{
		if (ptr[0]->id == id)
		{
			if ((*nods)->next == NULL)
			{
				ft_memdel((void **)nods);
				return (true);
			}
			else if ((*nods)->id == ptr[0]->id)
				(*nods) = ptr[0]->next;
			else
				ptr[1]->next = ptr[0]->next;
			ft_memdel((void **)&ptr[0]);
			return (true);
		}
		ptr[1] = ptr[0];
		ptr[0] = ptr[0]->next;
	}
	ptr[1]->next = ft_new_node(id);
	return (false);
}

int		ft_switch_col_mode(t_env *e, Sint32 sum)
{
	t_bool deleted;

	if (e->color_mode == NULL)
	{
		e->color_mode = ft_new_node(sum);
		deleted = false;
	}
	else
		deleted = ft_iter_lst(&(e->color_mode), sum);
	deleted ? ft_render(e) : ft_col_mode(e->sdl, sum);
	return (2);
}
