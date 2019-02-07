
#include "libpnt.h"
#include <stdio.h>
t_vector	ft_3_vector_refract
				(t_vector norm, t_vector direct, float refr1, float refr2)
{
	float	cos;
	float	a2;

	cos = ft_3_vector_dot(direct, norm);
	if (cos > 0)
	{
		norm = ft_3_vector_scale(norm, -1.0f);
	}

//	printf("%f\n", refr1 * sqrtf(1.0f - cos * cos) / refr2);

	a2 = asinf(refr1 * sqrtf(1.0f - cos * cos) / refr2);

	printf("angle: %f\n", a2);

	if (a2 >= M_PI_2)
		return (ft_3_nullpointnew());

	t_vector proj;
	if (a2 != 0.0f)
	{
		proj = ft_3_vector_project(norm, direct);
	//	printf("proj: (%f, %f, %f);\n", proj[0], proj[1], proj[2]);
	}

	float		n = refr1 / refr2;
	float		c2 = sqrtf(1 - n * n * (1 - cos * cos));
	t_vector	t = ft_3_vector_scale(direct, n) +
					ft_3_vector_scale(norm, n * cos - c2);

	if (refr1 > refr2) printf("[ %f -> %f ]:(%f, %f, %f);\n", refr1, refr2, t[0], t[1], t[2]);

	return ((a2 == 0.0f) ?
		direct :
		ft_3_vector_turn(
			ft_3_tounitvector(proj), norm, a2));
}
