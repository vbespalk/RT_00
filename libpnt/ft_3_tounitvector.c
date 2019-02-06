/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3_tounitvector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 11:39:44 by domelche          #+#    #+#             */
/*   Updated: 2018/09/19 11:40:07 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpnt.h"

t_vector		ft_3_tounitvector(t_vector vec)
{
	float	len;

	len = ft_3_vector_len(vec);
	return ((t_vector){vec[0] / len, vec[1] / len, vec[2] / len});
}
