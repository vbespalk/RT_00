/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_gui.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:17:16 by mdovhopo          #+#    #+#             */
/*   Updated: 2019/04/24 14:06:58 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_gui(t_env *e, uint32_t btn_id)
{
	SDL_Rect	background;
	SDL_Rect	gui_container;

	background = (SDL_Rect){
		e->sdl->scr_wid - GUI_WIDTH, GUI_HEIGHT, GUI_WIDTH,
		e->sdl->scr_hei - GUI_HEIGHT
	};
	gui_container = (SDL_Rect){
		e->sdl->scr_wid - GUI_WIDTH, 0, GUI_WIDTH, GUI_HEIGHT
	};
	if (background.h > 0)
	{
		SDL_SetRenderDrawColor(e->sdl->renderer, 49, 61, 66, 255);
		SDL_RenderFillRect(e->sdl->renderer, &background);
	}
	SDL_RenderCopy(e->sdl->renderer, e->sdl->gui->gui_texture,
	NULL, &gui_container);
	if (btn_id > BTN_ID_SHIFT)
	{
		SDL_SetRenderDrawColor(e->sdl->renderer, 255, 255, 255, 255);
		background = g_btn_containers[btn_id - BTN_ID_SHIFT - 1];
		background.x = e->sdl->scr_wid - background.x;
		SDL_RenderDrawRect(e->sdl->renderer, &background);
	}
}
