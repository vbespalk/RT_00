/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 13:25:05 by domelche          #+#    #+#             */
/*   Updated: 2018/08/23 13:27:16 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_parse(char *content, t_scene *scn)
{
	char			*attr;
	char			*tmp;
	char			*to_free;
	unsigned int	id;

	id = 0;
	if (!content)
		ft_error("scn file is empty");
	to_free = content;
	if ((attr = ft_search_attr(content, "scn", FTSA_GLOBALLY)))
		ft_parse_scene(attr, scn);
	if ((attr = ft_search_attr(content, "camera", FTSA_GLOBALLY)))
		ft_parse_camera(attr, scn);
	tmp = content;
	while ((attr = ft_search_attr(tmp, "light", FTSA_GLOBALLY)))
		tmp = ft_parse_light(attr, scn);
	tmp = content;
	while ((attr = ft_search_attr(tmp, "plane", FTSA_GLOBALLY)))
		tmp = ft_parse_plane(attr, scn, id++);
	tmp = content;
	while ((attr = ft_search_attr(tmp, "sphere", FTSA_GLOBALLY)))
		tmp = ft_parse_sphere(attr, scn, id++);
	tmp = content;
	while ((attr = ft_search_attr(tmp, "cone", FTSA_GLOBALLY)))
		tmp = ft_parse_cone(attr, scn, id++);
	free(to_free);
}

char		*ft_get_curve(char *attr, char curve)
{
	while (*attr && *attr != curve)
		++attr;
	if (!*attr)
		ft_error("invalid scn file");
	return (attr + 1);
}
