/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lattice_add_func.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 19:09:30 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/14 19:09:33 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float			lerp_val(float x, float nx[2])
{
	return (nx[0] + x * (nx[1] - nx[0]));
}

t_vector		lerp_vec(t_vector x, t_vector nx[2])
{
	return (nx[0] + x * (nx[1] - nx[0]));
}

static void		ft_lerp_noise_val(const int i_xyz[3], float noise_val[2][2][2],
						const float *table)
{
	int ijk[3];

	ijk[0] = -1;
	while (++ijk[0] <= 1)
	{
		ijk[1] = -1;
		while (++ijk[1] <= 1)
		{
			ijk[2] = -1;
			while (++ijk[2] <= 1)
				noise_val[ijk[0]][ijk[1]][ijk[2]] =
					table[INDEX((i_xyz[0] + ijk[2]),
					(i_xyz[1] + ijk[1]), (i_xyz[2] + ijk[0]))];
		}
	}
}

float			ft_linear_noise(t_vector point, const float *value_table)
{
	int		i;
	int		i_xyz[3];
	float	f_xyz[3];
	float	noise_val[2][2][2];
	float	interp[6];

	i = -1;
	while (++i < 3)
	{
		i_xyz[i] = (int)floorf(point[i]);
		f_xyz[i] = point[i] - i_xyz[i];
	}
	ft_lerp_noise_val(i_xyz, noise_val, value_table);
	interp[0] = lerp_val(f_xyz[0], (float[]){noise_val[0][0][0],
										noise_val[0][0][1]});
	interp[1] = lerp_val(f_xyz[0], (float[]){noise_val[0][1][0],
										noise_val[0][1][1]});
	interp[2] = lerp_val(f_xyz[0], (float[]){noise_val[1][0][0],
										noise_val[1][0][1]});
	interp[3] = lerp_val(f_xyz[0], (float[]){noise_val[1][1][0],
										noise_val[1][1][1]});
	interp[4] = lerp_val(f_xyz[1], (float[]){interp[0], interp[1]});
	interp[5] = lerp_val(f_xyz[1], (float[]){interp[2], interp[3]});
	return (lerp_val(f_xyz[2], (float[]){interp[4], interp[5]}));
}

t_vector		ft_spline_vec(t_vector x, const t_vector knots[4])
{
	t_vector coef[4];
	t_vector res;

	coef[0] = knots[1];
	coef[1] = ft_3_vector_scale((knots[2] - knots[0]), 0.5f);
	coef[2] = knots[0] - ft_3_vector_scale(knots[1], 2.5f) +
			ft_3_vector_scale(knots[2], 2.f) -
			ft_3_vector_scale(knots[3], 0.5f);
	coef[3] = ft_3_vector_scale(knots[0], -0.5f) +
			ft_3_vector_scale(knots[1], 1.5f) -
			ft_3_vector_scale(knots[2], 1.5f) +
			ft_3_vector_scale(knots[3], 0.5f);
	res = ((coef[3] * x + coef[2]) * x + coef[1]) * x + coef[0];
	return (res);
}
