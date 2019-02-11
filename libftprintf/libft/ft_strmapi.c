/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 16:06:45 by domelche          #+#    #+#             */
/*   Updated: 2017/10/30 16:06:46 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
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
			res[i] = f(i, str[i]);
			i++;
		}
		res[i] = 0;
		return (res);
	}
	return (NULL);
}
