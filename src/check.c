/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:25:41 by vbespalk          #+#    #+#             */
/*   Updated: 2018/08/20 18:25:42 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		is_tag(char *s)
{
	char		**objs;
	char		**prop;
	int			i;
	static int	propetry;

	objs = (char *[7]){"camera {", "light {", "plane {", "sphere {", \
	"cylinder {", "cone {", NULL};
	prop = (char *[9]){"\tpos(", "\tdir(", "\tcol(", "\trad(", "\trot(", \
	"\tsize(", "\tdiffuse(", "\treflect(", NULL};
	i = -1;
	if (!propetry)
		while (objs[++i])
			if (ft_strequ(s, objs[i]))
				return (propetry = 1);
	if (propetry)
	{
		if (*s == '}')
			propetry = 0;
		if (*s == '}' && (*(s + 1)))
			return (0);
		while (prop[++i])
			if (ft_strstr(s, prop[i]) || *s == '{' || *s == '}')
				return (1);
	}
	return (0);
}

int		get_vec(char *s, t_vector *vec)
{
	int		i;
	int		j;
	int		count;

	count = 0;
	i = 0;
	j = 0;
	if (!s)
		return (0);
	(*vec)[count++] = ft_atoi(s);
	while (*s)
	{
		if ((ft_isdigit(*s) || (*s == '-' && (ft_isdigit(*(s + 1))))) && !j)
			s++;
		else if (*s == ',' && ++i <= 2)
			(*vec)[count++] = ft_atoi(++s);
		else if (*s == ')' && !j++)
			s++;
		else
			return (0);
	}
	if (i != 2 || !j)
		return (0);
	return (1);
}

int		get_col(char *s, t_vector *vec)
{
	int		i;
	int		j;
	int		count;

	count = 0;
	i = 0;
	j = 0;
	if (!s)
		return (0);
	(*vec)[count++] = ft_atoi(s);
	while (*s)
	{
		if (ft_isdigit(*s) && !j)
			s++;
		else if (*s == ',' && ++i <= 2)
			(*vec)[count++] = ft_atoi(++s);
		else if (*s == ')' && !j++)
			s++;
		else
			return (0);
	}
	if (i != 2 || !j)
		return (0);
	return (1);
}

int		get_val(char *s, unsigned int *val)
{
	int		j;

	j = 0;
	if (!s)
		return (0);
	*val = ft_atoi(s);
	while (*s)
	{
		if (ft_isdigit(*s) && !j)
			s++;
		else if (*s == ')' && !j++)
			s++;
		else
			return (0);
	}
	if (!j)
		return (0);
	return (1);
}
