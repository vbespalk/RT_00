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
	ray->coll = ray_prev->coll;
	ray->stack_i = ray_prev->stack_i;
	i = -1;

//	printf("size: %lu\n", ray->stack_size);

	while (++i < ray->stack_size)
		ray->stack[i] = ray_prev->stack[i];
}

t_color			ft_throw_ray(t_thrarg *parg, t_ray *ray, int depth)
{
	t_ray		next_ray;
	t_coll		coll;
	t_color		spclr_col;
	t_color		trans_col;
	t_object	*(stack[parg->e->scn->depth]);
	float		num[2];
	t_vector	coll_pnt;

//	printf("before inits\n");
	next_ray.stack_size = parg->e->scn->depth;
	ft_bzero(&stack, next_ray.stack_size * sizeof(t_object *));
	next_ray.stack = stack;
//	printf("after inits\n");

	spclr_col.val = 0;
	trans_col.val = 0;

//	printf("before collision\n");
	coll = ft_get_collision(parg, ray);
//	printf("after collision\n");

	ray->coll = &coll;
	if (depth == 0)
		parg->e->pix_obj[ray->pix] = coll.o;
	if (coll.o == NULL)
	{
		if (parg->e->scn->skybox_on)
		    return (ft_apply_sky(parg->e->scn->skybox, ray->o, ray->d));
		return (parg->e->scn->bg_color);
	}
	num[1] = depth;
	if (coll.o->spclr && depth < parg->e->scn->depth)
	{
		coll_pnt = coll.coll_pnt + ft_3_vector_scale(coll.norm, SHIFT);
		ft_init_ray(ray, &next_ray, &coll_pnt, &(coll.spclr_vec));
		num[0] = coll.o->s_blur;
		spclr_col = (coll.o->s_blur) ?
			ft_throw_rays(parg, &next_ray, &(coll.spclr_vec), num) :
			ft_throw_ray(parg, &next_ray, depth + 1);
	}
	if (coll.o->trans && depth < parg->e->scn->depth
		&& !ft_3_isnullpoint(coll.trans_vec))
	{
		coll_pnt = coll.coll_pnt - ft_3_vector_scale(coll.norm, SHIFT);
		ft_init_ray(ray, &next_ray, &coll_pnt, &(coll.trans_vec));

//		printf("before handle hit\n");
		ft_handle_hit(&next_ray, coll.o);
//		printf("after handle hit\n");

		num[0] = coll.o->t_blur;
		trans_col = (coll.o->t_blur) ?
			ft_throw_rays(parg, &next_ray, &(coll.trans_vec), num) :
			ft_throw_ray(parg, &next_ray, depth + 1);
	}
	return ((coll.o->phong != 0.0)
		? ft_apply_phong(ft_sum_colors(&coll, spclr_col, trans_col, depth),
			coll.phong, coll.phong_color)
		: ft_sum_colors(&coll, spclr_col, trans_col, depth));
}

t_color			ft_throw_rays
					(t_thrarg *parg, t_ray *ray, t_vector *vec, float num[2])
{
	float		max_angle;
	int			rays;
	int			j;
	int			i;
	t_vector	rand;
	t_color		color;
	float		color_sum[3];

	color_sum[0] = 0.0f;
	color_sum[1] = 0.0f;
	color_sum[2] = 0.0f;
	max_angle = ft_torad(num[0] * 45.0f);
	rays = ft_limit(1, (int)(50.0f * sinf(ft_torad(45.0f))),
		(int)(sinf(max_angle) * 50.0f));
	if (ft_3_vector_cos(*vec, ray->coll->norm) < 0)
		ray->coll->norm = ft_3_vector_scale(ray->coll->norm, -1.0f);
	*vec = ft_change_blur_vec(ray->coll->norm, *vec, max_angle);
	i = -1;
	while (++i < rays)
	{
		rand = ft_3_vector_random_cone(*vec, max_angle);
		ray->d = rand;
		color = ft_throw_ray(parg, ray, (int)(num[1] + 1));
		j = -1;
		while (++j < 3)
			color_sum[j] += (float)(color.argb[j]) / (float)(rays);
	}
	color.argb[0] = (t_byte)(color_sum[0]);
	color.argb[1] = (t_byte)(color_sum[1]);
	color.argb[2] = (t_byte)(color_sum[2]);
	return (color);
}

t_color			ft_blind(t_scene *scn, t_color color, t_vector o, t_vector d)
{
	float 		k;
	float 		cos;
	t_list		*node;
	t_light		*l;
	t_vector	l_dir;

	node = scn->lights;
	while (node)
	{
		l = (t_light *)(node->content);
		l_dir = (l->type == L_POINT)
			? ft_3_unitvectornew(o, l->origin)
			: ft_3_vector_scale(l->direct, -1.0f);
		if ((cos = ft_3_vector_cos(d, l_dir)) > 0.9f)
		{
			k = (float)(pow(cos - 0.9f, 2) * 100.0f);
			color = ft_add_colors(color, ft_scale_color(l->color, k));
		}
		node = node->next;
	}
	return (color);
}

t_color			ft_trace_ray(t_thrarg *parg, int x, int y)
{
	t_object	*(stack[parg->e->scn->depth]);
	t_ray		ray;
	t_color		res;
	t_vector	o;
	t_vector	d;

	ray.stack_size = parg->e->scn->depth;

//	printf("size in bzero: %lu\n", ray.stack_size * sizeof(t_object *));

	ft_bzero(&stack, ray.stack_size * sizeof(t_object *));
	ray.stack = stack;
	ray.stack_i = -1;
	if (parg->e->scn->cam->inner_o)
	{
		ray.stack[0] = parg->e->scn->cam->inner_o;
		ray.stack_i = 0;
	}
	ray.pix = (Uint32)(y * parg->e->sdl->scr_wid + x);
	o = parg->e->scn->cam->origin;
	ray.o = o;
	d = parg->e->scn->cam->vs_start_point;
	d = d + ft_3_vector_scale(parg->e->scn->cam->vs_x_step_vec, x);
	d = d + ft_3_vector_scale(parg->e->scn->cam->vs_y_step_vec, y);
	d = ft_3_unitvectornew(parg->e->scn->cam->origin, d);
	ray.d = d;
	res = ft_throw_ray(parg, &ray,  0);

//	res = ft_blind(parg->e->scn, res, o, d);
	return (res);
}
