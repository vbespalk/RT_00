/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 13:25:05 by domelche          #+#    #+#             */
/*   Updated: 2018/08/23 13:25:05 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_point3		ft_change_blur_vec(t_point3 norm, t_point3 vec, float angle)
{
	t_point3	proj;

	proj = ft_3_vector_project(norm, vec);
	if (acos(ft_3_vector_cos(norm, vec)) + angle <= M_PI_2)
		return (vec);
	return (ft_3_vector_turn(proj, norm, M_PI_2 - angle));
}

t_point3		ft_get_blur_proj(t_point3 origin, t_point3 norm)
{
	t_point3	zero_proj;
	float		angle;

	zero_proj = ft_3_vector_project(
		norm, ft_3_vectornew(origin, ft_3_pointnew(0.0, 0.0, 0.0)));
	if (ft_3_vector_len(zero_proj) == 0.0)
		zero_proj = ft_3_vector_project(
			norm, ft_3_vectornew(origin, ft_3_pointnew(42.0, 0.0, 0.0)));
	if (ft_3_vector_len(zero_proj) == 0.0)
		zero_proj = ft_3_vector_project(
			norm, ft_3_vectornew(origin, ft_3_pointnew(0.0, 42.0, 0.0)));
	zero_proj = ft_3_tounitvector(zero_proj);
	angle = (float)rand() / (float)RAND_MAX * M_2_PI;
	return (ft_3_vector_turn_near(zero_proj, norm, angle));
}

t_color			ft_sum_colors(t_coll coll, t_color color_s, t_color color_t)
{
	t_color		res;
	t_object	*o;
	int			i;
	float		illum;

	res.val = 0;
	o = coll.o;
	i = -1;
	while (++i < 3)
	{
		illum = (float)ft_limitf(
			0.0, 1.0, o->ambnt + (float)(coll.illum_color.argb[i]) / 255.0);
		res.argb[i] = (t_byte)(
			(float)(o->color.argb[i]) * illum * o->diff +
			(float)(color_s.argb[i]) * o->spclr +
			(float)(color_t.argb[i]) * o->trans);
	}
	return (res);
}
