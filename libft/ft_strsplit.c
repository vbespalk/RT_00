/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 18:14:12 by domelche          #+#    #+#             */
/*   Updated: 2017/10/30 18:14:13 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_len(char *str, char c)
{
	int		i;

	i = 0;
	while (str[i] != c && str[i] != 0)
		i++;
	return (i);
}

static int	ft_words_count(char *s, char c)
{
	int		i;

	i = 0;
	while (1)
	{
		while (*s == c)
			s++;
		if (*s)
			i++;
		else
			return (i);
		while (*s != c && *s != 0)
			s++;
	}
	return (i);
}

static char	*ft_wordcpy(char *dst, char *src, char c)
{
	int		i;

	i = 0;
	while (src[i] != 0 && src[i] != c)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (dst);
}

static char	**ft_maketab(char **tab, char *str, int words_count, char c)
{
	int		i;
	int		counter;
	int		word_len;

	i = 0;
	counter = 0;
	word_len = 0;
	while (i < words_count)
	{
		while (str[counter] == c)
			counter++;
		word_len = ft_word_len(&str[counter], c);
		if (!(tab[i] = (char *)malloc(sizeof(char) * (word_len + 1))))
		{
			while (--i >= 0)
				free(tab[i]);
			free(tab);
			return (NULL);
		}
		tab[i] = ft_wordcpy(tab[i], &str[counter], c);
		counter += word_len;
		i++;
	}
	tab[i] = 0;
	return (tab);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab;
	char	*str;
	int		words_count;

	if (s)
	{
		str = (char *)s;
		words_count = ft_words_count((char *)s, c);
		if (!(tab = (char **)malloc(sizeof(char *) * (words_count + 1))))
			return (NULL);
		return (ft_maketab(tab, str, words_count, c));
	}
	return (NULL);
}
