/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3_vector_turn.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 11:44:07 by domelche          #+#    #+#             */
/*   Updated: 2018/09/19 11:44:30 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpnt.h"

t_point3		ft_3_vector_turn(t_point3 proj, t_point3 norm, float angle)
{
	return (ft_3_vector_add(
		ft_3_vector_scale(proj, (float)sin(angle)),
		ft_3_vector_scale(norm, (float)cos(angle))));
}
