
#include "libpnt.h"

t_vector	ft_3_vector_refract
				(t_vector norm, t_vector direct, float refr1, float refr2)
{
	float	cos;
	float	a1;
	float	a2;

	cos = ft_3_vector_cos(direct, norm);
	if (cos < 0)
	{
		norm =  -1.0 * norm;
		cos *= -1.0f;
	}
	a1 = (float)acos(cos);
	a2 = (float)asin(refr1 * sin(sin(acos(cos))) / refr2);
	if (a2 >= M_PI_2)
		return (ft_3_nullpointnew());
	return (ft_3_vector_turn_near(direct, norm, a2 - a1));
}
