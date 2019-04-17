//
// Created by ivoriik on 12.04.19.
//
#include "rt.h"

Uint32		ft_procedural_tor(void *fig, t_procedural *tex, t_vector coll)
{
	t_torus		*trs;
	t_vector	point;

	trs = (t_torus *)fig;
	point = ft_3_vector_scale(coll, 1 / trs->r_inner);
	return (tex->ft_get_color(tex, NULL, ft_3_vector_scale(point, 10)));
}