/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3_vector_project.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 11:45:24 by domelche          #+#    #+#             */
/*   Updated: 2018/09/19 11:45:35 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpnt.h"

t_point3		ft_3_vector_project(t_point3 norm, t_point3 vec)
{
	return (ft_3_vector_add(
			vec, ft_3_vector_scale(
				norm, (ft_3_vector_len(vec) * -ft_3_vector_cos(norm, vec)) /
					ft_3_vector_len(norm))));
}
