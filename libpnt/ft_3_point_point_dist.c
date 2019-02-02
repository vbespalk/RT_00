/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3_point_point_dist.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 11:22:48 by domelche          #+#    #+#             */
/*   Updated: 2018/09/19 11:23:07 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpnt.h"

float		ft_3_point_point_dist(t_point3 pnt_0, t_point3 pnt_1)
{
	return ((float)sqrt(
		pow(pnt_1.x - pnt_0.x, 2) +
		pow(pnt_1.y - pnt_0.y, 2) +
		pow(pnt_1.z - pnt_0.z, 2)));
}
