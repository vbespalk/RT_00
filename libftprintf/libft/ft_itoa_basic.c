/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_basic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 13:24:41 by domelche          #+#    #+#             */
/*   Updated: 2018/05/10 18:14:42 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	function ft_itoa_basic is strongly NOT recommended for straight usage,
**	because all validation is placed in "wrapping" functions, which are
**	recommended to use: ft_itoa, ft_itoa_base, ft_uitoa, ft_uitoa_base;
**	otherwise, in case of invalid arguments, undefined behavior is expected
*/

#include "libft.h"

static char	*ft_strextract(char *str, int sign)
{
	unsigned int	i;
	char			*res;

	i = 0;
	while (!str[i] && i < 8 * sizeof(unsigned long long) - 1)
		i++;
	if (sign)
		str[--i] = '-';
	res = ft_strdup(&str[i]);
	free(str);
	return (res);
}

char		*ft_itoa_basic(unsigned long long num, int sign, int base)
{
	int		i;
	char	*str;

	i = 8 * sizeof(unsigned long long) - 1;
	if (!(str = (char *)
		ft_memalloc(sizeof(char) * (8 * sizeof(unsigned long long) + 1))))
		return (NULL);
	str[i] = '0';
	while (num)
	{
		str[i--] = "0123456789ABCDEF"[num % base];
		num /= base;
	}
	return (ft_strextract(str, sign));
}
