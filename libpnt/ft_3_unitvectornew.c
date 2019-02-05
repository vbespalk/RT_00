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

t_vector		ft_3_unitvectornew(t_vector origin, t_vector direct)
{
	return (ft_3_tounitvector(direct - origin));
}
