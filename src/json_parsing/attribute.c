/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attribute.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 13:20:50 by domelche          #+#    #+#             */
/*   Updated: 2018/08/23 13:27:40 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json.h"

t_vector	ft_parse_point(char *str)
{
	float		coords[3];
	t_vector	point;

	ft_get_attr(str, &(coords[0]), "x", DT_FLOAT);
	ft_get_attr(str, &(coords[1]), "y", DT_FLOAT);
	ft_get_attr(str, &(coords[2]), "z", DT_FLOAT);
	point[0] = coords[0];
	point[1] = coords[1];
	point[2] = coords[2];
	return (point);
}

static int	ft_is_key_str(char **content)
{
	while (*(++(*content)) != '\"')
		;
	while (ft_isspace(*(++(*content))))
		;
	if (**content == ':')
	{
		++(*content);
		return (1);
	}
	else
	{
		--(*content);
		return (0);
	}
}

static char	*ft_search_attr(char *content, char *attr)
{
	int		curve_count;

	curve_count = 0;
	while (*content)
	{
		++content;
		if (*content == '{' || *content == '[')
			++curve_count;
		else if (*content == '}' || *content == ']')
			--curve_count;
		if (curve_count > 0)
			continue ;
		else if (curve_count < 0)
			return (NULL);
		if (curve_count == 0 && *content == '\"' && *(content - 1) != '\\' &&
			!ft_strncmp(attr, content + 1, ft_strlen(attr)) &&
			ft_is_key_str(&content))
			return (content);
	}
	return (NULL);
}

static void	ft_parse_str
				(char *content, char **data, void *dst, t_datatype datatype)
{
	++(*data);
	if (datatype == DT_STRING)
		*((char **)dst) = ft_strcut(
			*data, 0, ft_strchr(*data, '\"') - *data);
	else if (datatype == DT_COLOR)
		(*((int *)dst)) = ft_limit(
			0, 0xffffff, (int)ft_atoi_base(*data, 16));
	else
		ft_parse_warning(content, *data, datatype);
}

void		ft_get_attr
				(char *content, void *dst, char *attr, t_datatype datatype)
{
	char	*data;

	data = ft_search_attr(content, attr);
	while (ft_isspace(*data))
		++data;
	if (*data == '\"')
		ft_parse_str(content, &data, dst, datatype);
	else if (*data == '{')
	{
		if (datatype == DT_POINT)
			*((t_vector *)dst) = ft_parse_point(data);
		else
			ft_parse_warning(content, data, datatype);
	}
	else
	{
		if (datatype == DT_FLOAT)
			*((float *)dst) = (float)ft_atod(data);
		else if (datatype == DT_KOEF)
			*((float *)dst) = (float)ft_limitf(0.0, 1.0, (float)ft_atod(data));
		else
			ft_parse_warning(content, data, datatype);
	}
}
