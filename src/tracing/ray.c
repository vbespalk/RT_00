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

static t_color	ft_throw_ray(t_parg *parg, t_point3 od[2], int depth)
{
	t_coll		coll;
	t_color		spclr_col;
	t_color		trans_col;
	float		num[2];

	spclr_col.val = 0;
	trans_col.val = 0;
	coll = ft_get_collision(parg, od[0], od[1]);
	if (!coll.o)
		return (parg->e->scn->bg_color);
	od[0] = coll.coll_pnt;
	num[1] = depth;
	if (coll.o->spclr && depth < DEPTH)
	{
		od[1] = coll.spclr_vec;
		num[0] = coll.o->s_blur;
		spclr_col = (coll.o->s_blur) ?
			ft_throw_rays(parg, coll, &(coll.spclr_vec), num) :
			ft_throw_ray(parg, od, depth + 1);
	}
	if (coll.o->trans && depth < DEPTH)
	{
		od[1] = coll.trans_vec;
		num[0] = coll.o->t_blur;
		trans_col = (coll.o->t_blur) ?
			ft_throw_rays(parg, coll, &(coll.trans_vec), num) :
			ft_throw_ray(parg, od, depth + 1);
	}
	return ((coll.o->phong != 0.0) ?
		ft_apply_phong(ft_sum_colors(coll, spclr_col, trans_col),
			coll.phong, coll.phong_color) :
		ft_sum_colors(coll, spclr_col, trans_col));
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
					(t_parg *parg, t_coll coll, t_point3 *vec, float num[2])
{
	float		max_angle;
	int			rays;
	int			i;
	t_color		color[2];
	t_point3	od[2];

	max_angle = ft_torad(num[0] * 10.0f);
	rays = ft_limit(1, 10, (int)(sin(max_angle) * 10.0));
	i = -1;
	color[1].val = 0;
	*vec = ft_change_blur_vec(coll.norm, *vec, max_angle);
	while (++i < rays)
	{
		od[0] = coll.coll_pnt;
		od[1] = ft_3_vector_turn(ft_get_blur_proj(coll.coll_pnt, *vec),
			*vec, (float) rand() / (float) RAND_MAX * max_angle);
		color[0] = ft_throw_ray(parg, od, (int)(num[1] + 1));
		color[1] = ft_add_blur_colors(color[1], i, color[0]);
	}
	return (color[1]);
}

t_color			ft_trace_ray(t_parg *parg, int x, int y)
{
	t_color		res;
	t_point3	od[2];

	od[0] = parg->e->scn->cam->origin;
	od[1] = parg->e->scn->cam->vs_start_point;
	od[1] = ft_3_vector_add(od[1],
		ft_3_vector_scale(parg->e->scn->cam->vs_x_step_vec, x));
	od[1] = ft_3_vector_add(od[1],
		ft_3_vector_scale(parg->e->scn->cam->vs_y_step_vec, y));
	od[1] = ft_3_unitvectornew(parg->e->scn->cam->origin, od[1]);
	res = ft_throw_ray(parg, od, 0);
	return (res);
}
