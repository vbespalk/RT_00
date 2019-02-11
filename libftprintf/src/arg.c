/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 17:34:31 by domelche          #+#    #+#             */
/*   Updated: 2018/04/13 16:03:36 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

t_arg		*ft_argnew(char *buffer)
{
	t_arg	*arg;

	arg = (t_arg *)ft_memalloc(sizeof(t_arg));
	arg->prec = -1;
	arg->buf = ft_bufnew(buffer);
	return (arg);
}

void		ft_clrarg(t_arg *arg)
{
	t_buf	*tmp;

	tmp = arg->buf;
	free(arg->data);
	ft_bzero(arg, sizeof(t_arg));
	arg->buf = tmp;
	arg->prec = -1;
}

int			ft_isvalid_conv(char c)
{
	return (c == 's' || c == 'd' || c == 'i' || c == 'o' ||
			c == 'u' || c == 'x' || c == 'X' || c == 'c' ||
			c == 'p' || c == '%' || c == 'D' || c == 'C' ||
			c == 'S' || c == 'O' || c == 'U' || c == 'b' ||
			c == 'B');
}

static int	ft_getconv(t_arg *arg, char conv)
{
	char	res;

	res = conv;
	if (ft_isvalid_conv(conv))
		res = (conv != 'X') ? ft_tolower(conv) : conv;
	if (ft_isupper(conv) && conv != 'X')
		arg->lflags |= LF_L;
	if (res == 'c' && (arg->flags & (LF_L | LF_LL)) && MB_CUR_MAX == 1)
		arg->flags &= ~(LF_L | LF_LL);
	arg->flags &= ft_getmask(res);
	return (res);
}

char		*ft_getarg(t_arg *arg, char *format)
{
	format = ft_parse_flags(format, arg);
	arg->width = ft_atoi(format);
	while (ft_isdigit(*format))
		++format;
	if (*format == '.')
		arg->prec = ft_atoi(++format);
	while (ft_isdigit(*format))
		++format;
	format = ft_parse_lflags(format, arg);
	arg->conv = ft_getconv(arg, *format);
	if (arg->prec != -1 && (arg->conv == 'd' || arg->conv == 'i' ||
		arg->conv == 'o' || arg->conv == 'u' || arg->conv == 'x' ||
		arg->conv == 'X' || arg->conv == 'p' || arg->conv == 'b'))
		arg->flags &= ~F_ZERO;
	if (arg->conv == 'o' && (arg->flags & F_SHARP) && arg->prec > 0)
		--arg->prec;
	return (++format);
}
