/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ustos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 12:15:37 by domelche          #+#    #+#             */
/*   Updated: 2018/04/03 15:10:10 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_len_in_chars(wchar_t *us)
{
	size_t	len;

	len = 0;
	while (*us)
	{
		if (*us < 0x80)
			len += 1;
		else if (*us < 0x800)
			len += 2;
		else if (*us < 0x10000)
			len += 3;
		else if (*us < 0x110000)
			len += 4;
		++us;
	}
	return (len);
}

char			*ft_ustos(wchar_t *us)
{
	char	*s;
	size_t	size;
	size_t	i;

	if (!us)
		return (NULL);
	size = ft_len_in_chars(us);
	i = 0;
	if (!(s = (char *)ft_memalloc((size + 1) * sizeof(char))))
		return (NULL);
	s[size] = 0;
	while (i < size)
	{
		ft_write_wctoa(*us++, &s[i]);
		while (s[i])
			++i;
	}
	return (s);
}
