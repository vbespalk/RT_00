/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_cleanup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 18:07:58 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/08 18:08:00 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	cleanup_sdl_window(SDL_Window **win)
{
	if (*win)
		SDL_DestroyWindow(*win);
	*win = NULL;
}

void	cleanup_sdl_texture(SDL_Texture **tex)
{
	if (*tex)
		SDL_DestroyTexture(*tex);
	*tex = NULL;
}

void	cleanup_sdl_surface(SDL_Surface **surf)
{
	if (*surf)
		SDL_FreeSurface(*surf);
	*surf = NULL;
}

void	cleanup_sdl_render(SDL_Renderer **rend)
{
	if (*rend)
		SDL_DestroyRenderer(*rend);
	*rend = NULL;
}

void	on_sdl_close(char *fmt, ...)
{
	va_list	args_ptr;

	if (fmt == NULL)
		SDL_Quit();
	va_start(args_ptr, fmt);
	while (*fmt)
	{
		if (*fmt == 's')
			cleanup(va_arg(args_ptr, SDL_Surface **));
		else if (*fmt == 't')
			cleanup(va_arg(args_ptr, SDL_Texture **));
		else if (*fmt == 'r')
			cleanup(va_arg(args_ptr, SDL_Renderer **));
		else if (*fmt == 'w')
			cleanup(va_arg(args_ptr, SDL_Window **));
		else if (*fmt == 'v')
			ft_memdel(va_arg(args_ptr, void **));
		fmt++;
	}
	va_end(args_ptr);
	IMG_Quit();
	SDL_Quit();
}
