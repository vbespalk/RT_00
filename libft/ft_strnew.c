/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 14:58:23 by domelche          #+#    #+#             */
/*   Updated: 2017/10/30 14:58:25 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size, char c)
{
	char	*str;
	size_t	i;

	if (!(str = (char *)malloc(size + 1)))
		return (NULL);
	str[size] = 0;
	i = 0;
	while (i < size)
		str[i++] = c;
	return (str);
}
