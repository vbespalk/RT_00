/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nodenew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 17:48:05 by domelche          #+#    #+#             */
/*   Updated: 2018/03/15 17:48:09 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_nodenew(void *content, size_t content_size)
{
	t_list	*node;

	node = ft_smemalloc(sizeof(t_list), "ft_nodenew");
	node->content = content;
	node->content_size = (content) ? content_size : 0;
	node->next = NULL;
	return (node);
}
