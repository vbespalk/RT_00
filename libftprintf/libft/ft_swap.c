//
// Created by ivoriik on 11.04.19.
//
#include "libft.h"

void	ft_swap(void *nb1, void *nb2, size_t size)
{
	unsigned char	swap_tmp[size];

	ft_memcpy(&(*swap_tmp), (nb1), size);
	ft_memcpy((nb1), (nb2), size);
	ft_memcpy((nb2), &(*swap_tmp), size);
}
