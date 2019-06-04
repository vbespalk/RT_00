/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 18:59:18 by domelche          #+#    #+#             */
/*   Updated: 2019/05/25 18:59:26 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpnt.h"

void		ft_3_inv_trans_mat(
				t_matrix *rm, t_vector transl, t_vector rot, float sc)
{
	if (!rm)
		return ;
	ft_3_identity(rm);
	if (sc != FLT_MIN)
		ft_3_matrix_scale(rm, sc, 1);
	if (!(ft_3_isnullpoint(rot)))
		ft_3_matrix_rotate(rm, rot, 1);
	if (!(ft_3_isnullpoint(transl)))
		ft_3_matrix_move(rm, transl, 1);
}
