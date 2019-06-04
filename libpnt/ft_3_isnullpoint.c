/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3_isnullpoint.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 11:21:55 by domelche          #+#    #+#             */
/*   Updated: 2018/09/19 11:22:23 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpnt.h"

int		ft_3_isnullpoint(t_vector point)
{
	return (point[0] == -FLT_MAX
			&& point[1] == -FLT_MAX
			&& point[2] == -FLT_MAX);
}

int		ft_3_iszeropoint(t_vector point)
{
	return (point[0] == FLT_MIN
			&& point[1] == FLT_MIN
			&& point[2] == FLT_MIN);
}
