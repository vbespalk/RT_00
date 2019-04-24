//
// Created by ivoriik on 19.03.19.
//


#include "rt.h"

static int			ft_solve_sqr_(double a, double b, double c, double res[2])
{
	double	d;
	double 	tmp;

	d = pow(b, 2) - 4.0f * a * c;
	if (d < 0)
		return (0);
	d = sqrt(d);
	bzero(res, sizeof(double) * 2);
	res[0] = (-b + d) / (2.0f * a);
	res[1] = (-b - d) / (2.0f * a);
	if (res[0] > res[1] || res[0] < FLT_MIN)
	{
		tmp = res[0];
		res[0] = res[1];
		res[1] = tmp;
	}
	return (2);
}

int 				ft_solve_cubic(const double coef[4],  double res[3])
{
	double	abc[3];
	double	pq[2];
	double	d;
	double	phi;
	double 	t;

	abc[0] = coef[1] / coef[0];
	abc[1] = coef[2] / coef[0];
	abc[2] = coef[3] / coef[0];

	/*  substitute x = y - A/3 to eliminate quadric term: x^3 +px + q = 0 */

	pq[0] = 1.f / 3 * (-1.f / 3 * abc[0] * abc[0] + abc[1]);
	pq[1] = 1.f / 2 * (2.f / 27 * pow(abc[0], 3) - 1.f / 3 * abc[0] * abc[1] + abc[2]);

	/* use Cardano's formula */

	d = pq[1] * pq[1] + pow(pq[0], 3);
	if (IS_ZERO(d))
	{
		if (IS_ZERO(pq[1])) /* one triple solution */
		{
			res[0] = 0.f - 1.f / 3 * abc[0];
			return (1);
		}
		else
		{
			res[0] = 2.f * cbrt(-pq[1]) - 1.f / 3 * abc[0];
			res[1] = - cbrt(-pq[1]) - 1.f / 3 * abc[0];
			return (2);
		}
	}
	else if (d < 0) /* three real solutions */
	{
		phi = 1.f / 3 * acos(-pq[1] / sqrt(-(pq[0] * pq[0] * pq[0])));
		t = 2 * sqrt(-pq[0]);
		res[0] = t * cos(phi) - 1.f / 3 * abc[0];
		res[1] = -t * cos(phi + M_PI / 3.f) - 1.f / 3 * abc[0];
		res[2] = -t * cos(phi - M_PI / 3.f) - 1.f / 3 * abc[0];
		return (3);
	}
	/* one real solution */
	t = sqrt(d);
	res[0] = (cbrt(t - pq[1]) - cbrt(t + pq[1])) - 1.f / 3 * abc[0];
	return (1);
}

int 				ft_solve_quartic(const double coef[5],  double res[4])
{
	double	abcd[4];
	double 	pqr[3];
	double 	tmp;
	double 	sub;
	int 	num;
	double 	uv[2];
	int 	i;

/* to normal form: x^4 + Ax^3 + Bx^2 + Cx + D = 0 */

	abcd[0] = coef[1] / coef[0];
	abcd[1] = coef[2] / coef[0];
	abcd[2] = coef[3] / coef[0];
	abcd[3] = coef[4] / coef[0];
	sub = 0.25f * abcd[0];

/*  substitute x = y - A/4 to eliminate cubic term: x^4 + px^2 + qx + r = 0 */
	tmp = abcd[0] * abcd[0];
	pqr[0] = -3.f / 8 * tmp + abcd[1];
	pqr[1] = 1.f / 8 * tmp * abcd[0] - 0.5f * abcd[0] * abcd[1] + abcd[2];
	pqr[2] = -3.f / 256 * tmp * tmp + 1.f / 16 * tmp * abcd[1] - 0.25f * abcd[0] * abcd[2] + abcd[3];
	if (IS_ZERO(pqr[2])) /* no absolute term: y(y^3 + py + q) = 0 */
	{
		abcd[0] = 1;
		abcd[1] = 0;
		abcd[2] = pqr[0];
		abcd[3] = pqr[1];
		num = ft_solve_cubic(abcd, res);
		res[num++] = 0.f;
	}
	else
	{
		abcd[0] = 1;
		abcd[1] = -0.5f * pqr[0];
		abcd[2] = -pqr[2];
		abcd[3] = 0.5f * pqr[2] * pqr[0] - 1.f / 8 * pqr[1] * pqr[1];
		num = ft_solve_cubic(abcd, res); /* only 1 real solution */
		/* ... to build two quadric equations */
		i = -1;
		while (++i < num)
		{
			tmp = res[i];
			uv[0] = tmp * tmp - pqr[2];
			uv[1] = 2 * tmp - pqr[0];
			if (uv[0] > -EQN_EPS && uv[1] > -EQN_EPS)
				break ;
		}
		if (uv[0] < -1e-1)
		{
//			printf("uv[0] %f, coef %f, %f, %f, %f, %f\n", uv[0], coef[0], coef[1], coef[2], coef[3],
//					coef[4]);
			return (0);
		}
		uv[0] = IS_ZERO(uv[0]) ? 0.f : sqrt(fabs(uv[0]));
		if (uv[1] < -1e-1)
		{
//			printf("uv[1] %f, coef %f, %f, %f, %f, %f\n", uv[1], coef[0], coef[1], coef[2], coef[3],
//					coef[4]);
			return (0);
		}
		uv[1] = IS_ZERO(uv[1]) ? 0.f : sqrt(fabs(uv[1]));
		num = ft_solve_sqr_(1, pqr[1] < 0 ? uv[1] : -uv[1], tmp + uv[0], res);
		num += ft_solve_sqr_(1, pqr[1] < 0 ? -uv[1] : uv[1], tmp - uv[0], res + num);
	}
	i = -1;
	while (++i < num)
		res[i] -= sub;
	return (num);
}
