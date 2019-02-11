/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlist_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 15:09:14 by domelche          #+#    #+#             */
/*   Updated: 2017/11/06 15:09:16 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putlist_int(t_list *head)
{
	ft_putnode_int(head);
	if (head->next)
	{
		ft_putchar('\n');
		ft_putlist_int(head->next);
	}
	else
		ft_putchar('\n');
}
