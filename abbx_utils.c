
#include "rt.h"



int			ft_is_inside_aabb(void *fig, t_vector point)
{
	(void)fig;
	(void)point;
	return (0);
}

t_vector	ft_get_norm_aabb(void *fig, t_vector coll)
{
	t_aabb		*bbx;
	t_vector	vec;
	t_vector	div;
	t_vector	norm;
	float 		bias = 1.00001;

	Uint32		col;
	int			xy[2];

	bbx = (t_aabb *)fig;
	vec = coll - bbx->cntr;
	div = ft_3_fabsf_vector(ft_3_vector_scale(bbx->dgnl, 0.5f));
	vec = ft_3_vector_scale(vec / div, 1);
	norm = ft_3_tounitvector((t_vector){(int)(vec[0] * bias), (int)(vec[1] * bias), (int)(vec[2] * bias)});
	return (norm);
}
