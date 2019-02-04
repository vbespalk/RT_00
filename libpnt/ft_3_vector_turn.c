/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3_vector_turn.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 11:44:07 by domelche          #+#    #+#             */
/*   Updated: 2018/09/19 11:44:30 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpnt.h"

t_vector		ft_3_vector_turn(t_vector proj, t_vector norm, float angle)
{
	return (proj * (float)sin(angle) +	norm * (float)cos(angle));
}
