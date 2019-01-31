/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 16:14:35 by domelche          #+#    #+#             */
/*   Updated: 2017/10/30 16:14:36 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strequ(char const *s1, char const *s2)
{
	char	*str1;
	char	*str2;

	if (s1 && s2)
	{
		str1 = (char *)s1;
		str2 = (char *)s2;
		return ((!ft_strcmp(str1, str2)) ? 1 : 0);
	}
	return (0);
}
