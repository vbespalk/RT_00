/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 14:45:17 by vbespalk          #+#    #+#             */
/*   Updated: 2018/09/11 14:45:29 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			solve_qvadratic(float a, float b, float c, float *t)
{
	float q;
	float dis;
	float t0;
	float t1;

	dis = b * b - 4 * c * a;
	if (dis < 0)
		return (0);
	if (dis == 0)
	{
		*t = -0.5 * b / a;
		return (1);
	}
	q = (b >= 0) ? -0.5 * (b + sqrt(dis)) : -0.5 * (b - sqrt(dis));
	t0 = q / a;
	t1 = c / q;
	if (t0 > t1 || t0 < T_COEF)
		ft_swap(&t0, &t1, sizeof(t0));
	*t = t0;
	return (1);
}

int			s_intersect(t_vector dir, t_vector orig, t_object obj, float *t)
{
	float		a;
	float		b;
	float		c;
	t_vector	pos;

	pos = orig - obj.translate;
	a = dot_product(dir, dir);
	b = 2.0f * dot_product(dir, pos);
	c = dot_product(pos, pos) - (float)(obj.scale * obj.scale);
	if (!solve_qvadratic(a, b, c, t) || *t < T_COEF)
		return (0);
	return (1);
}

int			p_intersect(t_vector dir, t_vector orig, t_object obj, float *t)
{
	float		denom;
	t_vector	vec;

	vec = obj.translate - orig;
	if ((denom = dot_product(obj.rotate, dir)) < 0.0000001)
		return (0);
	*t = (dot_product(obj.translate, obj.rotate) - dot_product(orig, obj.rotate)) \
	/ denom;
	return (*t >= 0.01f);
}

int			cy_intersect(t_vector dir, t_vector orig, t_object obj, float *t)
{
	float		a;
	float		b;
	float		c;
	t_vector	x;
	t_vector	v;

	v = obj.rotate;
	x = orig - obj.translate;
	a = dot_product(dir, dir) - dot_product(dir, v) * dot_product(dir, v);
	b = 2.0f * (dot_product(x, dir) - dot_product(dir, v) * dot_product(x, v));
	c = dot_product(x, x) - dot_product(x, v) * dot_product(x, v) - \
	obj.scale * obj.scale;
	if (!solve_qvadratic(a, b, c, t) || *t < T_COEF)
		return (0);
	return (1);
}

int			co_intersect(t_vector dir, t_vector orig, t_object obj, float *t)
{
	float		a;
	float		b;
	float		c;
	t_vector	x;
	t_vector	v;
	t_cone		*cone;

	cone = (t_cone *)&(obj.fig);
	v = obj.rotate;
	x = orig - obj.translate;
	a = dot_product(dir, dir) - (1.0f + cone->tg2) * dot_product(dir, v) \
	* dot_product(dir, v);
	b = 2.0f * (dot_product(dir, x) - (1.0f + cone->tg2) * dot_product(dir, v) \
		* dot_product(x, v));
	c = dot_product(x, x) - (1.0f + cone->tg2) * dot_product(x, v) * \
	dot_product(x, v);
	if (!solve_qvadratic(a, b, c, t) || *t < T_COEF)
		return (0);
	return (1);
}
