/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 23:03:35 by vbespalk          #+#    #+#             */
/*   Updated: 2019/04/27 13:40:53 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpnt.h"
#include "../libftprintf/libft/libft.h"

t_vector	ft_3_pnt_transform(const t_matrix *m, t_vector p)
{
	float	x;
	float	y;
	float	z;

	if (!m)
		return (p);
	x = (*m)[0][0] * p[0] + (*m)[0][1] * p[1] + (*m)[0][2] * p[2] + (*m)[0][3];
	y = (*m)[1][0] * p[0] + (*m)[1][1] * p[1] + (*m)[1][2] * p[2] + (*m)[1][3];
	z = (*m)[2][0] * p[0] + (*m)[2][1] * p[1] + (*m)[2][2] * p[2] + (*m)[2][3];
	return ((t_vector){x, y, z});
}

t_vector	ft_3_vec_transform(const t_matrix *m, t_vector p)
{
	float	x;
	float	y;
	float	z;

	if (!m)
		return (p);
	x = (*m)[0][0] * p[0] + (*m)[0][1] * p[1] + (*m)[0][2] * p[2];
	y = (*m)[1][0] * p[0] + (*m)[1][1] * p[1] + (*m)[1][2] * p[2];
	z = (*m)[2][0] * p[0] + (*m)[2][1] * p[1] + (*m)[2][2] * p[2];
	return ((t_vector){x, y, z});
}

t_vector	ft_3_norm_transform(const t_matrix *m, t_vector p)
{
	float	x;
	float	y;
	float	z;

	if (!m)
		return (p);
	x = (*m)[0][0] * p[0] + (*m)[1][0] * p[1] + (*m)[2][0] * p[2];
	y = (*m)[0][1] * p[0] + (*m)[1][1] * p[1] + (*m)[2][1] * p[2];
	z = (*m)[0][2] * p[0] + (*m)[1][2] * p[1] + (*m)[2][2] * p[2];
	return ((t_vector){x, y, z});
}

/*
**	replace memcpy here with the default one to port the lib
*/

void		ft_3_matrix_mult(t_matrix *left, t_matrix *right, int inv)
{
	t_matrix	m;
	int			i;
	int			j;

	if (!right || !left)
		return ;
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			m[i][j] = (*left)[i][0] * (*right)[0][j] + \
			(*left)[i][1] * (*right)[1][j] + (*left)[i][2] \
			* (*right)[2][j] + (*left)[i][3] * (*right)[3][j];
		}
	}
	(inv)
	? ft_memcpy(left, m, sizeof(t_matrix))
	: ft_memcpy(right, m, sizeof(t_matrix));
}

void		ft_3_transform_mat(
				t_matrix *rm, t_vector transl, t_vector rot, float sc)
{
	if (!rm)
		return ;
	ft_3_identity(rm);
	if (sc != FLT_MIN)
		ft_3_matrix_scale(rm, sc, 0);
	if (!(ft_3_isnullpoint(rot)))
		ft_3_matrix_rotate(rm, rot, 0);
	if (!(ft_3_isnullpoint(transl)))
		ft_3_matrix_move(rm, transl, 0);
}
