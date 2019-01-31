/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 12:25:21 by domelche          #+#    #+#             */
/*   Updated: 2018/04/03 12:35:26 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_wstrlen(const wchar_t *wstr)
{
	size_t	len;

	if (!wstr)
		return (0);
	len = 0;
	while (*wstr++)
		++len;
	return (len);
}
