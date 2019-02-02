/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3_unitvectornew.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 11:38:26 by domelche          #+#    #+#             */
/*   Updated: 2018/09/19 11:38:51 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpnt.h"

t_point3		ft_3_unitvectornew(t_point3 origin, t_point3 direct)
{
	t_point3	vec;

	vec = ft_3_vectornew(origin, direct);
	return (ft_3_vector_scale(vec, 1.0f / ft_3_vector_len(vec)));
}
