/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 20:09:35 by domelche          #+#    #+#             */
/*   Updated: 2017/10/26 20:09:37 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strlcat_strlen(const char *str)
{
	size_t	res;

	res = 0;
	while (str[res] != '\0')
		res++;
	return (res);
}

static char		*ft_strlcat_strncpy(
					char *dst,
					const char *src,
					size_t dstsize,
					size_t dst_len)
{
	int		i;
	int		n;

	i = 0;
	n = (dstsize - dst_len - 1);
	while (i < n && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	if (n > 0)
		dst[i] = '\0';
	return (dst);
}

size_t			ft_strlcat(
					char *dst,
					const char *src,
					size_t dstsize)
{
	size_t	res;
	size_t	dst_len;
	int		i;

	i = 0;
	dst_len = ft_strlcat_strlen(dst);
	res = ((dstsize < dst_len) ? dstsize : dst_len) + ft_strlcat_strlen(src);
	while (dst[i])
		i++;
	ft_strlcat_strncpy(&dst[i], src, dstsize, dst_len);
	return (res);
}
