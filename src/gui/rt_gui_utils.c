/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_gui_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 12:17:04 by mdovhopo          #+#    #+#             */
/*   Updated: 2019/04/24 12:17:22 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
}

void		color_filter(t_env *e, const uint32_t id)
{
	printf("color filter\n");
}

void		translate(t_env *e, const uint32_t id)
{
	static const SDL_Keycode s_buttons_codes[] = {
		SDLK_d, SDLK_a, SDLK_s, SDLK_w, SDLK_e, SDLK_q,
	};
	if (e->selected)
		e->selected->ft_translate(s_buttons_codes[id - 9], e->selected->fig,
			&e->selected->translate);
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
			e->selected->fig, &e->selected->rotate);
	else
		ft_rotate_cam(s_buttons_codes[id - 15], &(e->scn->cam->angles));
}