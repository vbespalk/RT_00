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

t_vector	ft_3_line_point_proj(
				t_vector origin, t_vector direct, t_vector point)
{
	return (ft_3_line_plane_inter(point, direct, origin, direct));
}
