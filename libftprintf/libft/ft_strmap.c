/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:38:06 by domelche          #+#    #+#             */
/*   Updated: 2017/10/30 15:38:07 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char			*res;
	char			*str;
	unsigned int	i;

	if (s && f)
	{
		str = (char *)s;
		if (!(res = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1))))
			return (NULL);
		i = 0;
		while (str[i])
		{
			res[i] = f(str[i]);
			i++;
		}
		res[i] = 0;
		return (res);
	}
	return (NULL);
}
