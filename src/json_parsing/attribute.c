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

#include "rt.h"

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

void		ft_get_attr
				(char *content, void *dst, char *attr, t_datatype datatype)
{
	char	*data;

	data = ft_search_attr(content, attr);
	if (!data)
		return ;
	while (ft_isspace(*data))
		++data;
	if (*data == '\"')
		ft_parse_str(content, &data, dst, datatype);
	else if (*data == '{')
		ft_parse_json_object(content, &data, dst, datatype);
	else if (*data == '[')
		ft_parse_json_array(content, &data, dst, datatype);
	else
		ft_parse_num(content, &data, dst, datatype);
}
