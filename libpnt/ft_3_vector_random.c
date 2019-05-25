/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3_vector_random.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 18:58:42 by domelche          #+#    #+#             */
/*   Updated: 2019/05/25 18:58:44 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpnt.h"

t_vector	ft_3_vector_random(void)
{
	t_vector	vector;
	int			r_max_2;
	float		len;

	if (!g_is_seeded)
	{
		g_is_seeded = 1;
		srand(time(NULL));
	}
	r_max_2 = RAND_MAX / 2;
	len = 0;
	vector[0] = (float)(rand() - r_max_2);
	len += powf(vector[0], 2);
	vector[1] = (float)(rand() - r_max_2);
	len += powf(vector[1], 2);
	vector[2] = (float)(rand() - r_max_2);
	len += powf(vector[2], 2);
	len = sqrtf(len);
	vector[0] /= len;
	vector[1] /= len;
	vector[2] /= len;
	return (vector);
}
