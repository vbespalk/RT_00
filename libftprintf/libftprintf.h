/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 17:36:21 by domelche          #+#    #+#             */
/*   Updated: 2018/05/28 16:12:00 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H

# define LIBFTPRINTF_H

# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>
# include <wchar.h>
# include "libft/libft.h"

/*
**	Bits' positions in mask:
**
**	|#0-+ |
**	|00000|000 00000000
*/

# define F_SHARP	0x8000
# define F_ZERO		0x4000
# define F_MINUS	0x2000
# define F_PLUS		0x1000
# define F_SPACE	0x800

/*
**	|lLhHjz|
**	|000000|00
*/

# define LF_L		0x80
# define LF_LL		0x40
# define LF_H		0x20
# define LF_HH		0x10
# define LF_J		0x8
# define LF_Z		0x4

typedef struct		s_buf
{
	char			*str;
	int				i;
	int				res;
}					t_buf;

typedef struct		s_arg
{
	char			conv;
	char			sign;
	uint8_t			lflags;
	uint16_t		flags;
	int				width;
	int				pad_len;
	int				prec;
	int				prec_len;
	int				data_len;
	int				sharp_len;
	char			*data;
	t_buf			*buf;
}					t_arg;

/*
**	buffer.c
*/

t_buf				*ft_bufnew(char *buf_ptr);
void				ft_putbuf(t_buf *buf, int len);
void				ft_putchar_buf(t_buf *buf, char c);
void				ft_putnchar_buf(t_buf *buf, char *str, int n);
void				ft_putstr_buf(t_buf *buf, char *str);

/*
**	arg.c
*/

t_arg				*ft_argnew(char *buffer);
void				ft_clrarg(t_arg *arg);
char				*ft_getarg(t_arg *arg, char *format);
int					ft_isvalid_conv(char c);

/*
**	ft_putarg.c
*/

char				*ft_putarg(char *format, va_list *ap, t_arg *arg);

/*
**	lflag.c
*/

char				*ft_parse_lflags(char *str, t_arg *arg);

/*
**	flag.c
*/

char				*ft_parse_flags(char *str, t_arg *arg);
uint16_t			ft_getmask(char c);

/*
**	ft_getstr_arg_01.c
*/

char				*ft_getstr_arg_u(t_arg *arg, va_list *ap);
char				*ft_getstr_arg_i(t_arg *arg, va_list *ap);
char				*ft_getstr_arg_c(t_arg *arg, va_list *ap);
char				*ft_getstr_arg_s(t_arg *arg, va_list *ap);
char				*ft_getstr_arg_p(t_arg *arg, va_list *ap);

/*
**	ft_handle_flags.c
*/

void				ft_handle_flags(t_arg *arg);
char				*ft_handle_width(t_arg *arg, char *str);
char				*ft_handle_prec(t_arg *arg, char *str);
char				*ft_handle_plus(t_arg *arg, char *str);

/*
**	ft_printf.c
*/

int					ft_printf(const char *format, ...);

#endif
