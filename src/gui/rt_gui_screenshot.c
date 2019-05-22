/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_gui_screenshot.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 13:48:37 by mdovhopo          #+#    #+#             */
/*   Updated: 2019/05/22 16:39:11 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <time.h>

static char		*join_3_cstrings(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*joined;

	tmp = ft_strjoin(s1, s2);
	joined = ft_strjoin(tmp, s3);
	ft_memdel((void**)&tmp);
	return (joined);
}

int				make_screenshot(t_env *e)
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
	name = join_3_cstrings(DEFAULT_SCRSHT_NAME, str_time, ".png");
	ft_printf("ScreenShot \"%s\" saved with code: %d\n",
			name, IMG_SavePNG(sshot, name));
	ft_memdel((void **)&name);
	SDL_FreeSurface(sshot);
	return (0);
}
