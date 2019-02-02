/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3_line_point_proj.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 11:35:13 by domelche          #+#    #+#             */
/*   Updated: 2018/09/19 11:35:39 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpnt.h"

t_point3	ft_3_line_point_proj
				(t_point3 origin, t_point3 direct, t_point3 point)
{
	return (ft_3_line_plane_inter(point, direct, origin, direct));
}
