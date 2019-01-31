/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 15:15:38 by domelche          #+#    #+#             */
/*   Updated: 2018/07/22 15:17:09 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char			*ft_getstart(char *str, int *sign)
{
	int		i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		++i;
	*sign = (str[i] == '-') ? -1 : 1;
	if (str[i] == '-' || str[i] == '+')
		++i;
	while (str[i] == '0')
		++i;
	return (&(str[i]));
}

static long double	ft_get_mantissa(char *str)
{
	long double	man;
	long double	dev;
	int			i;

	man = 0;
	dev = 10.0;
	i = -1;
	while (ft_isdigit(str[++i]))
	{
		man += (long double)(str[i] - '0') / dev;
		dev *= 10;
	}
	return (man);
}

long double			ft_atod(const char *str)
{
	char			*s;
	int				sign;
	long double		res;
	int				i;

	res = 0;
	i = -1;
	s = ft_getstart((char *)str, &sign);
	while (ft_isdigit(s[++i]))
		res = res * 10.0 + (s[i] - '0');
	if (s[i] == '.')
		res += ft_get_mantissa(&(s[i + 1]));
	return (res * sign);
}
