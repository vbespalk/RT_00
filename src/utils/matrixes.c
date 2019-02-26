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

#include "rt.h"

t_matrix	*x_rotate(t_matrix *m_xrot, float angle)
{
	if (!m_xrot)
		return (NULL);
	ft_bzero(m_xrot, sizeof(t_matrix));
	(*m_xrot)[0][0] = 1.0f;
	(*m_xrot)[1][1] = cos(angle);
	(*m_xrot)[1][2] = -sin(angle);
	(*m_xrot)[2][1] = sin(angle);
	(*m_xrot)[2][2] = cos(angle);
	(*m_xrot)[3][3] = 1.0f;
	return (m_xrot);
}

t_matrix	*y_rotate(t_matrix *m_yrot, float angle)
{
	if (!m_yrot)
		return (NULL);
	ft_bzero(m_yrot, sizeof(t_matrix));
	(*m_yrot)[0][0] = cos(angle);
	(*m_yrot)[0][2] = -sin(angle);
	(*m_yrot)[1][1] = 1.0f;
	(*m_yrot)[2][0] = sin(angle);
	(*m_yrot)[2][2] = cos(angle);
	(*m_yrot)[3][3] = 1.0f;
	return (m_yrot);
}

t_matrix	*z_rotate(t_matrix *m_zrot, float angle)
{
	if (!m_zrot)
		return (NULL);
	ft_bzero(m_zrot, sizeof(t_matrix));
	(*m_zrot)[0][0] = cos(angle);
	(*m_zrot)[0][1] = -sin(angle);
	(*m_zrot)[1][0] = sin(angle);
	(*m_zrot)[1][1] = cos(angle);
	(*m_zrot)[2][2] = 1.0f;
	(*m_zrot)[3][3] = 1.0f;
	return (m_zrot);
}

t_matrix	*matrix_move(t_matrix *m_move, int x_move, int y_move, int z_move)
{
	if (!m_move)
		return (NULL);
	ft_bzero(m_move, sizeof(t_matrix));
	(*m_move)[0][0] = 1.0f;
	(*m_move)[1][1] = 1.0f;
	(*m_move)[2][2] = 1.0f;
	(*m_move)[0][3] += x_move;
	(*m_move)[1][3] += y_move;
	(*m_move)[2][3] += z_move;
	(*m_move)[3][3] = 1.0f;
	return (m_move);
}

t_matrix	*matrix_scale(t_matrix *m_scale, float scale)
{
	if (!m_scale)
		return (NULL);
	ft_bzero(m_scale, sizeof(t_matrix));
	(*m_scale)[0][0] = scale * 1.0f;
	(*m_scale)[1][1] = scale * 1.0f;
	(*m_scale)[2][2] = scale * 1.0f;
	(*m_scale)[3][3] = 1.0f;
	return (m_scale);
}
