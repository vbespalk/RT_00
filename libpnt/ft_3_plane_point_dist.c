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
				(t_point3 origin, t_point3 norm, t_point3 point)
{
	return (norm.x * (point.x - origin.x) + norm.y * (point.y - origin.y) +
		norm.z * (point.z - origin.z)) / ft_3_vector_len(norm);
}
