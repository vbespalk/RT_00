/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 13:25:05 by domelche          #+#    #+#             */
/*   Updated: 2018/08/23 13:25:05 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_scene		*ft_scenenew(void)
{
	t_scene	*scn;

	scn = ft_smemalloc(sizeof(t_scene), "ft_scenenew");
	scn->bg_color.val = 0;
	scn->cam = ft_cameranew();
	scn->skybox = NULL;
	return (scn);
}

void		ft_parse_scene(char **content, t_scene *scn)
{
	ft_get_attr(content, "name", (void *)&(scn->name), DT_STRING);
	if (!scn->name)
		scn->name = ft_strdup("New Scene");
	ft_get_attr(content, "bg_color", (void *)&(scn->bg_color), DT_COLOR);
	ft_get_attr(content, "skybox", (void *)&(scn->skybox), DT_SKYBOX);
	ft_get_attr(content, "camera", (void *)&(scn->cam), DT_CAMERA);
	ft_get_attr(content, "lights", (void *)&(scn->lights), DT_LIGHT_ARR);
	ft_get_attr(content, "objects", (void *)&(scn->objs), DT_OBJECT_ARR);
}
