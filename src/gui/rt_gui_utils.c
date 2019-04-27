/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_gui_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 12:17:04 by mdovhopo          #+#    #+#             */
/*   Updated: 2019/04/27 14:29:39 by mdovhopo         ###   ########.fr       */
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
 	sshot = SDL_CreateRGBSurface(0, e->sdl->rt_wid, e->sdl->scr_hei, 32, RMASK, GMASK, BMASK, AMASK);
	tmp = ft_strjoin(DEFAULT_SCRSHT_NAME, str_time);
	name = ft_strjoin(tmp, ".png");
	free(tmp);
	SDL_RenderReadPixels(e->sdl->renderer, NULL, SDL_PIXELFORMAT_RGBA32, sshot->pixels, sshot->pitch);
	ft_printf("ScreenShot \"%s\" saved with code: %d\n", name, IMG_SavePNG(sshot, name));
	free(name);
	SDL_FreeSurface(sshot);
}

float		clamp(float lo, float hi, float v)
{
	return (fmax(lo, fmin(hi, v)));
}

void		other_buttons(t_env *e, const uint32_t id)
{
	if (id == CAMERA_MODE)
		e->selected = NULL;
	else if (id == DELETE_OBJ && e->selected)
	{
		delete_obj(&(e->scn->objs), e->selected->id);
		e->selected = NULL;
	}
	else if (id == SKYBOX && e->scn->skybox)
		ft_switch_skybox(e->sdl, e->scn);
	else if (id == SCREENSHOT)
		make_screenshot(e);
}

void		color_filter(t_env *e, const uint32_t id)
{
	static const int32_t s_buttons_codes[] = {
		SDLK_g, SDLK_i, SDLK_u, SDLK_h
	};
	ft_switch_col_mode(e, s_buttons_codes[id - 2]);
}

void		translate(t_env *e, const uint32_t id)
{
	static const SDL_Keycode s_buttons_codes[] = {
		SDLK_d, SDLK_a, SDLK_s, SDLK_w, SDLK_e, SDLK_q,
	};
	if (e->selected)
		e->selected->ft_translate(s_buttons_codes[id - 9], e->selected,
				&(e->selected->transform), &(e->selected->inverse));
	else
		ft_translate_cam(s_buttons_codes[id - 9], &(e->scn->cam->origin));
}

void		rotate(t_env *e, const uint32_t id)
{
	static const SDL_Keycode s_buttons_codes[] = {
		SDLK_PAGEUP, SDLK_PAGEDOWN,
		SDLK_RIGHT, SDLK_LEFT, 
		SDLK_UP, SDLK_DOWN,
	};
	if (e->selected)
		e->selected->ft_rotate(s_buttons_codes[id - 15],
			e->selected, &(e->selected->transform), &(e->selected->inverse));
	else
		ft_rotate_cam(s_buttons_codes[id - 15], &(e->scn->cam->angles));
}