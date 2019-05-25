/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrixes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 16:25:28 by vbespalk          #+#    #+#             */
/*   Updated: 2019/04/27 13:40:59 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpnt.h"
#include "../libftprintf/libft/libft.h"

/*
**	replace bzero here with the default one to port the lib
*/

void		ft_3_identity(t_matrix *i)
{
	ft_bzero(i, sizeof(t_matrix));
	(*i)[0][0] = 1.0f;
	(*i)[1][1] = 1.0f;
	(*i)[2][2] = 1.0f;
	(*i)[3][3] = 1.0f;
}

void		ft_3_x_rotate(t_matrix *rm, float angle, int inv)
{
	t_matrix lm;

	if (!rm)
		return ;
	ft_3_identity(&lm);
	lm[0][0] = 1.0f;
	lm[1][1] = cosf(angle);
	lm[1][2] = -sinf(angle);
	lm[2][1] = sinf(angle);
	lm[2][2] = cosf(angle);
	lm[3][3] = 1.0f;
	inv ? ft_3_matrix_mult(rm, &lm, 1) : ft_3_matrix_mult(&lm, rm, 0);
}

void		ft_3_y_rotate(t_matrix *rm, float angle, int inv)
{
	t_matrix lm;

	if (!rm)
		return ;
	ft_3_identity(&lm);
	lm[0][0] = cosf(angle);
	lm[0][2] = -sinf(angle);
	lm[1][1] = 1.0f;
	lm[2][0] = sinf(angle);
	lm[2][2] = cosf(angle);
	lm[3][3] = 1.0f;
	inv ? ft_3_matrix_mult(rm, &lm, 1) : ft_3_matrix_mult(&lm, rm, 0);
}

void		ft_3_z_rotate(t_matrix *rm, float angle, int inv)
{
	t_matrix lm;

	if (!rm)
		return ;
	ft_3_identity(&lm);
	lm[0][0] = cosf(angle);
	lm[0][1] = -sinf(angle);
	lm[1][0] = sinf(angle);
	lm[1][1] = cosf(angle);
	lm[2][2] = 1.0f;
	lm[3][3] = 1.0f;
	inv ? ft_3_matrix_mult(rm, &lm, 1) : ft_3_matrix_mult(&lm, rm, 0);
}

void		ft_3_matrix_move(t_matrix *rm, t_vector transl, int inv)
{
	t_matrix lm;

	if (!rm)
		return ;
	ft_3_identity(&lm);
	lm[0][3] += transl[0];
	lm[1][3] += transl[1];
	lm[2][3] += transl[2];
	inv ? ft_3_matrix_mult(rm, &lm, 1) : ft_3_matrix_mult(&lm, rm, 0);
}
