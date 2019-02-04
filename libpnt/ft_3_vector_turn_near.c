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
	rotated[0] = vec[0] * (axis[0] * axis[0] * va + cos_a) +
				vec[1] * (axis[0] * axis[1] * va - axis[2] * sin_a) +
				vec[2] * (axis[0] * axis[2] * va + axis[1] * sin_a);
	rotated[1] = vec[0] * (axis[0] * axis[1] * va + axis[2] * sin_a) +
				vec[1] * (axis[1] * axis[1] * va + cos_a) +
				vec[2] * (axis[1] * axis[2] * va - axis[0] * sin_a);
	rotated[2] = vec[0] * (axis[0] * axis[2] * va - axis[1] * sin_a) +
				vec[1] * (axis[1] * axis[2] * va + axis[0] * sin_a) +
				vec[2] * (axis[2] * axis[2] * va + cos_a);
	return (rotated);
}
