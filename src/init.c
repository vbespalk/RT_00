/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 13:26:29 by vbespalk          #+#    #+#             */
/*   Updated: 2018/08/22 13:26:33 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_light	*init_slight(t_light **light, unsigned int *nb_li)
{
	t_light *ptr;

	(*nb_li)++;
	if (!(*light))
	{
		if (!(*light = (t_light *)malloc(sizeof(t_light))))
		{
			perror("Malloc: ");
			return (NULL);
		}
		ft_bzero((void *)(*light), sizeof(t_light));
		(*light)->next = NULL;
		return (*light);
	}
	ptr = *light;
	while (ptr->next)
		ptr = ptr->next;
	if (!(ptr->next = (t_light *)malloc(sizeof(t_light))))
	{
		perror("Malloc: ");
		return (NULL);
	}
	ft_bzero((void *)(ptr->next), sizeof(t_light));
	ptr->next->next = NULL;
	return (ptr->next);
}

t_object	*init_sobj(t_object **obj, unsigned int *nb_ob)
{
	t_object		*ptr;
	static int	id;

	(*nb_ob)++;
	if (!(*obj))
	{
		if (!(*obj = (t_object *)malloc(sizeof(t_object))))
		{
			perror("Malloc: ");
			return (NULL);
		}
		ft_bzero((void *)(*obj), sizeof(t_object));
		(*obj)->id = id++;
		(*obj)->next = NULL;
		return (*obj);
	}
	ptr = *obj;
	while (ptr->next)
		ptr = ptr->next;
	if (!(ptr->next = (t_object *)malloc(sizeof(t_object))))
	{
		perror("Malloc: ");
		return (NULL);
	}
	ft_bzero((void *)(ptr->next), sizeof(t_object));
	ptr->next->id = id++;
	ptr->next->next = NULL;
	return (ptr->next);
}

int		to_struct(t_scene *scene, char *s, int type)
{
	char	**prop;
	int		nb;

	if (!(prop = ft_strsplit(s, '\t')))
		return (0);
	nb = 0;
	while (prop[nb++])
		;
	if (type == 4)
		if (nb != 4 || !set_lights(scene, prop))
			return (clear_mem(&prop, nb));
	if (type == 5)
		if (nb != 3 || !set_cam(scene, prop))
			return (clear_mem(&prop, nb));
	if (!type || type == 1)
		if (nb != 5 || !set_object1(scene, prop, type))
			return (clear_mem(&prop, nb));
	if (type == 2 || type == 3)
		if (nb != 6 || !set_object2(scene, prop, type))
			return (clear_mem(&prop, nb));
	clear_mem(&prop, nb);
	return (1);
}
