/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3_pointcmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 11:36:18 by domelche          #+#    #+#             */
/*   Updated: 2018/09/19 11:37:19 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpnt.h"

int			ft_3_pointcmp(t_point3 pnt_0, t_point3 pnt_1, float prec)
{
	return (ft_3_point_point_dist(pnt_0, pnt_1) < prec);
}
