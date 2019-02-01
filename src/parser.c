/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 13:21:14 by vbespalk          #+#    #+#             */
/*   Updated: 2018/08/23 13:21:29 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

int		get_str(int fd, char **set, char **str)
{
	char	*tmp;

	tmp = NULL;
	while ((get_next_line(fd, str)) > 0)
	{
		if (*str && **str && !is_tag(*str))
			return (0);
		if (!(tmp = ft_strjoin(*set, *str)))
			return (0);
		free(*set);
		if (!(*set = ft_strnew(ft_strlen(tmp))))
		{
			free(tmp);
			return (0);
		}
		*set = ft_strncpy(*set, tmp, ft_strlen(tmp) + 1);
		free(tmp);
		ft_memdel((void **)str);
	}
	return (1);
}

int		parse_str(char *str, char **set, t_scene *scene)
{
	char	**obj;
	char	*s;
	int		i;
	int		j;
	int		nb;

	obj = (char *[7]){"plane {", "sphere {", "cylinder {", "cone {", \
	"light {", "camera {", NULL};
	if (!(set = ft_strsplit(str, '}')))
		return (0);
	nb = 0;
	while (set[++nb] && (i = -1))
		;
	while (set[++i] != 0 && (j = -1))
	{
		while (obj[++j])
			if ((s = ft_ptrtostr(set[i], obj[j])))
			{
				if (!to_struct(scene, s, j))
					return (clear_mem(&set, nb + 1));
				break ;
			}
	}
	clear_mem(&set, nb + 1);
	return (1);
}

int		parser(int fd, t_scene *scene)
{
	char	*set;
	char	*str;

	ft_bzero(scene, sizeof(t_scene));
	set = NULL;
	str = NULL;
	if ((!get_str(fd, &set, &str)))
	{
		free(set);
		ft_memdel((void **)&str);
		return (0);
	}
	ft_memdel((void **)&str);
	if (!parse_str(set, &str, scene))
	{
		struct_del(scene);
		free(set);
		return (0);
	}
	free(set);
	return (1);
}
