/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 19:15:26 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/17 19:15:27 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_ev.h"

int		on_mouse_wheel(Sint32 y, Uint32 dir, t_env *e)
{
	Uint32	sum;

	if (dir == SDL_MOUSEWHEEL_NORMAL)
		sum = (y > 0) ? SDLK_z : SDLK_x;
	else
		sum = (y < 0) ? SDLK_z : SDLK_x;
	e->selected ? e->selected->ft_scale(sum, e->selected,
				&(e->selected->transform), &(e->selected->inverse)) :
	ft_scale_cam(sum, &(e->scn->cam->fov));
	return (1);
}

int		on_lbutton_down(int x, int y, t_env *e)
{
	if (x >= e->sdl->rt_wid || y >= e->sdl->scr_hei)
		return (0);
	if (e->pix_obj[y * e->sdl->scr_wid + x])
		e->selected = (e->pix_obj)[y * e->sdl->scr_wid + x];
	else
		e->selected = NULL;
	return (0);
}

int		on_rbutton_down(int x, int y, t_env *e)
{
	(void)x;
	(void)y;
	e->selected = NULL;
	return (0);
}
