/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3_vector_cross.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 11:41:33 by domelche          #+#    #+#             */
/*   Updated: 2018/09/19 11:41:53 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpnt.h"

t_point3		ft_3_vector_cross(t_point3 vec_1, t_point3 vec_2)
{
	return (ft_3_pointnew(vec_1.y * vec_2.z - vec_1.z * vec_2.y,
		vec_1.z * vec_2.x - vec_1.x * vec_2.z,
		vec_1.x * vec_2.y - vec_1.y * vec_2.x));
}
