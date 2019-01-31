/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 17:35:29 by domelche          #+#    #+#             */
/*   Updated: 2018/03/22 14:44:46 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_swap_size_t(size_t *a, size_t *b)
{
	size_t	swap;

	swap = *a;
	*a = *b;
	*b = swap;
}

char		*ft_strcut(char *str, size_t from, size_t to)
{
	char	*strnew;
	size_t	len;
	size_t	i;
	size_t	j;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	from = (from >= len) ? len - 1 : from;
	to = (to >= len) ? len - 1 : to;
	if (from > to)
		ft_swap_size_t(&from, &to);
	i = 0;
	j = 0;
	if (!(strnew = (char *)malloc(sizeof(char) *
		(ft_strlen(str) - (to - from + 1) + 1))))
		return (NULL);
	while (str[i])
	{
		if (i < from || i > to)
			strnew[j++] = str[i];
		++i;
	}
	strnew[j] = 0;
	return (strnew);
}
