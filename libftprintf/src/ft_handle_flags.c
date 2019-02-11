/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 16:06:48 by domelche          #+#    #+#             */
/*   Updated: 2018/05/05 14:59:39 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

void	ft_handle_left_pad(t_arg *arg)
{
	int		i;

	if ((arg->flags & F_ZERO) || (arg->flags & F_MINUS) || !arg->pad_len)
		return ;
	i = -1;
	while (++i < arg->pad_len)
		ft_putchar_buf(arg->buf, ' ');
}

void	ft_handle_sharp(t_arg *arg)
{
	char	sharp_str[3];

	if (arg->sign)
		ft_putchar_buf(arg->buf, arg->sign);
	if (!arg->sharp_len)
		return ;
	sharp_str[0] = '0';
	sharp_str[1] = 0;
	sharp_str[2] = 0;
	if (arg->conv == 'p')
		sharp_str[1] = 'x';
	else if (arg->conv != 'o')
		sharp_str[1] = arg->conv;
	ft_putstr_buf(arg->buf, sharp_str);
}

void	ft_handle_zero_pad(t_arg *arg)
{
	int		i;

	i = -1;
	if ((arg->flags & F_ZERO) && !(arg->flags & F_MINUS) && arg->pad_len)
		while (++i < arg->pad_len)
			ft_putchar_buf(arg->buf, '0');
	if (arg->conv == 'c' || arg->conv == 's')
		return ;
	i = -1;
	while (++i < arg->prec_len)
		ft_putchar_buf(arg->buf, '0');
}

void	ft_handle_data(t_arg *arg)
{
	int		i;

	if (arg->conv == 'c' && !*(arg->data))
		ft_putchar_buf(arg->buf, 0);
	else if ((arg->conv == 's') &&
		arg->prec < arg->data_len && arg->prec != -1)
		ft_putnchar_buf(arg->buf, arg->data, arg->prec);
	else
		ft_putstr_buf(arg->buf,
			(arg->sign == '-') ? arg->data + sizeof(char) : arg->data);
	if ((arg->flags & F_ZERO) || !(arg->flags & F_MINUS) || !arg->pad_len)
		return ;
	i = -1;
	while (++i < arg->pad_len)
		ft_putchar_buf(arg->buf, ' ');
}

void	ft_handle_flags(t_arg *arg)
{
	arg->prec_len = (arg->prec > arg->data_len) ? arg->prec - arg->data_len : 0;
	if (arg->flags & F_SHARP)
		arg->sharp_len = (arg->conv == 'o') ? 1 : 2;
	if (arg->sign != '-')
	{
		if (arg->flags & F_SPACE)
			arg->sign = ' ';
		else if (arg->flags & F_PLUS)
			arg->sign = '+';
	}
	arg->pad_len = arg->width - arg->data_len - ((arg->sign) ? 1 : 0) -
		arg->sharp_len - ((arg->conv == 's' || arg->conv == 'c') ?
		0 : arg->prec_len);
	arg->pad_len = (arg->pad_len < 0) ? 0 : arg->pad_len;
	ft_handle_left_pad(arg);
	ft_handle_sharp(arg);
	ft_handle_zero_pad(arg);
	ft_handle_data(arg);
}
