/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_limit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 19:03:50 by domelche          #+#    #+#             */
/*   Updated: 2018/09/19 19:04:00 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int				ft_limit(int min, int max, int num)
{
	if (num < min)
		return (min);
	if (num > max)
		return (max);
	return (num);
}

unsigned int	ft_limit_uint(unsigned int min, unsigned int max, unsigned int num)
{
	if (num < min)
		return (min);
	if (num > max)
		return (max);
	return (num);
}
