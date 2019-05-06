/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_gui_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 12:17:04 by mdovhopo          #+#    #+#             */
/*   Updated: 2019/05/06 17:38:13 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
	static const int32_t	s_buttons_codes[] = {
		SDLK_g, SDLK_i, SDLK_u, SDLK_h
	};
	const int				id_shift = 2;

	ft_switch_col_mode(e, s_buttons_codes[id - id_shift]);
}

void		translate(t_env *e, const uint32_t id)
{
	static const SDL_Keycode	s_buttons_codes[] = {
		SDLK_d, SDLK_a, SDLK_s, SDLK_w, SDLK_e, SDLK_q,
	};
	const int					id_shift = 9;

	if (e->selected)
		e->selected->ft_translate(s_buttons_codes[id - id_shift], e->selected,
				&(e->selected->transform), &(e->selected->inverse));
	else
		ft_translate_cam(s_buttons_codes[id - id_shift],
			&(e->scn->cam->origin));
}

void		rotate(t_env *e, const uint32_t id)
{
	static const SDL_Keycode	s_buttons_codes[] = {
		SDLK_PAGEUP, SDLK_PAGEDOWN,
		SDLK_RIGHT, SDLK_LEFT,
		SDLK_UP, SDLK_DOWN,
	};
	const int					id_shift = 15;

	if (e->selected)
		e->selected->ft_rotate(s_buttons_codes[id - id_shift],
			e->selected, &(e->selected->transform), &(e->selected->inverse));
	else
		ft_rotate_cam(s_buttons_codes[id - id_shift], &(e->scn->cam->angles));
}

void		texture_editing(t_env *e, uint32_t id)
{
	const int id_shift = 41;

	ft_set_exposure(id - id_shift + SDLK_0, e->selected, e);
}
