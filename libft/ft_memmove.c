/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 15:40:24 by domelche          #+#    #+#             */
/*   Updated: 2017/10/27 15:40:26 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dst_str;
	unsigned char	*src_str;
	size_t			i;

	dst_str = (unsigned char *)dst;
	src_str = (unsigned char *)src;
	i = 0;
	if (dst_str > src_str)
		while (len-- > 0)
			dst_str[len] = src_str[len];
	else
	{
		while (i < len)
		{
			dst_str[i] = src_str[i];
			i++;
		}
	}
	return (dst);
}
