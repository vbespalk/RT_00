//
// Created by ivoriik on 23.03.19.
//

#include "rt.h"

float					fk_spline_val(float x, const float knots[4])
{
	float coef[4];

	coef[0] = knots[1];
	coef[1] = 0.5f * (knots[2] - knots[0]);
	coef[2] = knots[0] - 2.5f * knots[1] + 2.f * knots[2] - 0.5f * knots[3];
	coef[3] = -0.5f * knots[0] + 1.5f * knots[1] - 1.5f * knots[2] + 0.5f * knots[3];
	return (((coef[3] * x + coef[2]) * x + coef[1]) * x + coef[0]);
}

void					ft_init_value_table(float **vtable) {
	int i;

	*vtable = ft_smemalloc(sizeof(float) * LTABLE_SIZE, "ft_init_value_table");
	i = -1;
	while (++i < LTABLE_SIZE)
	{
		(*vtable)[i] = 1.f - (2.f * ((float) rand() / (float) RAND_MAX));
//		(*vtable)[i] = (float) ((float) rand() / (float) RAND_MAX);
		i % 8 == 0 ? printf("\n") : printf("val %0.4f ", (*vtable)[i]);
	}
	printf("\n");
}

static float		ft_spline_noise_val(const int *i_xyz, const float *f_xyz, const float *value_table)
{
	int		ijk[3];
	float 	xi[4];
	float 	yi[4];
	float 	zi[4];

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
	return (fk_spline_val(f_xyz[2], zi));
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
//	res = (ft_spline_noise_val(i_xyz, f_xyz, value_table) + 1) * 0.5f;
//	printf("RES %f, CLAMP %f\n", res, CLAMP(res, 0, 1));
	return (CLAMP(res, -1, 1));
};

void	ft_lattice_bounds(int octaves, float gain, float bounds[2])
{
	bounds[1] = gain == 1.0f ? octaves : (1.0f - powf(gain, octaves))
				/ (1.0f - gain);
	bounds[0] = -bounds[1];
}