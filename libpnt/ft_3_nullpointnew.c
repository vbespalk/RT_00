/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3_nullpointnew.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 11:18:58 by domelche          #+#    #+#             */
/*   Updated: 2018/09/19 11:21:18 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpnt.h"

t_vector	ft_3_nullpointnew(void)
{
	return ((t_vector) { -FLT_MAX, -FLT_MAX, -FLT_MAX });
}

t_vector	ft_3_zeropointnew(void)
{
	return ((t_vector) { FLT_MIN, FLT_MIN, FLT_MIN });
}