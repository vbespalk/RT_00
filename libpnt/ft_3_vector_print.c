
#include "libpnt.h"

#include <stdio.h>

void	ft_3_vector_print(const char *str, t_vector point)
{
	printf("%s(%f, %f, %f)\n", str, point[0], point[1], point[2]);
}
