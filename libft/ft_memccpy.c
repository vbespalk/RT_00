/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 14:27:20 by domelche          #+#    #+#             */
/*   Updated: 2017/10/27 14:27:21 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*dst_str;
	unsigned char	*src_str;
	size_t			i;

	dst_str = (unsigned char *)dst;
	src_str = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		dst_str[i] = src_str[i];
		i++;
		if (src_str[i - 1] == (unsigned char)c)
			return (&((unsigned char *)dst)[i]);
	}
	return (NULL);
}
