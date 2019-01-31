/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_smemalloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 17:39:37 by domelche          #+#    #+#             */
/*   Updated: 2018/02/15 17:53:48 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <errno.h>
#include <stdio.h>

void	*ft_smemalloc(size_t size, char *ft_name)
{
	void	*mem;

	if (!(mem = ft_memalloc(size)))
	{
		ft_putstr("Error: memory allocation fails at ");
		ft_putendl(ft_name);
		exit(EXIT_FAILURE);
	}
	return (mem);
}
