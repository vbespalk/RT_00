/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 13:52:07 by domelche          #+#    #+#             */
/*   Updated: 2017/10/27 13:52:08 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	char			*mem;
	unsigned char	chr;

	i = 0;
	mem = (char *)b;
	chr = (unsigned char)c;
	while (i < len)
		mem[i++] = chr;
	return (b);
}
