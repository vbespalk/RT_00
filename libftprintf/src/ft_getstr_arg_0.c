/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getstr_arg_0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 14:48:19 by domelche          #+#    #+#             */
/*   Updated: 2018/05/05 14:48:38 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

static char	*ft_getdata_arg_u(t_arg *arg, unsigned long long data, int base)
{
	if (arg->lflags & LF_LL)
		return (ft_uitoa_base(data, base));
	else if (arg->lflags & LF_L)
		return (ft_uitoa_base((unsigned long)data, base));
	else if (arg->lflags & LF_H)
		return (ft_uitoa_base((unsigned short)data, base));
	else if (arg->lflags & LF_HH)
		return (ft_uitoa_base((unsigned char)data, base));
	else if (arg->lflags & LF_J)
		return (ft_uitoa_base((uintmax_t)data, base));
	else if (arg->lflags & LF_Z)
		return (ft_uitoa_base((size_t)data, base));
	else
		return (ft_uitoa_base((unsigned int)data, base));
}

char		*ft_getstr_arg_u(t_arg *arg, va_list *ap)
{
	unsigned long long	data;
	int					base;
	char				*str;
	char				*to_free;

	data = va_arg(*ap, unsigned long long);
	base = 10;
	if (arg->conv == 'x' || arg->conv == 'X')
		base = 16;
	else if (arg->conv == 'o')
		base = 8;
	else if (arg->conv == 'b')
		base = 2;
	str = ft_getdata_arg_u(arg, data, base);
	if (arg->conv == 'x')
	{
		to_free = str;
		str = ft_strmap(str, (char (*)(char))ft_tolower);
		free(to_free);
	}
	if (!data && !arg->prec && !(arg->conv == 'o' && arg->flags & F_SHARP))
		*str = 0;
	if (!data)
		arg->flags &= ~F_SHARP;
	return (str);
}

char		*ft_getstr_arg_i(t_arg *arg, va_list *ap)
{
	long long	data;
	char		*str;

	data = va_arg(*ap, long long);
	if (arg->lflags & LF_LL)
		str = ft_itoa(data);
	else if (arg->lflags & LF_L)
		str = ft_itoa((long)data);
	else if (arg->lflags & LF_H)
		str = ft_itoa((short)data);
	else if (arg->lflags & LF_HH)
		str = ft_itoa((char)data);
	else if (arg->lflags & LF_J)
		str = ft_itoa((intmax_t)data);
	else if (arg->lflags & LF_Z)
		str = ft_itoa((ssize_t)data);
	else
		str = ft_itoa((int)data);
	if (!data && !arg->prec)
		*str = 0;
	return (str);
}

char		*ft_getstr_arg_c(t_arg *arg, va_list *ap)
{
	wint_t	data;
	char	*str;

	data = va_arg(*ap, int);
	if (!(str = (char *)ft_memalloc(5 * sizeof(char))))
		return (NULL);
	if (((arg->lflags & LF_L) | (arg->lflags & LF_LL)) &&
		MB_CUR_MAX == sizeof(wchar_t))
		ft_write_wctoa(data, str);
	else
		str[0] = (char)data;
	return (str);
}
