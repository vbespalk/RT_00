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

t_vector		ft_3_vector_project(t_vector norm, t_vector vec)
{
	return (vec + norm * (ft_3_vector_len(vec) * \
		-ft_3_vector_cos(norm, vec)) / ft_3_vector_len(norm));
}
