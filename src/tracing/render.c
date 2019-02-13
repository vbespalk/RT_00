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

static void	ft_get_vs_params(t_camera *cam)
{
	cam->direct = ft_3_vector_rotate(
		(t_vector){ 1.0f, 0.0f, 0.0f },
		cam->angles[0], cam->angles[1], cam->angles[2]);
	cam->vs_start_vec = ft_3_vector_rotate(
		(t_vector){ 0.0f, SCR_HEI / 2.0f, -SCR_WID / 2.0f },
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
				(SCR_WID / 2.0f) / (float)tan(cam->fov / 2.0f),
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
	int			x;
	int			y;

	thrarg = (t_thrarg *)arg;
	x = thrarg->i;
	while (x < thrarg->e->sdl->scr_wid)
	{
		y = -1;
		while (++y < thrarg->e->sdl->scr_hei)
//			img_pixel_put(
//				thrarg->e, x, y,
					(unsigned int)ft_trace_ray(thrarg, x, y).val;
		x += THREADS;
	}
	return (NULL);
}

void	ft_render(t_env *e)
{
	pthread_t	threads[THREADS];
	t_thrarg	thrargs[THREADS];
	int			i = 0;

	ft_get_vs_params(e->scn->cam);
	ft_get_start_refr(e->scn);
//	i = -1;
//	while (++i < THREADS)
//	{
		thrargs[i].i = i;
		thrargs[i].e = e;
//	}
//	i = -1;
//	while (++i < THREADS)
		pthread_create(&threads[i], NULL,
			ft_section_handle, (void *)&thrargs[i]);
//	i = -1;
//	while (++i < THREADS)
		pthread_join(threads[i], NULL);
}
