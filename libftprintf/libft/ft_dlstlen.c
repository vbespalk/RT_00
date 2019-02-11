/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 20:24:56 by domelche          #+#    #+#             */
/*   Updated: 2017/11/18 20:24:57 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_dlstlen(t_dlist **head)
{
	unsigned int	i;
	t_dlist			*lst;

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
