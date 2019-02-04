/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3_pointnew.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 11:18:25 by domelche          #+#    #+#             */
/*   Updated: 2018/09/19 11:18:32 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpnt.h"

t_vector	ft_3_pointnew(float x, float y, float z)
{
	t_vector	point;

	point[0] = x;
	point[1] = y;
	point[2] = z;
	return (point);
}
