/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrplc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 14:42:32 by domelche          #+#    #+#             */
/*   Updated: 2018/05/05 14:46:55 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strrplc(char *str, char find, char put)
{
	if (!str)
		return ;
	while (*str)
	{
		if (*str == find)
			*str = put;
		++str;
	}
}
