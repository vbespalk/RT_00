/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrixes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 16:25:28 by vbespalk          #+#    #+#             */
/*   Updated: 2018/06/03 19:50:30 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpnt.h"
#include "libft.h"

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

void		ft_3_matrix_scale(t_matrix *rm, float scale, int inv)
{
	t_matrix lm;

	if (!rm)
		return ;
	ft_3_identity(&lm);
	lm[0][0] = scale;
	lm[1][1] = scale;
	lm[2][2] = scale;
	lm[3][3] = 1.0f;
	inv ? ft_3_matrix_mult(rm, &lm, 1) : ft_3_matrix_mult(&lm, rm, 0);
}

void		ft_3_matrix_rotate(t_matrix *rm, t_vector ang, int inv)
{
	t_matrix	lm;
	t_vector	sin_;
	t_vector	cos_;

	if (!rm)
		return ;
	ft_3_identity(&lm);
	sin_[0] = sinf(ang[0]);
	sin_[1] = sinf(ang[1]);
	sin_[2] = sinf(ang[2]);
	cos_[0] = cosf(ang[0]);
	cos_[1] = cosf(ang[1]);
	cos_[2] = cosf(ang[2]);
	(lm)[0][0] = cos_[2] * cos_[1];
	(lm)[0][1] = cos_[2] * sin_[1] * sin_[0] - sin_[2] * cos_[0];
	(lm)[0][2] = sin_[2] * sin_[0] + cos_[0] * cos_[2] * sin_[1];
	(lm)[1][0] = cos_[1] * sin_[2];
	(lm)[1][1] = cos_[0] * cos_[2] + sin_[0] * sin_[1] * sin_[2];
	(lm)[1][2] = cos_[0] * sin_[1] * sin_[2] - sin_[0] * cos_[2];
	(lm)[2][0] = -(sin_[1]);
	(lm)[2][1] = sin_[0] * cos_[1];
	(lm)[2][2] = cos_[0] * cos_[1];
	(lm)[3][3] = 1.0f;
	inv ? ft_3_matrix_mult(rm, &lm, 1) : ft_3_matrix_mult(&lm, rm, 0);
}