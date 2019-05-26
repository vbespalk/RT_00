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

void			ft_init_ray(
					t_ray *ray_prev, t_ray *ray, t_vector *o, t_vector *d)
{
	int		i;

	ray->o = *o;
	ray->d = *d;
	ray->coll = ray_prev->coll;
	ray->stack_i = ray_prev->stack_i;
	i = -1;
	while (++i < (int)ray->stack_size)
		ray->stack[i] = ray_prev->stack[i];
}

t_vector		ft_change_blur_vec(t_vector norm, t_vector vec, float angle)
{
	t_vector	proj;
	float		nv_angle;

	nv_angle = acosf(ft_3_vector_cos(norm, vec));
	if (nv_angle + angle < M_PI_2)
		return (vec);
	proj = ft_3_tounitvector(ft_3_vector_project(norm, vec));
	return (ft_3_vector_turn(proj, norm, (float)M_PI_2 - angle - nv_angle));
}

t_color			ft_sum_colors(t_coll *coll, t_color color_s, t_color color_t)
{
	t_color		res;
	t_object	*o;
	int			i;
	float		illum;

	res.val = UINT32_MAX;
	o = coll->o;
	i = -1;
	while (++i < 3)
	{
		illum = (float)ft_limitf(
			0.0, 1.0, o->ambnt + (float)(coll->illum_color.argb[i]) / 255.0);
		res.argb[i] = (t_byte)((!coll->o->spclr || !coll->o->trans)
			? ((float)(coll->px_color.argb[i]) * illum * o->diff +
				(float)(color_s.argb[i]) * coll->o->spclr +
				(float)(color_t.argb[i]) * coll->o->trans)
			: ((float)(coll->px_color.argb[i]) * illum * o->diff +
				(1.0f - o->diff) *
				((float)(color_s.argb[i]) * coll->fresnel +
				(float)(color_t.argb[i]) * (1.0f - coll->fresnel))));
	}
	return (res);
}

t_color			ft_blind(t_env *e, t_color color, t_ray *ray)
{
	float		k;
	float		cos;
	t_list		*node;
	t_light		*l;
	t_vector	l_dir;

	if (e->pix_obj[ray->pix])
		return (color);
	node = e->scn->lights;
	while (node)
	{
		l = (t_light *)(node->content);
		l_dir = (l->type == L_POINT)
			? ft_3_unitvectornew(ray->o, l->origin)
			: ft_3_vector_scale(l->direct, -1.0f);
		if ((cos = ft_3_vector_cos(ray->d, l_dir)) > 0.95f)
		{
			k = (float)(pow(cos - 0.95f, 2) * 400.0f) * l->bright;
			color = ft_add_colors(color, ft_scale_color(l->color, k));
		}
		node = node->next;
	}
	return (color);
}
