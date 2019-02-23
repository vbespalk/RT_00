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
	light->origin = (t_vector){ 0.0f, 10000.0f, 0.0f };
	light->type = L_POINT;
	light->color.val = 0xffffff;
	return (light);
}

t_ltype		ft_get_light_type(char *type)
{
	t_ltype		res;

	res = L_POINT;
	if (!type)
		return (res);
	else if (!ft_strcmp(type, "point"))
		res = L_POINT;
	else if (!ft_strcmp(type, "direct"))
		res = L_DIRECT;
	else if (!ft_strcmp(type, "parallel"))
		res = L_PARALLEL;
	else
		ft_printf(
			"PARSE WARNING: no such light type '%s'; value set to default\n",
			type);
	return (res);
}

void		ft_parse_light(char **content, t_list **lst, Uint32 id)
{
	char 			*ltype_str;
	t_light			*light;

	ltype_str = NULL;
	light = ft_lightnew();
	ft_lstpush(lst, ft_nodenew((void *)light, sizeof(t_light)));
	ft_get_attr(content, "type", (void *)&(ltype_str), DT_STRING);
	light->type = ft_get_light_type(ltype_str);
	free(ltype_str);
	ft_get_attr(content, "origin", (void *)&(light->origin), DT_POINT);
	ft_get_attr(content, "direct", (void *)&(light->direct), DT_POINT);
	ft_get_attr(content, "bright", (void *)&(light->bright), DT_COEF);
	ft_get_attr(content, "color", (void *)&(light->color), DT_COLOR);
}
