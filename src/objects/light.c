/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 13:25:05 by domelche          #+#    #+#             */
/*   Updated: 2018/08/23 13:26:51 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_light		*ft_lightnew(void)
{
	t_light		*light;

	light = ft_smemalloc(sizeof(t_light), "ft_lightnew");
	light->bright = 0.15;
	light->origin = ft_3_pointnew(0.0, 10000.0, 0.0);
	light->type = POINT;
	light->color.val = 0XFFFFFF;
	return (light);
}

t_ltype		ft_get_light_type(char *type)
{
	t_ltype		res;

	res = POINT;
	if (!ft_strcmp(type, "direct"))
		res = DIRECT;
	if (!ft_strcmp(type, "parallel"))
		res = PARALLEL;
	return (res);
}

char		*ft_parse_light(char *attr, t_scene *scn)
{
	char			*ptr;
	char 			*ltype_str;
	t_light			*light;

	ltype_str = NULL;
	attr = ft_get_curve(attr, '{');
	if (!*attr)
		ft_error("invalid scene file");
	light = ft_lightnew();
	ft_lstpush(&(scn->lights), ft_nodenew((void *)light, sizeof(t_light)));
	ft_get_attr_in_scope(attr, "origin:", (void *)&(light->origin), PNT);
	ft_get_attr_in_scope(attr, "direct:", (void *)&(light->direct), PNT);
	ft_get_attr_in_scope(attr, "bright:", (void *)&(light->bright), KOEF);
	ft_get_attr_in_scope(attr, "color:", (void *)&(light->color), COLOR);
	if ((ptr = ft_search_attr(attr, "type:", FTSA_IN_SCOPE)))
	{
		ft_read_attr((void *)&(ltype_str), ptr, STR);
		light->type = ft_get_light_type(ltype_str);
	}
	return (ft_get_curve(attr, '}'));
}
