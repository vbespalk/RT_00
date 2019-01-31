/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt_high.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 16:50:29 by domelche          #+#    #+#             */
/*   Updated: 2017/11/18 16:50:36 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_sqrt_rec(int nb, int min, int max)
{
	long int mid;

	mid = 0;
	if (max < min)
		return (min);
	if (mid * mid == nb)
		return (mid);
	else
		mid = (max + min) / 2;
	if (mid * mid > nb)
		return (ft_sqrt_rec(nb, min, mid - 1));
	if (mid * mid < nb)
		return (ft_sqrt_rec(nb, mid + 1, max));
	return (mid);
}

int			ft_sqrt_high(int nb)
{
	return (ft_sqrt_rec(nb, 0, nb));
}
