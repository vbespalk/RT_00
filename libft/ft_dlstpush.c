/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstpush.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 19:51:08 by domelche          #+#    #+#             */
/*   Updated: 2017/11/18 19:51:09 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstpush(t_dlist **alst, t_dlist *new)
{
	t_dlist	*tmp;

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
				tmp->next->prev = tmp;
			}
			else
				*alst = new;
		}
		else
			alst = &new;
	}
}
