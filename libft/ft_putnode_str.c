/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnode_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 14:59:35 by domelche          #+#    #+#             */
/*   Updated: 2017/11/06 14:59:36 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnode_str(t_list *node)
{
	char	*content;

	ft_putstr("{ ");
	if (node)
	{
		ft_putstr("content: ");
		if (node->content)
		{
			content = (char *)(node->content);
			ft_putstr(content);
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
