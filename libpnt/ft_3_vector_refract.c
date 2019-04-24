
#include "libpnt.h"
#include <stdio.h>
#include "libft.h"

t_vector	ft_3_vector_refract
				(t_vector norm, t_vector direct, float refr1, float refr2)
{
	float		n;
	float		c1;
	float		k;

	c1 = ft_3_vector_cos(norm, direct);
	n = 1.f;
	if (c1 < 0)
	{
		c1 = -c1;
		n = refr1 / refr2;
	}
	else
	{
		norm = ft_3_vector_invert(norm);
		n = 1.0f / n;
	}
	k = 1 - n * n * (1 - c1 * c1);

//	printf("k = %f;\n", k);

	return ((k < 0)
		? ft_3_nullpointnew()
		: ft_3_vector_scale(direct, n) +
			ft_3_vector_scale(norm, n * c1 - sqrtf(k)));

//	if (refr1 > refr2) printf("[ %f -> %f ]:(%f, %f, %f);\n", refr1, refr2, t[0], t[1], t[2]);
}
