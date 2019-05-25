/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attribute_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 18:51:51 by domelche          #+#    #+#             */
/*   Updated: 2019/05/25 18:51:57 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			ft_parse_str(char **content, char **data,
								void *dst, t_datatype datatype)
{
	++(*data);
	if (datatype == DT_STRING)
		*((char **)dst) = ft_strsub(
				*data, 0, ft_strchr(*data, '\"') - *data);
	else if (datatype == DT_COLOR)
		(*((Uint32 *)dst)) = SDL_Swap32(ft_limit_uint(
				0, 0xffffff, (unsigned int)ft_atoi_base(*data, 16)) << 8);
	else
		ft_parse_warning_datatype(content[0], *data, datatype);
}

void			ft_parse_num(char **content, char **data,
								void *dst, t_datatype datatype)
{
	if (datatype == DT_FLOAT)
		*((float *)dst) = (float)ft_atod(*data);
	else if (datatype == DT_COEF)
		*((float *)dst) = (float)ft_limitf(0.0, 1.0, (float)ft_atod(*data));
	else
		ft_parse_warning_datatype(content[0], *data, datatype);
}

void			ft_parse_bool(char **content, char **data,
								void *dst, t_datatype datatype)
{
	if (datatype == DT_BOOL)
		*((int *)dst) = (**data == 't') ? 1 : 0;
	else
		ft_parse_warning_datatype(content[0], *data, datatype);
}
