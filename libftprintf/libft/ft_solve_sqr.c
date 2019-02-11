/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solve_sqr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 12:14:48 by domelche          #+#    #+#             */
/*   Updated: 2018/09/19 12:15:28 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_solve_sqr(float a, float b, float c, float (*res)[3])
{
	float	d;

	d = (float)pow(b, 2) - 4.0f * a * c;
	if (d < 0)
	{
		*res[0] = 0;
		return ;
	}
	d = (float)sqrt(d);
	(*res)[0] = 1;
	(*res)[1] = (-b + d) / (2.0f * a);
	(*res)[2] = (-b - d) / (2.0f * a);
}
