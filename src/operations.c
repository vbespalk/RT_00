/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 23:03:35 by vbespalk          #+#    #+#             */
/*   Updated: 2018/09/24 23:03:41 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector	*vec_multipl(const t_matrix *m, t_vector *p)
{
	float	x;
	float	y;
	float	z;
	float	w;

	if (!m || !p)
		return (NULL);
	x = (*m)[0][0] * (*p)[0] + (*m)[0][1] * (*p)[1] + (*m)[0][2] \
	* (*p)[2] + (*m)[0][3];
	y = (*m)[1][0] * (*p)[0] + (*m)[1][1] * (*p)[1] + (*m)[1][2] \
	* (*p)[2] + (*m)[1][3];
	z = (*m)[2][0] * (*p)[0] + (*m)[2][1] * (*p)[1] + (*m)[2][2] \
	* (*p)[2] + (*m)[2][3];
	w = (*m)[3][0] * (*p)[0] + (*m)[3][1] * (*p)[1] + (*m)[3][2] \
	* (*p)[2] + (*m)[3][3];
	if (w > 1)
		;
	(*p)[0] = x;
	(*p)[1] = y;
	(*p)[2] = z;
	return (p);
}

t_vector	*dir_multipl(const t_matrix *m, t_vector *p)
{
	float	x;
	float	y;
	float	z;

	if (!m || !p)
		return (NULL);
	x = (*m)[0][0] * (*p)[0] + (*m)[0][1] * (*p)[1] + (*m)[0][2] \
	* (*p)[2] + (*m)[0][3] * 0.0f;
	y = (*m)[1][0] * (*p)[0] + (*m)[1][1] * (*p)[1] + (*m)[1][2] \
	* (*p)[2] + (*m)[1][3] * 0.0f;
	z = (*m)[2][0] * (*p)[0] + (*m)[2][1] * (*p)[1] + (*m)[2][2] \
	* (*p)[2] + (*m)[2][3] * 0.0f;
	(*p)[0] = x;
	(*p)[1] = y;
	(*p)[2] = z;
	return (p);
}

t_matrix	*matrix_mult(t_matrix *left, t_matrix *right)
{
	t_matrix	m;
	int			i;
	int			j;

	if (!right || !left)
		return (NULL);
	ft_bzero(m, sizeof(t_matrix));
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			m[i][j] = (*left)[i][0] * (*right)[0][j] + \
			(*left)[i][1] * (*right)[1][j] + (*left)[i][2] \
			* (*right)[2][j] + (*left)[i][3] * (*right)[3][j];
			j++;
		}
		i++;
	}
	ft_memcpy(left, m, sizeof(m));
	return (left);
}

t_matrix	*transform_mat(t_matrix *lm, t_vector tr, t_vector rot, float sc)
{
	t_matrix rm;

	if (!lm || sc == 0)
		return (NULL);
	ft_bzero(lm, sizeof(t_matrix));
	matrix_scale(&rm, sc);
	if (rot[0] || rot[1] || rot[2])
	{
		matrix_rotate(lm, rot[0], rot[1], rot[2]);
		matrix_mult(&rm, lm);
	}
	matrix_mult(matrix_move(lm, tr[0], tr[1], tr[2]), &rm);
	return (lm);
}

t_matrix	*matrix_rotate(t_matrix *m, float x, float y, float z)
{
	float cos_x;
	float cos_y;
	float cos_z;
	float sin_x;
	float sin_y;

	if (!m)
		return (NULL);
	ft_bzero(m, sizeof(t_matrix));
	cos_x = cos(x);
	cos_y = cos(y);
	cos_z = cos(z);
	sin_x = sin(x);
	sin_y = sin(y);
	(*m)[0][0] = cos_y * cos_z;
	(*m)[0][1] = cos_y * sin(z);
	(*m)[0][2] = -sin_y;
	(*m)[1][0] = sin_x * sin_y * cos_z - cos_x * sin(z);
	(*m)[1][1] = sin_x * sin_y * sin(z) + cos_x * cos_z;
	(*m)[1][2] = sin_x * cos_y;
	(*m)[2][0] = cos_x * sin_y * cos_z + sin_x * sin(z);
	(*m)[2][1] = cos_x * sin_y * sin(z) - sin_x * cos_z;
	(*m)[2][2] = cos_x * cos_y;
	(*m)[3][3] = 1.0f;
	return (m);
}
