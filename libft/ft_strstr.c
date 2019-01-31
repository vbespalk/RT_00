/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 11:44:39 by domelche          #+#    #+#             */
/*   Updated: 2017/10/27 11:44:40 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	char	*large_str;
	char	*small_str;

	large_str = (char *)haystack;
	small_str = (char *)needle;
	if (!ft_strcmp(small_str, ""))
		return (large_str);
	while (*large_str)
	{
		if (*large_str == *small_str)
			if (!ft_strncmp(large_str, small_str, ft_strlen(small_str)))
				return (large_str);
		large_str++;
	}
	return (NULL);
}
