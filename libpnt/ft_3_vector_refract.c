/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3_vector_refract.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 18:58:59 by domelche          #+#    #+#             */
/*   Updated: 2019/05/25 18:59:01 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpnt.h"

t_vector	ft_3_vector_refract(
				t_vector norm, t_vector direct, float refr1, float refr2)
{
	float	n;
	float	c1;
	float	k;

	c1 = ft_3_vector_cos(norm, direct);
	n = 1.f;
	if (c1 < 0)
	{
		c1 = -c1;
		n = refr1 / refr2;
	}
	else
	{
		norm = ft_3_vector_invert(norm);
		n = 1.0f / n;
	}
	k = 1 - n * n * (1 - c1 * c1);
	return ((k < 0)
			? ft_3_nullpointnew()
			: ft_3_vector_scale(direct, n)
				+ ft_3_vector_scale(norm, n * c1 - sqrtf(k)));
}
