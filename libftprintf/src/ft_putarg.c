/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putarg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 15:54:11 by domelche          #+#    #+#             */
/*   Updated: 2018/05/05 14:59:15 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

static char	*ft_argtoa(t_arg *arg, va_list *ap)
{
	char	*str;

	if (!ft_isvalid_conv(arg->conv))
	{
		if (!(str = (char *)ft_memalloc(2 * sizeof(char))))
			return (NULL);
		str[0] = arg->conv;
		arg->conv = 'c';
	}
	else
	{
		if (arg->conv == '%')
			str = ft_strdup("%");
		else if (arg->conv == 'd' || arg->conv == 'i')
			str = ft_getstr_arg_i(arg, ap);
		else if (arg->conv == 'p')
			str = ft_getstr_arg_p(arg, ap);
		else if (arg->conv == 'c')
			str = ft_getstr_arg_c(arg, ap);
		else if (arg->conv == 's')
			str = ft_getstr_arg_s(arg, ap);
		else
			str = ft_getstr_arg_u(arg, ap);
	}
	return (str);
}

char		*ft_putarg(char *format, va_list *ap, t_arg *arg)
{
	format = ft_getarg(arg, format);
	if (!arg->conv)
		return (format);
	if (arg->conv == '%')
	{
		arg->data = ft_strnew(1, '%');
		arg->conv = 'c';
	}
	else
		arg->data = ft_argtoa(arg, ap);
	arg->data_len = (arg->conv == 'c' && !*(arg->data)) ?
		1 : ft_strlen(arg->data);
	if (arg->data[0] == '-' && (arg->conv == 'd' || arg->conv == 'i'))
	{
		arg->sign = '-';
		--(arg->data_len);
	}
	ft_handle_flags(arg);
	ft_clrarg(arg);
	return (format);
}
