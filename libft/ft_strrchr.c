/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 11:36:27 by domelche          #+#    #+#             */
/*   Updated: 2017/10/27 11:36:28 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	char	*res;

	str = (char *)s;
	res = NULL;
	while (*str != '\0')
	{
		if (*str == c)
			res = str;
		str++;
	}
	if (c == '\0')
		return (str);
	else
		return (res);
}
