//
// Created by ivoriik on 26.03.19.
//

#include "rt.h"

float					lerp_val(float x, float nx[2])
{
	return (nx[0] + x * (nx[1] - nx[0]));
}

t_vector				lerp_vec(t_vector x, t_vector nx[2])
{
	return (nx[0] + x * (nx[1] - nx[0]));
}

static void				ft_lerp_noise_val(const int i_xyz[3], float noise_val[2][2][2], const float *table)
{
	int i;
	int j;
	int k;

	i = -1;
	while (++i <= 1)
	{
		j = -1;
		while (++j <= 1)
		{
			k = -1;
			while (++k <= 1)
				noise_val[i][j][k] = table[INDEX((i_xyz[0] + k),
												 (i_xyz[1] + j), (i_xyz[2] + i))];
		}
	}
}

float 					ft_linear_noise(t_vector point, const float *value_table)
{
	int		i;
	int 	i_xyz[3];
	float 	f_xyz[3];
	float 	noise_val[2][2][2];
	float 	interp[6];

	i = -1;
	while (++i < 3)
	{
		i_xyz[i] = (int)floorf(point[i]);
		f_xyz[i] = point[i] - i_xyz[i];
	}
	ft_lerp_noise_val(i_xyz, noise_val, value_table);
	interp[0] = lerp_val(f_xyz[0], (float []){noise_val[0][0][0], noise_val[0][0][1]});
	interp[1] = lerp_val(f_xyz[0], (float []){noise_val[0][1][0], noise_val[0][1][1]});
	interp[2] = lerp_val(f_xyz[0], (float []){noise_val[1][0][0], noise_val[1][0][1]});
	interp[3] = lerp_val(f_xyz[0], (float []){noise_val[1][1][0], noise_val[1][1][1]});
	interp[4] = lerp_val(f_xyz[1], (float []){interp[0], interp[1]});
	interp[5] = lerp_val(f_xyz[1], (float []){interp[2], interp[3]});
	return (lerp_val(f_xyz[2], (float []){interp[4], interp[5]}));

}

t_vector				fk_spline_vec(t_vector x, const t_vector knots[4])
{
	t_vector coef[4];
	t_vector res;

	coef[0] = knots[1];
	coef[1] = ft_3_vector_scale((knots[2] - knots[0]), 0.5f);
	coef[2] = knots[0] - ft_3_vector_scale(knots[1], 2.5f) + ft_3_vector_scale(knots[2], 2.f) -
			  ft_3_vector_scale(knots[3], 0.5f);
	coef[3] = ft_3_vector_scale(knots[0], -0.5f) + ft_3_vector_scale(knots[1], 1.5f) -
			  ft_3_vector_scale(knots[2], 1.5f) + ft_3_vector_scale(knots[3], 0.5f);
	res = ((coef[3] * x + coef[2]) * x + coef[1]) * x + coef[0];
	return (res);
}