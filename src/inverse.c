/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 19:06:19 by vbespalk          #+#    #+#             */
/*   Updated: 2018/09/14 19:06:43 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float		get3m_det(t_matrix *m4, int s_i, int s_j)
{
	int		i;
	int		j;
	int		k;
	float	m3[9];
	float	d;

	d = 0;
	k = 0;
	i = -1;
	while (++i < 4 && (j = -1))
	{
		if (i == s_i)
			continue ;
		while (++j < 4)
		{
			if (j == s_j)
				continue ;
			m3[k] = (*m4)[i][j];
			k++;
		}
	}
	d = m3[0] * m3[4] * m3[8] + m3[1] * m3[5] * m3[6] + m3[2] * m3[3] * m3[7] \
	- m3[2] * m3[4] * m3[6] - m3[1] * m3[3] * m3[8] - m3[5] * m3[7] * m3[0];
	return (d);
}

t_matrix	*inverse(t_matrix *m_inv, t_matrix *m4)
{
	int			i;
	int			j;
	float		d;

	ft_bzero(m_inv, sizeof(t_matrix));
	d = (*m4)[0][0] * get3m_det(m4, 0, 0) - (*m4)[1][0] * get3m_det(m4, 1, 0) \
	+ (*m4)[2][0] * get3m_det(m4, 2, 0) - (*m4)[3][0] * get3m_det(m4, 3, 0);
	if (!(d))
		return (NULL);
	d = 1.0f / d;
	i = -1;
	while (++i < 4 && (j = -1))
		while (++j < 4)
			(*m_inv)[j][i] = d * pow(-1, i + j) * get3m_det(m4, i, j);
	return (m_inv);
}
