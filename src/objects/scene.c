/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scn.c                                            :+:      :+:    :+:   */
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
	return (scn);
}

t_scene		*ft_get_scene(char *file_name)
{
	t_scene		*scn;
	int			fd;

	scn = ft_scenenew();
	if ((fd = open(file_name, O_RDONLY)) < 0)
		ft_error("cannot open file");
	if ((read(fd, NULL, 0)) < 0)
		ft_error("cannot read file");
	ft_parse(ft_readfile(file_name), scn);
	return (scn);
}

void		ft_parse_scene(char *content, t_scene *scn)
{
	ft_get_attr(content, "name", (void *)&(scn->name), DT_STRING);
	if (!scn->name)
		scn->name = ft_strdup("New Scene");
	ft_get_attr(content, "bg_color", (void *)&(scn->bg_color), DT_COLOR);
	ft_get_attr(content, "camera", (void *)&(scn->cam), DT_CAMERA);
	ft_get_attr(content, "objects", (void *)&(scn->objs), DT_OBJECT_ARR);
	ft_get_attr(content, "lights", (void *)&(scn->objs), DT_LIGHT_ARR);
}
