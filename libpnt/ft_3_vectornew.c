/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3_vectornew.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 11:38:00 by domelche          #+#    #+#             */
/*   Updated: 2018/09/19 11:38:12 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpnt.h"

t_vector		ft_3_vectornew(t_vector origin, t_vector direct)
{
	return (ft_3_pointnew(
		direct[0] - origin[0], direct[1] - origin[1], direct[2] - origin[2]));
}
