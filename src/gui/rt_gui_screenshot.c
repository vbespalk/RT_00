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

int		    make_screenshot(t_env *e)
{
	SDL_Surface			*sshot;
	static time_t		now = 0;
	char				*str_time;
	char				*name;
	char				*tmp;

	if (now == time(0))
		return (0);
	now = time(0);
	str_time = ctime(&now);
	str_time[ft_strlen(str_time) - 1] = '\0';
    if (!(sshot = SDL_CreateRGBSurfaceFrom(e->sdl->pixels, e->sdl->rt_wid,
            e->sdl->scr_hei, e->sdl->format->BitsPerPixel,
            e->sdl->pitch * sizeof(Uint32), RMASK, GMASK, BMASK, AMASK)))
    {
        sdl_img_error(ON_WARN "make_screenshot");
        return (0);
    }
	tmp = ft_strjoin(DEFAULT_SCRSHT_NAME, str_time);
	name = ft_strjoin(tmp, ".png");
	ft_memdel((void **)&tmp);
	ft_printf("ScreenShot \"%s\" saved with code: %d\n",
		name, IMG_SavePNG(sshot, name));
	ft_memdel((void **)&name);
	SDL_FreeSurface(sshot);
    return (0);
}
