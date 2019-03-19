//
// Created by ivoriik on 15.03.19.
//

#include "libpnt.h"

t_vector				ft_3_fabsf_vector(t_vector vec)
{
	return ((t_vector){fabsf(vec[0]), fabsf(vec[1]), fabsf(vec[2])});
}
