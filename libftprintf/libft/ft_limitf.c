/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_limitf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 19:04:29 by domelche          #+#    #+#             */
/*   Updated: 2018/09/19 19:04:40 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	ft_limitf(double min, double max, double num)
{
	if (num < min)
		return (min);
	if (num > max)
		return (max);
	return (num);
}
