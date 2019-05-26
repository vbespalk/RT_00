/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 18:10:01 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/26 15:33:57 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		get_format_data(t_sdl *sdl)
{
	SDL_Surface	*surface;

	if (!(surface = SDL_CreateRGBSurface(0, sdl->rt_wid, sdl->scr_hei, 32,
			RMASK, GMASK, BMASK, AMASK)))
	{
		sdl_error(ON_ERR "get_format_data");
		exit(-1);
	}
	sdl->pitch = surface->pitch / sizeof(Uint32);
	sdl->format = (SDL_PixelFormat *)malloc(sizeof(SDL_PixelFormat));
	ft_memcpy(sdl->format, surface->format, sizeof(SDL_PixelFormat));
	SDL_FreeSurface(surface);
	return (0);
}

int		sdl_init(t_sdl *sdl, char *name)
{
	Uint32				flags[3];

	flags[0] = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
	flags[1] = SDL_RENDERER_ACCELERATED;
	flags[2] = IMG_INIT_JPG | IMG_INIT_PNG;
	sdl->scr_wid = SCR_WID;
	sdl->rt_wid = sdl->scr_wid - GUI_WIDTH;
	sdl->scr_hei = SCR_HEI;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
		return (sdl_error(ON_ERR "sdl_init"));
	if (!IMG_Init(flags[2]))
		return (sdl_img_error(ON_ERR "sdl_init"));
	if (!(sdl->window = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, SCR_WID, SCR_HEI, flags[0])))
		return (sdl_error(ON_ERR "sdl_init"));
	if (!(sdl->renderer = SDL_CreateRenderer(sdl->window, -1, flags[1])))
		return (sdl_error(ON_ERR "sdl_init"));
	if (!(sdl->screen = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_RGBA32,
			SDL_TEXTUREACCESS_STATIC, sdl->rt_wid, sdl->scr_hei)))
		return (sdl_error(ON_ERR "sdl_init"));
	get_format_data(sdl);
	sdl->pixels = (Uint32 *)ft_smemalloc(sizeof(Uint32) *
			sdl->scr_hei * sdl->rt_wid, "sdl_init");
	sdl->rt_cont = (SDL_Rect){0, 0, sdl->rt_wid, sdl->scr_hei};
	return (0);
}

int		sdl_error(char *message)
{
	if (message)
		ft_putendl(message);
	ft_putstr("SDL Error: ");
	ft_putendl(SDL_GetError());
	return (-1);
}

int		sdl_img_error(char *message)
{
	if (message)
		ft_putendl(message);
	ft_putstr("SDL_Image Error: ");
	ft_putendl(IMG_GetError());
	return (-1);
}
