/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_gui.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:17:16 by mdovhopo          #+#    #+#             */
/*   Updated: 2019/05/06 17:29:32 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		button_pressed(t_env *e, int id)
{
	float		x_m;
	float		y_m;
	SDL_Rect	src;
	SDL_Rect	dst;

	dst = g_btn_containers[id - BTN_ID_SHIFT - 1];
	dst.x = e->sdl->scr_wid - dst.x;
	x_m = (float)(e->sdl->gui->w) / (float)GUI_WIDTH;
	y_m = (float)(e->sdl->gui->h) / ((float)GUI_HEIGHT);
	src = g_btn_containers[id - BTN_ID_SHIFT - 1];
	src.x = GUI_WIDTH - src.x;
	src.x *= x_m;
	src.y *= y_m;
	src.w *= x_m;
	src.h *= y_m;
	src.x += 3;
	src.y += 10;
	src.h -= 15;
	SDL_SetTextureColorMod(e->sdl->gui->gui_texture, 128, 128, 128);
	SDL_RenderCopy(e->sdl->renderer, e->sdl->gui->gui_texture, &src, &dst);
	SDL_SetTextureColorMod(e->sdl->gui->gui_texture, 255, 255, 255);
}

void		update_w_color_mode(t_env *e)
{
	t_sdl *sdl;

	sdl = e->sdl;
	SDL_UpdateTexture(
		sdl->screen, NULL, sdl->pixels, sdl->rt_wid * sizeof(Uint32));
	SDL_RenderCopy(sdl->renderer, sdl->screen, NULL, &(sdl->rt_cont));
}

void		ft_gui(t_env *e, uint32_t id)
{
	SDL_Rect	gui_container;
	SDL_Rect	tmp;
	float		k;

	tmp = (SDL_Rect){
		e->sdl->scr_wid - GUI_WIDTH, GUI_HEIGHT, GUI_WIDTH,
		e->sdl->scr_hei - GUI_HEIGHT
	};
	gui_container = (SDL_Rect){
		e->sdl->scr_wid - GUI_WIDTH, 0, GUI_WIDTH, GUI_HEIGHT
	};
	if (tmp.h > 0)
	{
		SDL_SetRenderDrawColor(e->sdl->renderer, 49, 61, 66, 255);
		SDL_RenderFillRect(e->sdl->renderer, &tmp);
	}
	SDL_RenderCopy(e->sdl->renderer, e->sdl->gui->gui_texture,
	NULL, &gui_container);
	if (id >= GRAYSCALE + BTN_ID_SHIFT && id <= INVERTED)
		update_w_color_mode(e);
	if (id > BTN_ID_SHIFT)
		button_pressed(e, id);
}
