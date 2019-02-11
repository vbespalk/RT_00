/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_basic.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 13:41:31 by domelche          #+#    #+#             */
/*   Updated: 2018/03/31 14:21:20 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITOA_BASIC_H

# define ITOA_BASIC_H

/*
**	function ft_itoa_basic is strongly NOT recommended for straight usage,
**	because all validation is placed in "wrapping" functions, which are
**	recommended to use: ft_itoa, ft_itoa_base, ft_uitoa, ft_uitoa_base;
**	otherwise, in case of invalid arguments, undefined behavior is expected
*/

char	*ft_itoa_basic(unsigned long long num, int sign, int base);

#endif
