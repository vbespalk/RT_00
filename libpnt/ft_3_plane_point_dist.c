/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3_plane_point_dist.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 11:24:11 by domelche          #+#    #+#             */
/*   Updated: 2018/09/19 11:24:33 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpnt.h"

float		ft_3_plane_point_dist
				(t_vector origin, t_vector norm, t_vector point)
{
	return (norm[0] * (point[0] - origin[0]) +
			norm[1] * (point[1] - origin[1]) +
			norm[2] * (point[2] - origin[2])) / ft_3_vector_len(norm);
}
