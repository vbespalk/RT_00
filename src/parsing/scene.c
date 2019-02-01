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
	scn->name = ft_strdup("New Scene");
	scn->cam = ft_cameranew();
	return (scn);
}

t_scene		*ft_get_scene(char *file_name)
{
	t_scene		*scn;
	int			fd;
	int			i;
	int			length;

	scn = ft_scenenew();
	if ((fd = open(file_name, O_RDONLY)) < 0)
		ft_error("cannot open file");
	if ((read(fd, NULL, 0)) < 0)
		ft_error("cannot read file");
	ft_parse(ft_readfile(file_name), scn);
	i = -1;
	length = ft_lstlen(&(scn->objs));
	while (++i < THREADS)
		scn->rhhns[i] = ft_rhhn_list_new(length);
	return (scn);
}

void		ft_parse_scene(char *attr, t_scene *scn)
{
	char	*ptr;
	char	*to_free;

	attr = ft_get_curve(attr, '{');
	if ((ptr = ft_search_attr(attr, "name:", FTSA_IN_SCOPE)))
	{
		to_free = scn->name;
		ft_read_attr((void *)&(scn->name), ptr, STR);
		free(to_free);
	}
	if ((ptr = ft_search_attr(attr, "world_color:", FTSA_IN_SCOPE)))
		ft_read_attr((void *)&(scn->bg_color), ptr, COLOR);
}
