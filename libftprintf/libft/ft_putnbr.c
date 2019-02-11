/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 18:05:33 by domelche          #+#    #+#             */
/*   Updated: 2017/11/03 18:05:35 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	unsigned int	num;
	unsigned int	div;

	if (n < 0)
	{
		ft_putchar('-');
		num = (n + 1) * (-1) + 1;
	}
	else
		num = n;
	div = 1;
	while (num / div >= 10)
		div *= 10;
	while (div > 0)
	{
		ft_putchar(num / div % 10 + '0');
		div /= 10;
	}
}
