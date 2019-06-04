/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3_line_line_inter.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 11:34:13 by domelche          #+#    #+#             */
/*   Updated: 2018/09/19 11:34:55 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpnt.h"

t_vector	ft_3_line_line_inter(
				t_vector o1, t_vector d1, t_vector o2, t_vector d2)
{
	float		t;
	float		len;
	t_vector	den;

	den = ft_3_vector_cross(d1, d2);
	if ((len = ft_3_vector_len(den)) == 0.0)
		return (ft_3_nullpointnew());
	t = ft_3_vector_dot(
		ft_3_vector_cross((o2 - o1), d2), den) /
			(float)pow(len, 2);
	return (o1 + ft_3_vector_scale(d1, t));
}
