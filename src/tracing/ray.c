/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 13:25:05 by domelche          #+#    #+#             */
/*   Updated: 2018/08/23 13:25:05 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_color	ft_throw_trans(t_thrarg *parg, t_ray *ray, int depth)
{
	t_color		zero;
	float		num[2];
	t_vector	coll_pnt;
	t_ray		next_ray;
	t_object	*(stack[parg->e->scn->depth]);

	zero.val = 0;
	next_ray.stack_size = parg->e->scn->depth;
	ft_bzero(&stack, next_ray.stack_size * sizeof(t_object *));
	next_ray.stack = stack;
	num[1] = depth;
	if (ray->coll->o->trans && depth < parg->e->scn->depth
	&& !ft_3_isnullpoint(ray->coll->trans_vec))
	{
		coll_pnt =
			ray->coll->coll_pnt - ft_3_vector_scale(ray->coll->norm, SHIFT);
		ft_init_ray(ray, &next_ray, &coll_pnt, &(ray->coll->spclr_vec));
		ft_handle_hit(&next_ray, ray->coll->o);
		num[0] = ray->coll->o->t_blur;
		next_ray.d = ray->coll->trans_vec;
		return ((ray->coll->o->t_blur)
			? ft_throw_rays(parg, &next_ray, num)
			: ft_throw_ray(parg, &next_ray, depth + 1));
	}
	return (zero);
}

static t_color	ft_throw_spclr(t_thrarg *parg, t_ray *ray, int depth)
{
	t_color		zero;
	float		num[2];
	t_vector	coll_pnt;
	t_ray		next_ray;
	t_object	*(stack[parg->e->scn->depth]);

	zero.val = 0;
	next_ray.stack_size = parg->e->scn->depth;
	ft_bzero(&stack, next_ray.stack_size * sizeof(t_object *));
	next_ray.stack = stack;
	num[1] = depth;
	if (ray->coll->o->spclr && depth < parg->e->scn->depth)
	{
		coll_pnt =
			ray->coll->coll_pnt + ft_3_vector_scale(ray->coll->norm, SHIFT);
		ft_init_ray(ray, &next_ray, &coll_pnt, &(ray->coll->spclr_vec));
		num[0] = ray->coll->o->s_blur;
		next_ray.d = ray->coll->spclr_vec;
		return ((ray->coll->o->s_blur)
			? ft_throw_rays(parg, &next_ray, num)
			: ft_throw_ray(parg, &next_ray, depth + 1));
	}
	return (zero);
}

t_color			ft_throw_ray(t_thrarg *parg, t_ray *ray, int depth)
{
	t_coll		coll;
	t_color		st_col[2];

	st_col[0].val = 0;
	st_col[1].val = 0;
	coll = ft_get_collision(parg, ray);
	ray->coll = &coll;
	if (depth == 0)
		parg->e->pix_obj[ray->pix] = coll.o;
	if (coll.o == NULL)
	{
		if (parg->e->scn->skybox_on)
			return (ft_apply_sky(parg->e->scn->skybox, ray->o, ray->d));
		return (parg->e->scn->bg_color);
	}
	st_col[0] = ft_throw_spclr(parg, ray, depth);
	st_col[1] = ft_throw_trans(parg, ray, depth);
	return ((coll.o->phong != 0.0)
		? ft_apply_phong(ft_sum_colors(&coll, st_col[0], st_col[1]),
			coll.phong, coll.phong_color)
		: ft_sum_colors(&coll, st_col[0], st_col[1]));
}

t_color			ft_throw_rays(t_thrarg *parg, t_ray *ray, float num[2])
{
	float		max_angle;
	int			i[3];
	t_color		color;
	float		color_sum[3];

	ft_bzero(color_sum, 3 * sizeof(float));
	max_angle = ft_torad(num[0] * 45.0f);
	i[2] = ft_limit(1, (int)(50.0f * sinf(ft_torad(45.0f))),
		(int)(sinf(max_angle) * 50.0f));
	if (ft_3_vector_cos(ray->d, ray->coll->norm) < 0)
		ray->coll->norm = ft_3_vector_invert(ray->coll->norm);
	ray->d = ft_change_blur_vec(ray->coll->norm, ray->d, max_angle);
	i[0] = -1;
	while (++i[0] < i[2])
	{
		ray->d = ft_3_vector_random_cone(ray->d, max_angle);
		color = ft_throw_ray(parg, ray, (int)(num[1] + 1));
		i[1] = -1;
		while (++i[1] < 3)
			color_sum[i[1]] += (float)(color.argb[i[1]]) / (float)(i[2]);
	}
	color.argb[0] = (t_byte)(color_sum[0]);
	color.argb[1] = (t_byte)(color_sum[1]);
	color.argb[2] = (t_byte)(color_sum[2]);
	return (color);
}

t_color			ft_trace_ray(t_thrarg *parg, int x, int y)
{
	t_object	*(stack[parg->e->scn->depth]);
	t_ray		ray;
	t_color		res;
	t_vector	d;

	ray.stack_size = parg->e->scn->depth;
	ft_bzero(&stack, ray.stack_size * sizeof(t_object *));
	ray.stack = stack;
	ray.stack_i = -1;
	if (parg->e->scn->cam->inner_o)
	{
		ray.stack[0] = parg->e->scn->cam->inner_o;
		ray.stack_i = 0;
	}
	ray.pix = (Uint32)(y * parg->e->sdl->scr_wid + x);
	ray.o = parg->e->scn->cam->origin;
	d = parg->e->scn->cam->vs_start_point;
	d = d + ft_3_vector_scale(parg->e->scn->cam->vs_x_step_vec, x);
	d = d + ft_3_vector_scale(parg->e->scn->cam->vs_y_step_vec, y);
	d = ft_3_unitvectornew(parg->e->scn->cam->origin, d);
	ray.d = d;
	res = ft_throw_ray(parg, &ray, 0);
//	res = ft_blind(parg->e, res, &ray);
	return (res);
}
