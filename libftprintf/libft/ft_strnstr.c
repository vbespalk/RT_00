/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 12:18:03 by domelche          #+#    #+#             */
/*   Updated: 2017/10/27 12:18:05 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*large_str;
	char	*large_str_len;
	char	*small_str;
	int		i;

	large_str = (char *)haystack;
	small_str = (char *)needle;
	if (!ft_strcmp(small_str, ""))
		return (large_str);
	if (!(large_str_len = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	ft_strncpy(large_str_len, large_str, len);
	large_str_len[len] = '\0';
	while (large_str_len[i])
	{
		if (large_str_len[i] == small_str[0])
			if (!ft_strncmp(&large_str_len[i], small_str, ft_strlen(small_str)))
				return (&large_str[i]);
		i++;
	}
	return (NULL);
}
