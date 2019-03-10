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

t_vector		ft_change_blur_vec(t_vector norm, t_vector vec, float angle)
{
	t_vector	proj;

	if (acosf(ft_3_vector_cos(norm, vec)) + angle <= M_PI_2)
		return (vec);
	proj = ft_3_tounitvector(ft_3_vector_project(norm, vec));
	return (ft_3_vector_turn(proj, norm, (float)M_PI_2 - angle));
}

t_vector		ft_get_blur_proj(t_vector origin, t_vector norm)
{
	t_vector	zero_proj;
	float		angle;

	zero_proj = ft_3_vector_project(
		norm, ((t_vector){0.0f, 0.0f, 0.0f} - origin));
	if (ft_3_vector_len(zero_proj) == 0.0)
		zero_proj = ft_3_vector_project(
			norm, ((t_vector){42.0f, 0.0f, 0.0f} - origin));
	if (ft_3_vector_len(zero_proj) == 0.0)
		zero_proj = ft_3_vector_project(
			norm, ((t_vector){0.0, 42.0, 0.0} - origin));
	zero_proj = ft_3_tounitvector(zero_proj);
	angle = (float)rand() / (float)RAND_MAX * (float)M_2_PI;
	return (ft_3_vector_turn_near(zero_proj, norm, angle));
}

t_color			ft_sum_colors
		(t_coll *coll, t_color color_s, t_color color_t, int depth)
{
	t_color		res;
	t_object	*o;
	int			i;
	float		illum;

	res.val = 0;
	o = coll->o;
	if (coll->o->ft_mapping && coll->o->texture)
		res.val = coll->o->ft_mapping(coll->o->fig, coll->o->texture, coll->coll_pnt);
	else
		res.val = o->color.val;
	i = -1;
	while (++i < 3)
	{
		illum = (float)ft_limitf(
				0.0, 1.0, o->ambnt + (float)(coll->illum_color.argb[i]) / 255.0);
		res.argb[i] = (t_byte)(
				(!coll->o->spclr || !coll->o->trans)
				? ((float)(res.argb[i]) * illum * o->diff +
				   (float)(color_s.argb[i]) * coll->o->spclr +
				   (float)(color_t.argb[i]) * coll->o->trans)
				: ((float)(res.argb[i]) * illum * o->diff +
				   (1.0f - o->diff) *
				   ((float)(color_s.argb[i]) * coll->fresnel +
					(float)(color_t.argb[i]) * (1.0f - coll->fresnel))));
	}
	return (res);
}
