/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 12:48:18 by vbespalk          #+#    #+#             */
/*   Updated: 2018/08/28 12:48:20 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float		vec_mod(t_vector *v)
{
	if (!v)
		return (-1);
	return (sqrt((*v)[0] * (*v)[0] + (*v)[1] * (*v)[1] + (*v)[2] * (*v)[2]));
}

t_vector	*normilize_vec(t_vector *v)
{
	float mod;

	if (!v)
		return (NULL);
	mod = vec_mod(v);
	if (!mod)
		return (v);
	(*v)[0] /= mod;
	(*v)[1] /= mod;
	(*v)[2] /= mod;
	return (v);
}

float		dot_product(t_vector v1, t_vector v2)
{
	return (v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2]);
}

t_vector	vec_scalar_mult(t_vector v, float s)
{
	t_vector v1;

	v1[0] = v[0] * s;
	v1[1] = v[1] * s;
	v1[2] = v[2] * s;
	return (v1);
}

t_vector	cross_prod(t_vector u, t_vector v)
{
	t_vector res;

	res[0] = (u[1] * v[2] - u[2] * v[1]);
	res[1] = (u[2] * v[0] - u[0] * v[2]);
	res[2] = (u[0] * v[1] - u[1] * v[0]);
	return (res);
}
