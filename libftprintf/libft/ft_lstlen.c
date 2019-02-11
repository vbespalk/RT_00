/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_len.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 17:35:19 by domelche          #+#    #+#             */
/*   Updated: 2017/11/18 17:39:57 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_lstlen(t_list **head)
{
	unsigned int	i;
	t_list			*lst;

	i = 1;
	if (!head || !*head)
		return (0);
	lst = *head;
	while (lst->next)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
