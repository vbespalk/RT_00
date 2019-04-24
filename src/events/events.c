/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 19:52:24 by vbespalk          #+#    #+#             */
/*   Updated: 2019/04/24 15:20:35 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_event.h"

int		event_handler(t_env *e)
{
	SDL_Event			event;
	static SDL_bool		mouse_pressed = SDL_FALSE;
	static t_vector		v = {0, 0, 0, 0};
	uint32_t			btn_id;

	if (SDL_PollEvent(&event) || mouse_pressed)
	{
		if (event.type == SDL_MOUSEBUTTONUP)
			mouse_pressed = 0;
		//User requests quit
		if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
			return (ft_on_exit(e));
		else if (event.type == SDL_KEYDOWN)
			return (on_key_down(event.key.keysym.sym, event.key.keysym.mod, e));
		else if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED)
			return (on_resize(event.window.data1, event.window.data2, e));
		// else if (event.type == SDL_KEYUP)
		// 	on_key_up(event.key.keysym.sym, event.key.keysym.mod, e);
		// else if (event.type == SDL_MOUSEMOTION)
		// 	on_mouse_move(event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel, e, \
		// 		event.motion.state == SDL_BUTTON_LMASK, event.motion.state == SDL_BUTTON_RMASK, \
		// 		event.motion.state == SDL_BUTTON_MMASK);
		else if (mouse_pressed || event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (!mouse_pressed)
				v = (t_vector){event.button.x, event.button.y, 0, 0};
			mouse_pressed = SDL_TRUE;
			if ((btn_id = mouse_on_btn((const int32_t)v[0], (const int32_t)v[1], e)))
				return (handle_button(e, btn_id) + BTN_ID_SHIFT);
			if (event.button.button == SDL_BUTTON_LEFT)
				return (on_lbutton_down(event.button.x, event.button.y, e));
			if (event.button.button == SDL_BUTTON_RIGHT)
				return (on_rbutton_down(event.button.x, event.button.y, e));
		}
		else if (event.type == SDL_MOUSEWHEEL && event.wheel.y)
			return (on_mouse_wheel(event.wheel.y, event.wheel.direction, e));
		// else if (event.type == SDL_MOUSEBUTTONUP)
		// {
		// 	if (event.button.button == SDL_BUTTON_LEFT)
		// 		on_lbutton_up(event.button.x, event.button.y, e);
		// }
		else
			return (0);
	}
	return (0);
}


// int		event_handler(t_sdl *sdl)
// {
// 	SDL_Event	event;

// 	while (SDL_PollEvent(&event) != 0)
// 	{
// 		//User requests quit
// 		if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
// 			sdl->event_loop = 0;
// 	}
// 	return (0);
// }
