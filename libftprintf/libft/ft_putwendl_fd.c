/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwendl_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 13:37:57 by domelche          #+#    #+#             */
/*   Updated: 2018/03/31 13:38:05 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putwendl_fd(const wchar_t *wstr, int fd)
{
	ft_putwstr_fd(wstr, fd);
	ft_putchar_fd('\n', fd);
}
