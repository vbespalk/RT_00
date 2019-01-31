/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 18:05:58 by domelche          #+#    #+#             */
/*   Updated: 2017/11/03 18:05:59 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	num;
	unsigned int	div;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		num = (n + 1) * (-1) + 1;
	}
	else
		num = n;
	div = 1;
	while (num / div >= 10)
		div *= 10;
	while (div > 0)
	{
		ft_putchar_fd(num / div % 10 + '0', fd);
		div /= 10;
	}
}
