/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3_line_plane_inter.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 11:30:44 by domelche          #+#    #+#             */
/*   Updated: 2018/09/19 11:32:01 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpnt.h"

t_point3	ft_3_line_plane_inter
				(t_point3 pln_o, t_point3 pln_norm,
				t_point3 ln_o, t_point3 ln_d)
{
	float		t;
	float		dev;

	dev = ft_3_vector_dot(pln_norm, ln_d);
	if (!dev)
		return (ft_3_nullpointnew());
	t = (ft_3_vector_dot(pln_norm, pln_o) -
		ft_3_vector_dot(pln_norm, ln_o)) / dev;
	return (ft_3_vector_add(ln_o, ft_3_vector_scale(ln_d, t)));
}
