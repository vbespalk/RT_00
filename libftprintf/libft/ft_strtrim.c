/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 17:56:33 by domelche          #+#    #+#             */
/*   Updated: 2017/10/30 17:56:34 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_get_start(char *s)
{
	int		i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	return (i);
}

static unsigned int	ft_get_end(char *s)
{
	int		i;

	i = ft_strlen(s) - 1;
	while ((s[i] == ' ' || s[i] == '\n' || s[i] == '\t') && i != 0)
		i--;
	return (i);
}

char				*ft_strtrim(char const *s)
{
	char			*str;
	unsigned int	start;
	unsigned int	end;

	if (s)
	{
		str = (char *)s;
		start = ft_get_start(str);
		end = ft_get_end(str);
		if (start > end)
		{
			if (!(str = (char *)malloc(sizeof(char))))
				return (NULL);
			str[0] = '\0';
			return (str);
		}
		else
			return (ft_strsub(s, start, end - start + 1));
	}
	return (NULL);
}
