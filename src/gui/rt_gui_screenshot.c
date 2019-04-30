/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_gui_screenshot.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 13:48:37 by mdovhopo          #+#    #+#             */
/*   Updated: 2019/04/30 13:57:45 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <time.h>

void		make_screenshot(t_env *e)
{
	SDL_Surface			*sshot;
	static time_t		now = 0;
	char				*str_time;
	char				*name;
	char				*tmp;

	if (now == time(0))
		return ;
	now = time(0);
	str_time = ctime(&now);
	str_time[ft_strlen(str_time) - 1] = '\0';
	sshot = SDL_CreateRGBSurface(0, e->sdl->rt_wid, e->sdl->scr_hei, 32,
		RMASK, GMASK, BMASK, AMASK);
	tmp = ft_strjoin(DEFAULT_SCRSHT_NAME, str_time);
	name = ft_strjoin(tmp, ".png");
	free(tmp);
	SDL_RenderReadPixels(e->sdl->renderer, NULL, SDL_PIXELFORMAT_RGBA32,
		sshot->pixels, sshot->pitch);
	ft_printf("ScreenShot \"%s\" saved with code: %d\n",
		name, IMG_SavePNG(sshot, name));
	free(name);
	SDL_FreeSurface(sshot);
}
