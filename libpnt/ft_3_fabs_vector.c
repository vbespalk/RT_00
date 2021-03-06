/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3_fabs_vector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 18:57:28 by domelche          #+#    #+#             */
/*   Updated: 2019/05/25 18:57:32 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpnt.h"

t_vector	ft_3_fabsf_vector(t_vector vec)
{
	return ((t_vector){fabsf(vec[0]), fabsf(vec[1]), fabsf(vec[2])});
}
