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

t_object	*ft_objectnew(void)
{
	t_object	*obj;

	obj = ft_smemalloc(sizeof(t_object), "ft_objectnew");
	obj->color.val = 0xffff00;
	obj->ambnt = 0.1;
	obj->diff = 1.0;
	obj->phong = 0;
	obj->refr = 1.0;
	return (obj);
}

static void	ft_balance_koefs(t_object *o)
{
	float	sum;

	sum = o->diff + o->trans + o->spclr;
	if (sum > 1.0)
	{
		o->diff /= sum;
		o->trans /= sum;
		o->spclr /= sum;
	}
}

t_object	*ft_parse_object(char *attr)
{
	t_object	*o;

	o = ft_objectnew();
	attr = ft_get_curve(attr, '{');
	ft_get_attr_in_scope(attr, "color:", (void *)(&(o->color)), COLOR);
	ft_get_attr_in_scope(attr, "ambnt:", (void *)(&(o->ambnt)), KOEF);
	ft_get_attr_in_scope(attr, "diff:", (void *)(&(o->diff)), KOEF);
	ft_get_attr_in_scope(attr, "spclr:", (void *)(&(o->spclr)), KOEF);
	ft_get_attr_in_scope(attr, "s_blur:", (void *)(&(o->s_blur)), KOEF);
	ft_get_attr_in_scope(attr, "refr:", (void *)(&(o->refr)), KOEF);
	ft_get_attr_in_scope(attr, "trans:", (void *)(&(o->trans)), KOEF);
	ft_get_attr_in_scope(attr, "t_blur:", (void *)(&(o->t_blur)), KOEF);
	ft_get_attr_in_scope(attr, "phong:", (void *)(&(o->phong)), KOEF);
	ft_get_attr_in_scope(attr, "translate:", (void *)(&(o->translate)), PNT);
	ft_get_attr_in_scope(attr, "rotate:", (void *)(&(o->rotate)), PNT);
	ft_balance_koefs(o);
	o->rotate.x = ft_torad(o->rotate.x);
	o->rotate.y = ft_torad(o->rotate.y);
	o->rotate.z = ft_torad(o->rotate.z);
	return (o);
}
