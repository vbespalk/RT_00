/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3_vector_reflect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 11:43:26 by domelche          #+#    #+#             */
/*   Updated: 2018/09/19 11:43:47 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpnt.h"

t_vector	ft_3_vector_reflect(t_vector origin, t_vector coll, t_vector norm)
{
	t_vector		oc;

	oc = coll - origin;
	return (ft_3_unitvectornew(
		coll, origin + ft_3_vector_scale(
			(coll + ft_3_vector_scale(
				norm, (ft_3_vector_len(oc) * -ft_3_vector_cos(oc, norm))))
			- origin, 2.0f)));
}
