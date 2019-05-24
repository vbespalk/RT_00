/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 19:15:07 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/24 19:15:10 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			ft_solve_qdr(float a, float b, float c, float res[2])
{
	float d;

	res[0] = -FLT_MAX;
	res[1] = -FLT_MAX;
	if (IS_ZERO(a) && !IS_ZERO(b))
	{
		res[0] = -c / b;
		return (1);
	}
	d = powf(b, 2) - 4.0f * a * c;
	if (d < 0)
		return (0);
	d = sqrtf(d);
	res[0] = (-b + d) / (2.0f * a);
	res[1] = (-b - d) / (2.0f * a);
	if ((res[0] > res[1] && res[1] > FLT_MIN) || res[0] < FLT_MIN)
		ft_swap(&res[0], &res[1], sizeof(float));
	return (2);
}

int			ft_solve_sq(double a, double b, double c, double res[2])
{
	double	d;

	res[0] = FLT_MAX;
	res[1] = FLT_MAX;
	if (IS_ZERO(a))
	{
		res[0] = -c / b;
		res[1] = res[0];
		return (1);
	}
	d = pow(b, 2) - 4.0f * a * c;
	if (d < 0)
		return (0);
	d = sqrt(d);
	res[0] = (-b + d) / (2.0f * a);
	res[1] = (-b - d) / (2.0f * a);
	if ((res[0] > res[1] && res[1] >= 0) || res[0] <= 0)
		ft_swap(&res[0], &res[1], sizeof(double));
	return (2);
}
