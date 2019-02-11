/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lflag.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 17:35:39 by domelche          #+#    #+#             */
/*   Updated: 2018/04/13 16:26:50 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

static char	*ft_parse_lflags_l(char *str, t_arg *arg)
{
	if (*(str + 1) == 'l')
	{
		arg->lflags |= LF_LL;
		++str;
	}
	else
		arg->lflags |= LF_L;
	return (str);
}

static char	*ft_parse_lflags_h(char *str, t_arg *arg)
{
	if (*(str + 1) == 'h')
	{
		arg->lflags |= LF_HH;
		++str;
	}
	else
		arg->lflags |= LF_H;
	return (str);
}

char		*ft_parse_lflags(char *str, t_arg *arg)
{
	while (1)
	{
		if (*str == 'l')
			str = ft_parse_lflags_l(str, arg);
		else if (*str == 'h')
			str = ft_parse_lflags_h(str, arg);
		else if (*str == 'j')
			arg->lflags |= LF_J;
		else if (*str == 'z')
			arg->lflags |= LF_Z;
		else
			return (str);
		++str;
	}
}
