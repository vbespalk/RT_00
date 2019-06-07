/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paraboloid_coll_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 18:55:04 by domelche          #+#    #+#             */
/*   Updated: 2019/05/25 18:55:06 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float	ft_get_prbld_caps_coll(t_list **objs, t_vector v[4][2], t_object *obj)
{
	int			i;
	float		t;
	t_vector	hit;
	t_prbld		*par;

	i = 0;
	par = (t_prbld *)(obj->fig);
	v[0][0][1] -= par->maxh;
	t = (par->maxh == FLT_MAX) ? FLT_MAX : -(v[0][0][1]) / v[0][1][1];
	if (t <= 0 || t == FLT_MAX)
		return (FLT_MAX);
	v[2][1] = v[0][0] + ft_3_vector_scale(v[0][1], t);
	if (ft_3_vector_dot(v[2][1], v[2][1]) > 4.0f * par->maxh)
		return (FLT_MAX);
	hit = v[1][0] + ft_3_vector_scale(v[1][1], t);
	v[3][1] = ft_get_norm_plane(obj->fig, &(obj->inverse), v[2][1]);
	if (obj->is_neg)
		hit += ft_3_vector_scale(v[3][1], SHIFT);
	if (obj->react_neg || obj->is_neg)
		i = ft_inside_type(objs, hit);
	if (ft_is_invisible(obj, i))
		return (FLT_MAX);
	v[2][1][1] += par->maxh;
	return (t);
}

double	ft_get_prbld_cides_coll(
			t_list **objs, t_vector v[4][2], double *t, t_object *obj)
{
	int			i[2];
	t_vector	hit[4];
	t_prbld		*par;

	par = (t_prbld *)(obj->fig);
	i[0] = -1;
	i[1] = 0;
	while (++i[0] < 2)
	{
		hit[i[0]] = v[0][0] + ft_3_vector_scale(v[0][1], (float)t[i[0]]);
		if (t[i[0]] >= 0 && IN_RANGE(hit[i[0]][1], 0, par->maxh))
		{
			hit[i[0] + 2] =
				v[1][0] + ft_3_vector_scale(v[1][1], (float)t[i[0]]);
			v[3][0] = obj->ft_get_norm(obj->fig, &obj->inverse, hit[i[0]]);
			if (obj->is_neg)
				hit[i[0] + 2] += ft_3_vector_scale(v[3][0], SHIFT);
			if (obj->react_neg || obj->is_neg)
				i[1] = ft_inside_type(objs, hit[i[0] + 2]);
			if (ft_is_invisible(obj, i[1]))
				continue ;
			v[2][0] = hit[i[0]];
			return (t[i[0]]);
		}
	}
	return (FLT_MAX);
}
