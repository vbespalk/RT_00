//
// Created by ivoriik on 23.03.19.
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

double					fk_spline_val(float x, const double knots[4])
{
	double coef[4];

	coef[0] = knots[1];
	coef[1] = 0.5 * (knots[2] - knots[0]);
	coef[2] = knots[0] - 2.5 * knots[1] + 2.f * knots[2] - 0.5 * knots[3];
	coef[3] = -0.5f * knots[0] + 1.5 * knots[1] - 1.5f * knots[2] + 0.5 * knots[3];
	return (((coef[3] * x + coef[2]) * x + coef[1]) * x + coef[0]);
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

void					ft_init_value_table(float *vtable) {
	int i;

	i = -1;
	while (++i < LTABLE_SIZE)
	{
//		vtable[i] = 1.f - (2.f * (float) ((double) rand() / (double) RAND_MAX));
		vtable[i] = (float) ((double) rand() / (double) RAND_MAX);
//		i % 8 == 0 ? printf("\n") : printf("val %0.4f ", vtable[i]);
	}
//	printf("\n");
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

static float		ft_spline_noise_val(const int *i_xyz, const float *f_xyz, const float *value_table)
{
	int		ijk[3];
	double 	xi[4];
	double 	yi[4];
	double 	zi[4];

	ijk[0] = -2;
	while (++ijk[0] <= 2)
	{
		ijk[1] = -2;
		while (++ijk[1] <= 2)
		{
			ijk[2] = -2;
			while (++ijk[2] <= 2)
				xi[ijk[2] + 1] = value_table[INDEX((i_xyz[0] + ijk[2]),
								 (i_xyz[1] + ijk[1]), (i_xyz[2] + ijk[0]))];
			yi[ijk[1] + 1] = fk_spline_val(f_xyz[0], xi);
		}
		zi[ijk[0] + 1] = fk_spline_val(f_xyz[1], yi);
	}
	return ((float)fk_spline_val(f_xyz[2], zi));
}

float					ft_cubic_noise(t_vector point, const float *value_table)
{
	int		i;
	int 	i_xyz[3];
	float 	f_xyz[3];
	float	res;

	i = -1;
	while (++i < 3)
	{
		i_xyz[i] = (int)floorf(point[i]);
		f_xyz[i] = point[i] - i_xyz[i];
	}
	res = ft_spline_noise_val(i_xyz, f_xyz, value_table);
	return (CLAMP(res, 0, 1));
};

Uint32	ft_basic_noise(t_color col, float noise_val)
{
	col.argb[0] = (t_byte)(col.argb[0] * noise_val);
	col.argb[1] = (t_byte)(col.argb[1] * noise_val);
	col.argb[2] = (t_byte)(col.argb[2] * noise_val);
	col.argb[3] = (t_byte)(col.argb[3] * noise_val);
	return (col.val);
}