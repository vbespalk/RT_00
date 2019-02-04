/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3_vector_rotate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 11:45:49 by domelche          #+#    #+#             */
/*   Updated: 2018/09/19 11:46:09 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpnt.h"

t_vector		ft_3_vector_rotate
					(t_vector vec, float alpha, float beta, float gamma)
{
	t_vector	rotated;
	t_vector	sin_;
	t_vector	cos_;

	sin_[0] = (float)sin(alpha);
	sin_[1] = (float)sin(beta);
	sin_[2] = (float)sin(gamma);
	cos_[0] = (float)cos(alpha);
	cos_[1] = (float)cos(beta);
	cos_[2] = (float)cos(gamma);
	rotated.x = vec[0] * cos_[2] * cos_[1] +
				vec[1] * (cos_[2] * sin_[1] * sin_[0] - sin_[2] * cos_[0]) +
				vec[2] * (sin_[2] * sin_[0] + cos_[0] * cos_[2] * sin_[1]);
	rotated.y = vec[0] * cos_[1] * sin_[2] +
				vec[1] * (cos_[0] * cos_[2] + sin_[0] * sin_[1] * sin_[2]) +
				vec[2] * (cos_[0] * sin_[1] * sin_[2] - sin_[0] * cos_[2]);
	rotated.z = vec[0] * -(sin_[1]) +
				vec[1] * sin_[0] * cos_[1] +
				vec[2] * cos_[0] * cos_[1];
	return (rotated);
}
