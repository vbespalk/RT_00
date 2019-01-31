/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 19:48:40 by domelche          #+#    #+#             */
/*   Updated: 2017/11/18 19:48:42 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlstnew(void const *content, size_t content_size)
{
	t_dlist	*node;

	if (!(node = (t_dlist *)malloc(sizeof(t_dlist))))
		return (NULL);
	if (content != NULL)
	{
		if (!(node->content = malloc(content_size)))
			return (NULL);
		node->content = ft_memmove(node->content, content, content_size);
	}
	else
	{
		node->content = NULL;
		content_size = 0;
	}
	node->content_size = content_size;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}
