/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3_vector_random_cone.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 18:58:25 by domelche          #+#    #+#             */
/*   Updated: 2019/05/25 18:58:27 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpnt.h"

t_vector	ft_3_vector_random_cone(t_vector d, float cone_angle)
{
	t_vector	rand;
	float		angle;
	float		turn_angle;

	rand = ft_3_vector_random();
	while (ft_3_pointcmp(d, rand, 1e-6))
		rand = ft_3_vector_random();
	angle = acosf(ft_3_vector_cos(d, rand));
	turn_angle = 0.0f;
	while (angle - turn_angle > cone_angle)
		turn_angle += cone_angle * 2.0f;
	rand = ft_3_vector_turn(
		ft_3_tounitvector(ft_3_vector_project(rand, d)), rand, turn_angle);
	return (rand);
}
