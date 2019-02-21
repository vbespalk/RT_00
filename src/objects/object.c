/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 13:25:05 by domelche          #+#    #+#             */
/*   Updated: 2018/08/23 13:27:08 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_object	*ft_objectnew(Uint32 id)
{
	t_object	*o;

	o = ft_smemalloc(sizeof(t_object), "ft_objectnew");
	o->id = id;
	o->color.val = 0xffff00;
	o->ambnt = 0.1f;
	o->diff = 1.0f;
	o->phong = 0;
	o->refr = 1.0f;
	return (o);
}

static void	ft_balance_koefs(t_object *o)
{
	float	sum;

	sum = o->diff + o->trans + o->spclr;
	if (sum > 1.0f)
	{
		o->diff /= sum;
		o->trans /= sum;
		o->spclr /= sum;
	}
}

void		*ft_get_figure_parser(char *name)
{
	if (!name)
	{
		ft_parse_warning("object with unspecified name ignored");
		return (NULL);
	}
	else if (!ft_strcmp(name, "plane"))
		return (ft_parse_plane);
	else if (!ft_strcmp(name, "sphere"))
		return (ft_parse_sphere);
	else if (!ft_strcmp(name, "cone"))
		return (ft_parse_cone);
	else
	{
		ft_printf("PARSE WARNING: unknown object name '%s'\n", name);
		return (NULL);
	}
}

void		ft_parse_object(char *content, t_list *list, Uint32 id)
{
	t_object	*o;
	char		*name;
	void		*(*ft_parse_figure)(char *, t_object *o);

	ft_get_attr(content, "name", (void *)(&(name)), DT_STRING);
	if (!(ft_parse_figure = ft_get_figure_parser(name)))
		return ;
	o = ft_objectnew(id);
	ft_get_attr(content, "color", (void *)(&(o->color)), DT_COLOR);
	ft_get_attr(content, "ambnt", (void *)(&(o->ambnt)), DT_KOEF);
	ft_get_attr(content, "diff", (void *)(&(o->diff)), DT_KOEF);
	ft_get_attr(content, "spclr", (void *)(&(o->spclr)), DT_KOEF);
	ft_get_attr(content, "s_blur", (void *)(&(o->s_blur)), DT_KOEF);
	ft_get_attr(content, "refr", (void *)(&(o->refr)), DT_FLOAT);
	ft_get_attr(content, "trans", (void *)(&(o->trans)), DT_KOEF);
	ft_get_attr(content, "t_blur", (void *)(&(o->t_blur)), DT_KOEF);
	ft_get_attr(content, "phong", (void *)(&(o->phong)), DT_KOEF);
	ft_get_attr(content, "translate", (void *)(&(o->translate)), DT_POINT);
	ft_get_attr(content, "rotate", (void *)(&(o->rotate)), DT_POINT);
	ft_balance_koefs(o);
	o->rotate[0] = (float)ft_torad(o->rotate[0]);
	o->rotate[1] = (float)ft_torad(o->rotate[1]);
	o->rotate[2] = (float)ft_torad(o->rotate[2]);
	o->fig = ft_parse_figure(content, o);
	ft_lstpush(&(list), ft_nodenew((void *)o, sizeof(t_object)));
}
