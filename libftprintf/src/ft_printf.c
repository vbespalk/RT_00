/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 17:35:29 by domelche          #+#    #+#             */
/*   Updated: 2018/05/05 14:54:28 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

static int	ft_print_format(va_list *ap, char *f, t_arg *arg)
{
	while (f && *f)
	{
		if (*f != '%')
			ft_putchar_buf(arg->buf, *(f++));
		else
			f = ft_putarg(++f, ap, arg);
	}
	ft_putbuf(arg->buf, arg->buf->i);
	return (arg->buf->res);
}

int			ft_printf(const char *format, ...)
{
	va_list ap;
	char	**f;
	char	buf[BUFF_SIZE];
	int		res;
	t_arg	*arg;

	if (!ft_strchr(format, '%'))
	{
		ft_putstr(format);
		return ((int)ft_strlen(format));
	}
	if (!(f = (char **)malloc(sizeof(char *) * 2)))
		return (-1);
	va_start(ap, format);
	f[0] = ft_strdup(format);
	f[1] = f[0];
	arg = ft_argnew(buf);
	res = ft_print_format(&ap, f[0], arg);
	va_end(ap);
	free(f[1]);
	free(arg->buf);
	free(arg);
	free(f);
	return (res);
}
