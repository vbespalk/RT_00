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

t_point3		ft_3_tounitvector(t_point3 vec)
{
	float	len;

	len = ft_3_vector_len(vec);
	return (ft_3_pointnew(vec.x / len, vec.y / len, vec.z / len));
}
