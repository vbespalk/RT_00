/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 13:09:09 by vbespalk          #+#    #+#             */
/*   Updated: 2018/08/21 13:09:29 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		clear_mem(char ***mem, int nb)
{
	while (--nb >= 0)
		ft_memdel((void **)&(*mem)[nb]);
	ft_memdel((void **)(mem));
	return (0);
}

void	struct_del(t_scene *scene)
{
	if (scene->light)
		slight_del(&(scene->light));
	if (scene->objs)
		sobj_del((&scene->objs));
}

void	slight_del(t_light **lst)
{
	t_light *tmp;

	if ((*lst) == NULL)
		return ;
	while ((*lst)->next)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		ft_memdel((void **)&tmp);
	}
	ft_memdel((void **)lst);
}

void	sobj_del(t_object **lst)
{
	t_object *tmp;

	if ((*lst) == NULL)
		return ;
	while ((*lst)->next)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		ft_memdel((void **)&tmp);
	}
	ft_memdel((void **)lst);
}

char	*ft_ptrtostr(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!s1)
		return (NULL);
	if (*s2 == '\0')
		return ((char *)s1);
	while (s1[i])
	{
		j = 0;
		while (s1[i + j] == s2[j])
		{
			j++;
			if (s2[j] == '\0')
				return ((char *)&s1[i + j]);
		}
		i++;
	}
	return (NULL);
}
