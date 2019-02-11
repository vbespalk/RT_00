/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 14:37:13 by domelche          #+#    #+#             */
/*   Updated: 2017/11/06 14:37:14 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnode_int(t_list *node)
{
	int		*content;

	ft_putstr("{ ");
	if (node)
	{
		ft_putstr("content: ");
		if (node->content)
		{
			content = (int *)(node->content);
			ft_putnbr(*content);
		}
		else
			ft_putstr("NULL");
		ft_putstr("; content_size: ");
		ft_putnbr((int)(node->content_size));
		ft_putchar(';');
	}
	else
		ft_putstr("NULL");
	ft_putstr(" }");
}
