/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 13:41:05 by domelche          #+#    #+#             */
/*   Updated: 2018/03/31 14:22:25 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "itoa_basic.h"

char		*ft_uitoa_base(unsigned long long num, int base)
{
	if (base < 2 || base > 16)
		return (NULL);
	return (ft_itoa_basic(num, 0, base));
}
