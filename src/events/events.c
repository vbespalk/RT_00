/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 19:52:24 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/10 15:16:52 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_ev.h"

t_bool		check_if_holdable(const uint32_t btn_id)
{
	return ((btn_id >= SCREENSHOT && btn_id <= CAMERA_MODE) ||
			btn_id == SKYBOX ||
			(btn_id >= COLOR && btn_id <= TEX_6));
}

static int	event_handler_buttons(t_env *e, SDL_Event *event, uint32_t *btn_id,
		SDL_bool *mouse_pressed)
{
	static t_vector		v = {0, 0, 0, 0};

	if (*mouse_pressed || event->type == SDL_MOUSEBUTTONDOWN)
	{
		if (!*mouse_pressed)
			v = (t_vector){event->button.x, event->button.y, 0, 0};
		*mouse_pressed = SDL_TRUE;
		if ((*btn_id = mouse_on_btn((const int32_t)v[0],
									(const int32_t)v[1], e)))
		{
			*mouse_pressed = (check_if_holdable(*btn_id) ?
					SDL_FALSE : SDL_TRUE);
			return (handle_button(e, *btn_id));
		}
		if (event->button.button == SDL_BUTTON_LEFT)
			return (on_lbutton_down(event->button.x, event->button.y, e));
		if (event->button.button == SDL_BUTTON_RIGHT)
			return (on_rbutton_down(event->button.x, event->button.y, e));
	}
	else
		return (0);
	*btn_id = 0;
	return (0);
}

int			event_handler(t_env *e, uint32_t *btn_id)
{
	SDL_Event			event;
	static SDL_bool		mouse_pressed = SDL_FALSE;

	if (SDL_PollEvent(&event) || mouse_pressed)
	{
		if (event.type == SDL_MOUSEBUTTONUP)
			mouse_pressed = 0;
		if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN &&
			event.key.keysym.sym == SDLK_ESCAPE))
			return (ft_on_exit(e));
		else if (event.type == SDL_KEYDOWN)
			return (on_key_down(event.key.keysym.sym, e));
		else if (event.type == SDL_WINDOWEVENT &&
			event.window.event == SDL_WINDOWEVENT_RESIZED)
			return (on_resize(event.window.data1, event.window.data2, e));
		else if (event.type == SDL_MOUSEWHEEL && event.wheel.y)
			return (on_mouse_wheel(event.wheel.y, event.wheel.direction, e));
		else
			return (event_handler_buttons(e, &event, btn_id, &mouse_pressed));
	}
	*btn_id = 0;
	return (0);
}
