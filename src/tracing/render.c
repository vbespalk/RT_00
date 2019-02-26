/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 13:25:05 by domelche          #+#    #+#             */
/*   Updated: 2018/08/23 13:25:05 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ft_get_vs_params(t_sdl *sdl, t_camera *cam)
{
	cam->direct = ft_3_vector_rotate(
		(t_vector){ 1.0f, 0.0f, 0.0f },
		cam->angles[0], cam->angles[1], cam->angles[2]);
	cam->vs_start_vec = ft_3_vector_rotate(
		(t_vector){ 0.0f, sdl->scr_hei / 2.0f, sdl->scr_wid / -2.0f },
		cam->angles[0], cam->angles[1], cam->angles[2]);
	cam->vs_x_step_vec = ft_3_vector_rotate(
		(t_vector){ 0.0f, 0.0f, 1.0f },
		cam->angles[0], cam->angles[1], cam->angles[2]);
	cam->vs_y_step_vec = ft_3_vector_rotate(
		(t_vector){ 0.0f, -1.0f, 0.0f },
		cam->angles[0], cam->angles[1], cam->angles[2]);
	cam->vs_start_point =
		cam->vs_start_vec + cam->origin + ft_3_vector_rotate(
			(t_vector){
				(sdl->scr_wid / 2.0f) / (float)tan(cam->fov / 2.0f),
				0.0f,
				0.0f
				},
			cam->angles[0], cam->angles[1], cam->angles[2]);
}

/*
**	x/y[0] - start point, iterator;
**	x/y[1] - end point;
*/

void	*ft_section_handle(void *arg)
{
	t_thrarg	*thrarg;
	int			x[2];
	int			y[2];
	int			y_iter;

	thrarg = (t_thrarg *)arg;
	x[0] = (thrarg->i % 4) * (thrarg->e->sdl->scr_wid / (THREADS / 2) - 1);
	y[0] = (thrarg->i / 4) * (thrarg->e->sdl->scr_hei / 2 - 1);
	x[1] = x[0] + thrarg->e->sdl->scr_wid / (THREADS / 2) + 1;
	y[1] = y[0] + thrarg->e->sdl->scr_hei / 2 + 1;
	while (++x[0] < x[1])
	{
		y_iter = y[0];
		while (++y_iter < y[1])
			img_pixel_put(thrarg->e, x[0], y_iter,
				ft_trace_ray(thrarg, x[0], y_iter).val);
	}
	return (NULL);
}

void	ft_render(t_env *e)
{
	pthread_t	threads[THREADS];
	t_thrarg	thrargs[THREADS];
	int			i;

	ft_get_vs_params(e->sdl, e->scn->cam);
	ft_get_start_refr(e->scn);
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
