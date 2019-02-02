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

t_point3	ft_3_line_line_inter
	(t_point3 o1, t_point3 d1, t_point3 o2, t_point3 d2)
{
	float		t;
	float		len;
	t_point3	den;

	den = ft_3_vector_cross(d1, d2);
	if ((len = ft_3_vector_len(den)) == 0.0)
		return (ft_3_nullpointnew());
	t = ft_3_vector_dot(
		ft_3_vector_cross(ft_3_vectornew(o1, o2), d2), den) /pow(len, 2);
	return (ft_3_vector_add(o1, ft_3_vector_scale(d1, t)));
}
