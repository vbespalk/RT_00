/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlist_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 15:22:46 by domelche          #+#    #+#             */
/*   Updated: 2017/11/06 15:22:48 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putlist_str(t_list *head)
{
	ft_putnode_str(head);
	if (head->next)
	{
		ft_putchar('\n');
		ft_putlist_str(head->next);
	}
	else
		ft_putchar('\n');
}
