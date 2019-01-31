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

t_point3	ft_atopoint3(char *str)
{
	t_point3		point;

	while (*str && *str != '(')
		++str;
	if (!*str)
		ft_error("invalid scene file");
	point.x = ft_atod(++str);
	while (*str && *str != ',')
		++str;
	if (!*str)
		ft_error("invalid scene file");
	point.y = ft_atod(++str);
	while (*str && *str != ',')
		++str;
	if (!*str)
		ft_error("invalid scene file");
	point.z = ft_atod(++str);
	while (*str && *str != ')')
		++str;
	if (!*str)
		ft_error("invalid scene file");
	return (point);
}

char		*ft_search_attr(char *content, char *attr, int ftsa_mode)
{
	int		curve_count;
	int		is_comment;

	curve_count = ftsa_mode;
	is_comment = 0;
	while (*content)
	{
		if (*content == '{')
			++curve_count;
		else if (*content == '}')
			if (ftsa_mode == FTSA_IN_SCOPE)
				return (NULL);
			else
				--curve_count;
		else if (*content == '#')
			is_comment = 1;
		else if (is_comment && *content == '\n')
			is_comment = 0;
		if (curve_count == ftsa_mode && !is_comment && *content == *attr)
			if (!ft_strncmp(content, attr, ft_strlen(attr)))
				return (content);
		++content;
	}
	return (NULL);
}

void		ft_read_attr(void *dst, char *attr, int type)
{
	char			*data;
	char			*to_free;
	long long		i;

	while (*attr && *attr != ':')
		++attr;
	++attr;
	if ((i = (long long)ft_strchr(attr, ';') - (long long)attr) < 0)
		ft_error("invalid scene file");
	data = ft_strsub(attr, 0, i);
	to_free = data;
	data = ft_strtrim(data);
	free(to_free);
	if (type == KOEF)
		*((double *)dst) = ft_limitf(0, 1, ft_atod(data));
	else if (type == DBL)
		*((double *)dst) = ft_atod(data);
	else if (type == STR)
		*((char **)dst) = ft_strdup(data);
	else if (type == PNT)
		*((t_point3 *)dst) = ft_atopoint3(data);
	else
		(*((t_color *)dst)).val = ft_limit(0, 0xffffff, ft_atoi_base(data, 16));
	free(data);
}

void		ft_get_attr_in_scope(char *start, char *name, void *dst, int type)
{
	char	*ptr;

	if ((ptr = ft_search_attr(start, name, FTSA_IN_SCOPE)))
		ft_read_attr(dst, ptr, type);
}
