/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 17:46:11 by domelche          #+#    #+#             */
/*   Updated: 2017/11/01 17:46:12 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*node;
	t_list	*next;

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
