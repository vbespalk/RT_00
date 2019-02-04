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

float		ft_3_point_point_dist(t_vector pnt_0, t_vector pnt_1)
{
	return ((float)sqrt(
		pow(pnt_1[0] - pnt_0[0], 2) +
		pow(pnt_1[1] - pnt_0[1], 2) +
		pow(pnt_1[2] - pnt_0[2], 2)));
}
