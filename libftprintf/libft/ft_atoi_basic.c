/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_basic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 15:16:17 by domelche          #+#    #+#             */
/*   Updated: 2018/07/22 15:17:45 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_getstart(char *str, int *sign, int base)
{
	int		i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		++i;
	*sign = (base == 10 && str[i] == '-') ? -1 : 1;
	if (str[i] == '-' || str[i] == '+')
		++i;
	if (base == 8 && str[i] == '0')
		++i;
	else if (base == 16 && str[i] == '0' &&
		(str[i + 1] == 'x' || str[i + 1] == 'X'))
		i += 2;
	while (str[i] == '0')
		++i;
	return (&(str[i]));
}

static int	ft_isbasechar(int c, int base)
{
	int		index;

	index = ft_indexof_chr("0123456789abcdef", ft_tolower(c));
	return ((index >= 0 && index < base) ? 1 : 0);
}

static int	ft_get_num(int c)
{
	if (ft_isdigit(c))
		return (c - '0');
	else if (c >= 'a')
		return (c - 'a' + 10);
	else
		return (c - 'A' + 10);
}

long long	ft_atoi_basic(const char *str, int base)
{
	char				*s;
	int					sign;
	int					str_len;
	unsigned long long	res;
	size_t				i;

	res = 0;
	str_len = 0;
	i = 0;
	s = ft_getstart((char *)str, &sign, base);
	while (ft_isbasechar(s[i], base))
	{
		res = res * base + (ft_get_num(s[i++]));
		++str_len;
	}
	if ((res > LONG_MAX || str_len > 19) && sign > 0)
		return (-1);
	if ((res - 1 > LONG_MAX || str_len > 19) && sign < 0)
		return (0);
	return ((long long)(res * sign));
}
