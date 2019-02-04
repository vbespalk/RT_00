/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3_line_line_dist.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 11:32:20 by domelche          #+#    #+#             */
/*   Updated: 2018/09/19 18:50:28 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpnt.h"

float		ft_3_line_line_dist
				(t_vector o1, t_vector d1, t_vector o2, t_vector d2)
{
	t_vector	axb;

	axb = ft_3_vector_cross(d1, d2);
	return ((float)fabs(ft_3_vector_dot(o2 + o1 * -1.0f, axb)) /
		ft_3_vector_len(axb));
}
