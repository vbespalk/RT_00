/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_wctoa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 12:53:04 by domelche          #+#    #+#             */
/*   Updated: 2018/04/03 15:43:05 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_convert(wchar_t wc, char *u_char, int size)
{
	if (size == 1)
		u_char[0] = wc;
	else if (size == 2)
	{
		u_char[0] = 0xC0 | ((0xFC0 & wc) >> 6);
		u_char[1] = 0x80 | (0x3F & wc);
	}
	else if (size == 3)
	{
		u_char[0] = 0xE0 | ((0xF000 & wc) >> 12);
		u_char[1] = 0x80 | ((0xFC0 & wc) >> 6);
		u_char[2] = 0x80 | (0x3F & wc);
	}
	else
	{
		u_char[0] = 0xF0 | ((0x3C0000 & wc) >> 18);
		u_char[1] = 0x80 | ((0x3F000 & wc) >> 12);
		u_char[2] = 0x80 | ((0xFC0 & wc) >> 6);
		u_char[3] = 0x80 | (0x3F & wc);
	}
}

void		ft_write_wctoa(wchar_t wc, char *str)
{
	int		size;

	if (!str)
		return ;
	if (wc < 0x80)
		size = 1;
	else if (wc < 0x800)
		size = 2;
	else if (wc < 0x10000)
		size = 3;
	else
		size = 4;
	ft_convert(wc, str, size);
}
