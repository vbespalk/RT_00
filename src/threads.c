/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 20:46:17 by vbespalk          #+#    #+#             */
/*   Updated: 2018/09/21 20:46:19 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	*thread_funct(void *ptr)
{
	t_thread		*th;
	int				i;
	int				j;
	unsigned int	color;
	t_ray			ray;

	th = (t_thread *)ptr;
	j = th->s_pix - 1;
	while (++j < th->e_pix)
	{
		i = -1;
		while (++i < th->env->sdl->scr_wid)
		{
			ray.dir = ray_generate(th->env, i, j);
			ray.ori = th->env->scn->r_ori;
			if (cast_ray(&ray, th->env, j * th->env->sdl->scr_wid + i))
			{
				color = get_rgb(th->env->sdl, ray.hit_c[0], ray.hit_c[1], ray.hit_c[2]);
				img_pixel_put(th->env, i, j, color);
			}
			else
				img_pixel_put(th->env, i, j, get_rgb(th->env->sdl, 0, 0, 0));
		}
	}
	return (NULL);
}

int		mult_threads(t_env *e)
{
	int			count;
	pthread_t	threads_id[NB_THREADS];
	t_thread	th[NB_THREADS];

	count = -1;
	while (++count < NB_THREADS)
		th[count].env = e;
	count = -1;
	while (++count < NB_THREADS)
	{
		th[count].s_pix = count * e->sdl->scr_hei / NB_THREADS;
		th[count].e_pix = th[count].s_pix + e->sdl->scr_hei / NB_THREADS + 1;
		if (pthread_create((&(threads_id[count])), NULL, \
			thread_funct, &th[count]))
			ft_error("error creating thread\n");
	}
	count = -1;
	while (++count < NB_THREADS)
		if (pthread_join(threads_id[count], NULL))
			ft_error("error joining thread\n");
	return (0);
}
