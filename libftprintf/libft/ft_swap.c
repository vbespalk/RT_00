/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 18:30:51 by domelche          #+#    #+#             */
/*   Updated: 2019/05/25 18:30:59 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swap(void *nb1, void *nb2, size_t size)
{
	unsigned char	swap_tmp[size];

	ft_memcpy(&(*swap_tmp), (nb1), size);
	ft_memcpy((nb1), (nb2), size);
	ft_memcpy((nb2), &(*swap_tmp), size);
}
