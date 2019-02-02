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
	(t_point3 o1, t_point3 d1, t_point3 o2, t_point3 d2)
{
	t_point3	axb;

	axb = ft_3_vector_cross(d1, d2);
	return ((float)fabs(
		ft_3_vector_dot(
			ft_3_vector_add(o2, ft_3_vector_scale(o1, -1)), axb)) /
		ft_3_vector_len(axb));
}
