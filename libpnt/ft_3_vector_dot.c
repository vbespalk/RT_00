/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3_vector_dot.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 11:40:53 by domelche          #+#    #+#             */
/*   Updated: 2018/09/19 11:41:09 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpnt.h"

float	ft_3_vector_dot(t_vector vec_1, t_vector vec_2)
{
	return ((vec_1[0] * vec_2[0] + vec_1[1] * vec_2[1] + vec_1[2] * vec_2[2]));
}

double	ft_3_vector_db_dot(t_vector vec_1, t_vector vec_2)
{
	return (((double)vec_1[0] * vec_2[0] + (double)vec_1[1] * vec_2[1] +
		(double)vec_1[2] * vec_2[2]));
}
