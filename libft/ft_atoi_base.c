/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 15:15:19 by domelche          #+#    #+#             */
/*   Updated: 2018/07/22 15:16:54 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "atoi_basic.h"

long long	ft_atoi_base(const char *str, int base)
{
	if (!str || base < 2 || base > 16)
		return (0);
	return (ft_atoi_basic(str, base));
}
