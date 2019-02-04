
#include "libpnt.h"

t_vector	ft_3_vector_refract
				(t_vector norm, t_vector direct, float refr1, float refr2)
{
	float	cos;
	float	a2;

	cos = ft_3_vector_cos(direct, norm);
	if (cos < 0)
	{
		norm = ft_3_vector_scale(norm, -1.0f);
		cos *= -1.0f;
	}
	a2 = (float)asin(refr1 * sin(sin(acos(cos))) / refr2);
	if (a2 >= M_PI_2)
		return (ft_3_nullpointnew());
	return (ft_3_vector_turn(
		ft_3_tounitvector(ft_3_vector_project(norm, direct)), norm, a2));
}
