/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 15:14:07 by domelche          #+#    #+#             */
/*   Updated: 2018/07/22 15:14:20 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_readfile(char *file_name)
{
	char	*content;
	int		fd;
	size_t	size;
	size_t	tmp;

	if (!(size = ft_get_filesize(file_name)))
		return (NULL);
	if (!(content = malloc(size + 1)))
		return (NULL);
	fd = open(file_name, O_RDONLY);
	if (size <= UINT_MAX)
		read(fd, content, size);
	else
	{
		tmp = size;
		while (tmp > UINT_MAX)
		{
			read(fd, content, UINT_MAX);
			tmp -= UINT_MAX;
		}
		read(fd, content, tmp);
	}
	content[size] = 0;
	close(fd);
	return (content);
}
