/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3_line_point_dist.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 11:23:26 by domelche          #+#    #+#             */
/*   Updated: 2018/09/19 11:23:50 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpnt.h"

float		ft_3_line_point_dist
				(t_point3 origin, t_point3 direct, t_point3 point)
{
	return (ft_3_vector_len(ft_3_vector_cross(direct,
		ft_3_vectornew(point, origin))));
}
