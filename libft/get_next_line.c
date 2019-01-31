/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 16:41:02 by domelche          #+#    #+#             */
/*   Updated: 2018/01/31 16:46:55 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_stradd(char *s1, size_t *len1, char *s2, size_t len2)
{
	char	*str;
	size_t	i;

	if (!(str = (char *)ft_memalloc(*len1 + len2)))
		return (NULL);
	i = -1;
	while (++i < *len1)
		str[i] = s1[i];
	i--;
	while (++i < *len1 + len2)
		str[i] = s2[i - *len1];
	ft_memdel((void **)&s1);
	*len1 += len2;
	return (str);
}

static int		ft_quit(int ret, char **line, size_t size)
{
	if (size != 0 && (*line)[size - 1] == '\n')
		size--;
	*line = ft_stradd(*line, &size, "\0", 1);
	if (ret == 0 && size > 1)
		ret = 1;
	if (ret == 0 || size == 1)
	{
		free(*line);
		if (!(*line = (char *)ft_memalloc(sizeof(char))))
			return (-1);
	}
	return (ret);
}

static t_file	*ft_getfile(int fd, t_list **ahead)
{
	t_list		*node;
	t_file		*file;

	node = *ahead;
	while (node)
	{
		if (((t_file *)(node->content))->fd == fd)
			return ((t_file *)(node->content));
		node = node->next;
	}
	if (!(file = (t_file *)ft_memalloc(sizeof(t_file))))
		return (NULL);
	file->fd = fd;
	if (!(file->buf = (char *)ft_memalloc(BUFF_SIZE)))
		return (NULL);
	file->i = BUFF_SIZE;
	file->buf_size = BUFF_SIZE;
	ft_lstpush(ahead, ft_lstnew((void *)file, sizeof(*file)));
	free(file);
	node = *ahead;
	while (node->next)
		node = node->next;
	return ((t_file *)(node->content));
}

static int		ft_is_there_newl(t_file *file, char **line, size_t *size)
{
	size_t	start;

	start = file->i;
	while (file->i < file->buf_size)
	{
		if (file->buf[file->i] == '\n')
		{
			*line = ft_stradd(*line, size,
				&(file->buf[start]), file->i - start + 1);
			file->i += ((file->i == file->buf_size) ? 0 : 1);
			return (1);
		}
		file->i++;
	}
	*line = ft_stradd(*line, size, &(file->buf[start]), file->i - start);
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*head;
	t_file			*file;
	size_t			size;

	if (!line || (read(fd, NULL, 0) == -1) || BUFF_SIZE < 1)
		return (-1);
	*line = NULL;
	size = 0;
	file = ft_getfile(fd, &head);
	if (ft_is_there_newl(file, line, &size))
		return (ft_quit(1, line, size));
	while (1)
	{
		file->i = 0;
		if (!(file->buf_size = read(fd, file->buf, BUFF_SIZE)))
			return (ft_quit(0, line, size));
		if (ft_is_there_newl(file, line, &size))
			return (ft_quit(1, line, size));
		ft_bzero((void *)(file->buf), BUFF_SIZE);
	}
	return (-1);
}
