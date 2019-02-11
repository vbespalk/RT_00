/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getstr_arg_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 14:50:52 by domelche          #+#    #+#             */
/*   Updated: 2018/05/05 14:53:28 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

char		*ft_getstr_arg_p(t_arg *arg, va_list *ap)
{
	void	*data;
	char	*str;
	char	*to_free;

	(void)arg;
	data = va_arg(*ap, void *);
	str = ft_uitoa_base((unsigned long long)data, 16);
	arg->flags |= F_SHARP;
	to_free = str;
	str = ft_strmap(str, (char (*)(char))ft_tolower);
	free(to_free);
	if (!data && !arg->prec)
		*str = 0;
	return (str);
}

static void	ft_getprec_for_ls(t_arg *arg, char *str)
{
	if (arg->prec > (int)ft_strlen(str) && arg->prec != -1)
		return ;
	while ((unsigned char)str[arg->prec] >= 0x80 &&
			(unsigned char)str[arg->prec] < 0xC0 && arg->prec > 0)
		--arg->prec;
}

char		*ft_getstr_arg_s(t_arg *arg, va_list *ap)
{
	wchar_t	*data;
	char	*res;
	int		len;

	data = va_arg(*ap, wchar_t *);
	if (!data)
		res = ft_strdup("(null)");
	else if ((arg->lflags & LF_L) | (arg->lflags & LF_LL))
	{
		res = ft_ustos(data);
		ft_getprec_for_ls(arg, res);
	}
	else
		res = ft_strdup((char *)data);
	len = ft_strlen(res);
	if (arg->prec < len && arg->prec != -1)
		res[arg->prec] = 0;
	return (res);
}
