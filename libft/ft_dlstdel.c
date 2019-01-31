/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstdel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 19:41:52 by domelche          #+#    #+#             */
/*   Updated: 2017/11/18 19:41:53 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstdel(t_dlist **alst, void (*del)(void *, size_t))
{
	t_dlist	*node;
	t_dlist	*next;

	if (alst && *alst && del)
	{
		node = *alst;
		while (node)
		{
			next = node->next;
			del(node->content, node->content_size);
			free(node);
			node = next;
		}
		*alst = NULL;
	}
}
