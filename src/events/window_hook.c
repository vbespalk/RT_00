/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 19:19:19 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/17 19:19:21 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_ev.h"

int		on_resize(Sint32 w, Sint32 h, t_env *e)
{
	if (w < GUI_WIDTH)
		return (0);
	e->sdl->scr_wid = w;
	e->sdl->rt_wid = e->sdl->scr_wid - GUI_WIDTH;
	e->sdl->scr_hei = h;
	e->sdl->rt_cont = (SDL_Rect){0, 0, e->sdl->rt_wid, e->sdl->scr_hei};
	get_format_data(e->sdl);
	cleanup_sdl_texture(&e->sdl->screen);
	e->sdl->screen = SDL_CreateTexture(e->sdl->renderer, SDL_PIXELFORMAT_RGBA32,
		SDL_TEXTUREACCESS_STATIC, e->sdl->scr_wid - GUI_WIDTH, e->sdl->scr_hei);
	if (e->sdl->screen == NULL)
	{
		on_sdl_close("wr", &e->sdl->window, &e->sdl->renderer);
		sdl_error("Surface could not be created! ");
		exit(-1);
	}
	ft_memdel((void **)&(e->sdl->pixels));
	e->sdl->pixels = (Uint32 *)ft_smemalloc(sizeof(Uint32) * e->sdl->scr_hei *
		e->sdl->rt_wid, "on_resize");
	ft_memdel((void **)&(e->pix_obj));
	e->pix_obj = (t_object **)ft_smemalloc(sizeof(t_object) * e->sdl->rt_wid *
		e->sdl->scr_hei, "on_resize");
	return (1);
}

/*
** on_quit(): destroy_all_data, exit;
*/

int		ft_on_exit(t_env *e)
{
	e->sdl->event_loop = 0;
	on_sdl_close("wrtt", &e->sdl->window, &e->sdl->renderer, &e->sdl->screen,
		&e->sdl->gui->gui_texture);
	system("leaks RT");
	return (0);
}
