/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_filesize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 15:15:59 by domelche          #+#    #+#             */
/*   Updated: 2018/07/22 15:17:23 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_get_filesize(char *file_name)
{
	int		fd;
	size_t	size;
	int		res;
	char	buf[BUFF_SIZE];

	if ((fd = open(file_name, O_RDONLY)) < 0)
		return (0);
	if (read(fd, NULL, 0) < 0)
		return (0);
	size = 0;
	while ((res = read(fd, buf, BUFF_SIZE)) > 0)
		size += res;
	close(fd);
	return (size);
}
