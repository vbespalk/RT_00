/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 17:34:14 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/24 17:34:16 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	less_zero_det(double res[3], double const pqd[3], double delim)
{
	double	t;
	double	phi;

	if (IS_ZERO(pqd[2]))
		if (IS_ZERO(pqd[1]))
		{
			res[0] = 0.f - delim;
			return (1);
		}
		else
		{
			res[0] = 2.f * cbrt(-pqd[1]) - delim;
			res[1] = -cbrt(-pqd[1]) - delim;
			return (2);
		}
	else
	{
		phi = 1.f / 3 * acos(-pqd[1] / sqrt(-(pqd[0] * pqd[0] * pqd[0])));
		t = 2 * sqrt(-pqd[0]);
		res[0] = t * cos(phi) - delim;
		res[1] = -t * cos(phi + M_PI / 3.0) - delim;
		res[2] = -t * cos(phi - M_PI / 3.0) - delim;
		return (3);
	}
}

int			ft_solve_cubic(const double coef[4], double res[3])
{
	double	abc[3];
	double	pqd[3];

	abc[0] = coef[1] / coef[0];
	abc[1] = coef[2] / coef[0];
	abc[2] = coef[3] / coef[0];
	pqd[0] = (-1.f / 3 * abc[0] * abc[0] + abc[1]) / 3.0;
	pqd[1] = 0.5 * (2.0 / 27 * pow(abc[0], 3) -
			1.0 / 3 * abc[0] * abc[1] + abc[2]);
	pqd[2] = pqd[1] * pqd[1] + pow(pqd[0], 3);
	if (IS_ZERO(pqd[2]) || pqd[2] < 0)
		return (less_zero_det(res, pqd, abc[0] / 3.0));
	pqd[2] = sqrt(pqd[2]);
	res[0] = (cbrt(pqd[2] - pqd[1]) - cbrt(pqd[2] + pqd[1])) - abc[0] / 3.0;
	return (1);
}

static int	general_case(double rs[4], double const pqr[3], double s)
{
	double	abcd[4];
	double	uv[2];
	int		i[2];

	abcd[0] = 1;
	abcd[1] = -0.5 * pqr[0];
	abcd[2] = -pqr[2];
	abcd[3] = 0.5 * pqr[2] * pqr[0] - 1.0 / 8 * pqr[1] * pqr[1];
	i[1] = ft_solve_cubic(abcd, rs);
	i[0] = -1;
	ft_bzero(uv, sizeof(double) * 2);
	while (++i[0] < i[1])
	{
		s = rs[i[0]];
		uv[0] = s * s - pqr[2];
		uv[1] = 2 * s - pqr[0];
		if (uv[0] > -EQN_EPS && uv[1] > -EQN_EPS)
			break ;
	}
	if (uv[0] < -1e-1 || uv[1] < -1e-1)
		return (0);
	uv[0] = IS_ZERO(uv[0]) ? 0 : sqrt(fabs(uv[0]));
	uv[1] = IS_ZERO(uv[1]) ? 0 : sqrt(fabs(uv[1]));
	i[1] = ft_solve_sq(1, pqr[1] < 0 ? uv[1] : -uv[1], s + uv[0], rs);
	i[1] += ft_solve_sq(1, pqr[1] < 0 ? -uv[1] : uv[1], s - uv[0], rs + i[1]);
	return (i[1]);
}

static int	no_absol_term_case(double res[4], double const pqr[3])
{
	double	abcd[4];
	int		num;

	abcd[0] = 1;
	abcd[1] = 0;
	abcd[2] = pqr[0];
	abcd[3] = pqr[1];
	num = ft_solve_cubic(abcd, res);
	res[num++] = 0;
	return (num);
}

int			ft_solve_quartic(double abcde[5], double res[4])
{
	double	pqr[3];
	double	tmp;
	double	delim;
	int		i[2];

	abcde[1] = abcde[1] / abcde[0];
	abcde[2] = abcde[2] / abcde[0];
	abcde[3] = abcde[3] / abcde[0];
	abcde[4] = abcde[4] / abcde[0];
	delim = 0.25 * abcde[1];
	tmp = abcde[1] * abcde[1];
	pqr[0] = -3.0 / 8 * tmp + abcde[2];
	pqr[1] = 1.0 / 8 * tmp * abcde[1] - 0.5 * abcde[1] * abcde[2] + abcde[3];
	pqr[2] = -3.0 / 256 * tmp * tmp + (tmp * abcde[2]) / 16.0 -
			0.25 * abcde[1] * abcde[3] + abcde[4];
	if (IS_ZERO(pqr[2]))
		i[1] = no_absol_term_case(res, pqr);
	else
		i[1] = general_case(res, pqr, 0);
	i[0] = -1;
	while (++i[0] < i[1])
		res[i[0]] -= delim;
	return (i[1]);
}
