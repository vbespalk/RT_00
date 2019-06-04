/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 17:19:29 by vbespalk          #+#    #+#             */
/*   Updated: 2018/08/21 16:11:31 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

Uint32			get_rgb(t_sdl *sdl, Uint8 red, Uint8 green, Uint8 blue)
{
	Uint32 col;

	col = SDL_MapRGB(sdl->format, red, green, blue);
	return (col);
}

void			img_pixel_put(t_sdl *sdl, int x, int y, unsigned int color)
{
	if (!(x >= 0 && x < sdl->rt_wid && y >= 0 && y < sdl->scr_hei))
		return ;
	sdl->pixels[y * sdl->pitch + x] = color;
}
