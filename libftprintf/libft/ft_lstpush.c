/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 15:24:33 by domelche          #+#    #+#             */
/*   Updated: 2017/11/06 15:24:34 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpush(t_list **alst, t_list *new)
{
	t_list	*tmp;

	if (new)
	{
		if (alst)
		{
			if (*alst)
			{
				tmp = *alst;
				while (tmp->next)
					tmp = tmp->next;
				tmp->next = new;
			}
			else
				*alst = new;
		}
		else
			alst = &new;
	}
}
