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

static void		ft_init_ray
					(t_ray *ray_prev, t_ray *ray, t_vector *o, t_vector *d)
{
	int		i;

	ray->o = *o;
	ray->d = *d;
	ray->stack_i = ray_prev->stack_i;
	i = -1;
	while (++i < STACK_SIZE)
		ray->stack[i] = ray_prev->stack[i];
}

t_color			ft_throw_ray(t_thrarg *parg, t_ray *ray, int depth)
{
	t_ray		next_ray;
	t_coll		coll;
	t_color		spclr_col;
	t_color		trans_col;
	float		num[2];

	spclr_col.val = 0;
	trans_col.val = 0;
	coll = ft_get_collision(parg, ray);
	ray->coll = &coll;
	if (depth == 0)
		parg->e->pix_obj[ray->pix] = coll.o;
	if (!coll.o)
		return (parg->e->scn->bg_color);
	num[1] = depth;
	if (coll.o->spclr && depth < DEPTH)
	{
		ft_init_ray(ray, &next_ray, &(coll.coll_pnt), &(coll.spclr_vec));
		num[0] = coll.o->s_blur;
		spclr_col = (coll.o->s_blur) ?
			ft_throw_rays(parg, &next_ray, &(coll.spclr_vec), num) :
			ft_throw_ray(parg, &next_ray, depth + 1);
	}
	if (coll.o->trans && depth < DEPTH && !ft_3_isnullpoint(coll.trans_vec))
	{
		ft_init_ray(ray, &next_ray, &(coll.coll_pnt), &(coll.trans_vec));
		ft_handle_hit(&next_ray, coll.o);
		num[0] = coll.o->t_blur;
		trans_col = (coll.o->t_blur) ?
			ft_throw_rays(parg, &next_ray, &(coll.trans_vec), num) :
			ft_throw_ray(parg, &next_ray, depth + 1);
	}
	return ((coll.o->phong != 0.0) ?
		ft_apply_phong(ft_sum_colors(&coll, spclr_col, trans_col, depth),
			coll.phong, coll.phong_color) :
		ft_sum_colors(&coll, spclr_col, trans_col, depth));
}

t_color			ft_add_blur_colors(t_color sum, int num, t_color new)
{
	int		i;

	if (!num)
		return (new);
	i = 4;
	while (--i > 0)
		sum.argb[i] = (t_byte)((float)(sum.argb[i] + new.argb[i]) /
			(float)(num + 1));
	return (sum);
}

t_color			ft_throw_rays
					(t_thrarg *parg, t_ray *ray, t_vector *vec, float num[2])
{
	float		max_angle;
	int			rays;
	int			i;
	t_color		color[2];
	t_vector	od[2];

	max_angle = ft_torad(num[0] * 30.0f);
	rays = ft_limit(1, 100, (int)(sinf(max_angle) * 200.0f));
	i = -1;
	color[1].val = 0;
	*vec = ft_change_blur_vec(ray->coll->norm, *vec, max_angle);
	while (++i < rays)
	{
		od[0] = ray->coll->coll_pnt;
		od[1] = ft_3_vector_turn(ft_get_blur_proj(ray->coll->coll_pnt, *vec),
			*vec, (float)rand() / (float)RAND_MAX * max_angle);
		color[0] = ft_throw_ray(parg, ray, (int)(num[1] + 1));
		color[1] = ft_add_blur_colors(color[1], i, color[0]);
	}
	return (color[1]);
}

t_color			ft_trace_ray(t_thrarg *parg, int x, int y)
{
	t_ray		ray;
	t_color		res;

	ray.stack_i = -1;
	if (parg->e->scn->cam->inner_o)
	{
		ray.stack[0] = parg->e->scn->cam->inner_o;
		ray.stack_i = 0;
//		printf("start refraction: %f\n", parg->e->scn->cam->inner_o->refr);
	}
//	else
//		printf(" --- no start object --- \n");
	ray.pix = (Uint32)(y * parg->e->sdl->scr_wid + x);
	ray.o = parg->e->scn->cam->origin;
	ray.d = parg->e->scn->cam->vs_start_point;
	ray.d = ray.d + ft_3_vector_scale(parg->e->scn->cam->vs_x_step_vec, x);
	ray.d = ray.d + ft_3_vector_scale(parg->e->scn->cam->vs_y_step_vec, y);
	ray.d = ft_3_unitvectornew(parg->e->scn->cam->origin, ray.d);
	res = ft_throw_ray(parg, &ray,  0);
	return (res);
}
