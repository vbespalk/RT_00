/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 18:52:54 by domelche          #+#    #+#             */
/*   Updated: 2019/05/25 18:53:06 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static char	*ft_read(char *filename)
{
	int		fd;

	if ((fd = open(filename, O_RDONLY)) < 0)
		ft_error("cannot open file");
	if ((read(fd, NULL, 0)) < 0)
		ft_error("cannot read file");
	return (ft_readfile(filename));
}

t_scene		*ft_parse_json(char *filename)
{
	char	*(content[2]);
	t_scene	*scn;

	content[0] = ft_read(filename);
	content[1] = content[0];
	scn = ft_scenenew();
	ft_check_syntax(content[0]);
	ft_parse_scene(content, scn);
	free(content[0]);
	return (scn);
}
