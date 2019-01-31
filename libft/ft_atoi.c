/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 18:49:36 by domelche          #+#    #+#             */
/*   Updated: 2018/03/31 14:14:30 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "atoi_basic.h"

long long	ft_atoi(const char *str)
{
	if (!str)
		return (0);
	return (ft_atoi_basic(str, 10));
}
