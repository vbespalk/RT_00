/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 11:55:04 by domelche          #+#    #+#             */
/*   Updated: 2018/03/31 13:35:11 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "itoa_basic.h"

char		*ft_itoa_base(long long num, int base)
{
	unsigned long long	unum;
	int					sign;

	if (base < 2 || base > 16)
		return (NULL);
	if (num < 0)
	{
		unum = -1 * num;
		sign = 1;
	}
	else
	{
		unum = num;
		sign = 0;
	}
	return (ft_itoa_basic(unum, sign, base));
}
