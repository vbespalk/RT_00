/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 13:25:05 by domelche          #+#    #+#             */
/*   Updated: 2019/05/06 18:55:45 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		ft_get_vs_params(t_sdl *sdl, t_camera *cam)
{
	cam->direct = ft_3_vector_rotate(
		(t_vector) { 1.0f, 0.0f, 0.0f },
		cam->angles[0], cam->angles[1], cam->angles[2]);
	cam->vs_start_vec = ft_3_vector_rotate(
		(t_vector) { 0.0f, sdl->scr_hei / 2.0f, sdl->rt_wid / -2.0f },
		cam->angles[0], cam->angles[1], cam->angles[2]);
	cam->vs_x_step_vec = ft_3_vector_scale(
		ft_3_vector_rotate(
			(t_vector) { 0.0f, 0.0f, 1.0f },
			cam->angles[0], cam->angles[1], cam->angles[2]),
		1.0f / (float)(cam->smooth + 1));
	cam->vs_y_step_vec = ft_3_vector_scale(
		ft_3_vector_rotate(
			(t_vector) { 0.0f, -1.0f, 0.0f },
			cam->angles[0], cam->angles[1], cam->angles[2]),
		1.0f / (float)(cam->smooth + 1));
	cam->vs_start_point =
		cam->vs_start_vec + cam->origin + ft_3_vector_rotate(
			(t_vector){
				(sdl->rt_wid / 2.0f) / tanf(cam->fov / 2.0f), 0.0f, 0.0f },
			cam->angles[0], cam->angles[1], cam->angles[2]);
}

static t_color	ft_get_pixel_color(t_thrarg *thrarg, int x, int y, int smth)
{
	t_color	color;
	float	nums[4];
	int		i[2];

	x = x * smth - 1;
	y = y * smth - 1;
	i[0] = x + smth + 1;
	i[1] = y + smth + 1;
	ft_bzero((void *)nums, sizeof(nums));
	nums[3] = smth * smth;
	while (++x < i[0])
	{
		y = i[1] - smth - 1;
		while (++y < i[1])
		{
			color = ft_trace_ray(thrarg, x, y);
			nums[0] += (float)(color.argb[0]) / nums[3];
			nums[1] += (float)(color.argb[1]) / nums[3];
			nums[2] += (float)(color.argb[2]) / nums[3];
		}
	}
	color.argb[0] = (t_byte)(nums[0]);
	color.argb[1] = (t_byte)(nums[1]);
	color.argb[2] = (t_byte)(nums[2]);
	return (color);
}

static void		ft_update_obj_lst(t_camera *cam, t_list *objs)
{
	t_object *o;

	while (objs)
	{
		o = ((t_object *)objs->content);
		o->dist = ft_3_vector_len(o->translate - cam->origin);
		objs = objs->next;
	}
}

void			*ft_section_handle(void *arg)
{
	int			x;
	int			y;
	int			smth;
	t_color		col;
	t_thrarg	*thrarg;

	thrarg = (t_thrarg *)arg;
	x = thrarg->i;
	smth = thrarg->e->scn->cam->smooth + 1;
	while (x < thrarg->e->sdl->rt_wid)
	{
		y = -1;
		while (++y < thrarg->e->sdl->scr_hei)
		{
			col = (thrarg->e->color_mode == NULL)
			? ft_get_pixel_color(thrarg, x, y, smth)
			: ft_px_mode(
				ft_get_pixel_color(thrarg, x, y, smth), thrarg->e->color_mode);
			img_pixel_put(thrarg->e->sdl, x, y, (unsigned int)SDL_MapRGB(
				thrarg->e->sdl->format, col.argb[0], col.argb[1], col.argb[2]));
		}
		x += THREADS;
	}
	return (NULL);
}

void			ft_render(t_env *e)
{
	pthread_t	threads[THREADS];
	t_thrarg	thrargs[THREADS];
	int			i;

	ft_get_vs_params(e->sdl, e->scn->cam);
	ft_get_start_stack(e->scn);
	ft_update_obj_lst(e->scn->cam, e->scn->objs);
	i = -1;
	while (++i < THREADS)
	{
		thrargs[i].i = i;
		thrargs[i].e = e;
	}
	i = -1;
	while (++i < THREADS)
		pthread_create(&threads[i], NULL,
			ft_section_handle, (void *)&thrargs[i]);
	i = -1;
	while (++i < THREADS)
		pthread_join(threads[i], NULL);
}
