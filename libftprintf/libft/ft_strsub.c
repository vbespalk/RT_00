/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 16:31:40 by domelche          #+#    #+#             */
/*   Updated: 2017/10/30 16:31:41 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	char	*sub;
	size_t	i;

	if (s)
	{
		str = (char *)s;
		if (!(sub = (char *)ft_memalloc(sizeof(char) * (len + 1))))
			return (NULL);
		i = 0;
		while (i < len && s[i])
			sub[i++] = str[start++];
		sub[i] = 0;
		return (sub);
	}
	return (NULL);
}
