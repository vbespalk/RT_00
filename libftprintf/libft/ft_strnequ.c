/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 16:25:12 by domelche          #+#    #+#             */
/*   Updated: 2017/10/30 16:25:13 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	char	*str1;
	char	*str2;

	if (s1 && s2)
	{
		str1 = (char *)s1;
		str2 = (char *)s2;
		return ((!ft_strncmp(str1, str2, n)) ? 1 : 0);
	}
	return (0);
}
