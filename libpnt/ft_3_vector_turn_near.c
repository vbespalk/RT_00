/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3_vector_turn_near.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 11:46:26 by domelche          #+#    #+#             */
/*   Updated: 2018/09/19 11:46:57 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpnt.h"

/*
**	turn vec towards axis on angle
*/

t_vector		ft_3_vector_turn_near(t_vector vec, t_vector axis, float angle)
{
	t_vector	rotated;
	float		sin_a;
	float		cos_a;
	float		va;

	sin_a = (float)sin(angle);
	cos_a = (float)cos(angle);
	va = 1 - cos_a;
	rotated.x = vec[0] * (axis.x * axis.x * va + cos_a) +
				vec[1] * (axis.x * axis.y * va - axis.z * sin_a) +
				vec[2] * (axis.x * axis.z * va + axis.y * sin_a);
	rotated.y = vec[0] * (axis.x * axis.y * va + axis.z * sin_a) +
				vec[1] * (axis.y * axis.y * va + cos_a) +
				vec[2] * (axis.y * axis.z * va - axis.x * sin_a);
	rotated.z = vec[0] * (axis.x * axis.z * va - axis.y * sin_a) +
				vec[1] * (axis.y * axis.z * va + axis.x * sin_a) +
				vec[2] * (axis.z * axis.z * va + cos_a);
	return (rotated);
}
