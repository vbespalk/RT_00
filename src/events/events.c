/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 19:52:24 by vbespalk          #+#    #+#             */
/*   Updated: 2019/04/17 19:13:02 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_event.h"

const SDL_Rect buttons[] = { // need to add this to env struct
	(SDL_Rect){45, 20, DEFAULT_BUTTTON_SIZE, DEFAULT_BUTTTON_SIZE},
	(SDL_Rect){10, 55, DEFAULT_BUTTTON_SIZE, DEFAULT_BUTTTON_SIZE},
	(SDL_Rect){45, 55, DEFAULT_BUTTTON_SIZE, DEFAULT_BUTTTON_SIZE},
	(SDL_Rect){80, 55, DEFAULT_BUTTTON_SIZE, DEFAULT_BUTTTON_SIZE},
	(SDL_Rect){10, 20, DEFAULT_BUTTTON_SIZE, DEFAULT_BUTTTON_SIZE},
	(SDL_Rect){80, 20, DEFAULT_BUTTTON_SIZE, DEFAULT_BUTTTON_SIZE},
	(SDL_Rect){45, 110, DEFAULT_BUTTTON_SIZE, DEFAULT_BUTTTON_SIZE},
	(SDL_Rect){10, 145, DEFAULT_BUTTTON_SIZE, DEFAULT_BUTTTON_SIZE},
	(SDL_Rect){45, 145, DEFAULT_BUTTTON_SIZE, DEFAULT_BUTTTON_SIZE},
	(SDL_Rect){80, 145, DEFAULT_BUTTTON_SIZE, DEFAULT_BUTTTON_SIZE},
	(SDL_Rect){10, 110, DEFAULT_BUTTTON_SIZE, DEFAULT_BUTTTON_SIZE},
	(SDL_Rect){80, 110, DEFAULT_BUTTTON_SIZE, DEFAULT_BUTTTON_SIZE}
};

uint8_t	mouse_on_btn(const int32_t x, const int32_t y, t_env *e)
{
	// read buttons from e struct
	uint8_t id;
	uint8_t i;

	id = 0;
	i = 0;
	while (i < 12)
	{
		if (x > buttons[i].x && x < buttons[i].x + buttons[i].w &&
			y > buttons[i].y && y < buttons[i].y + buttons[i].h)
			return i + 1;
		i++;
	}
	return (id);
}

int		handle_button(const int32_t x, const int32_t y, t_env *e, uint32_t btn_id, SDL_Keycode sum)
{
	const SDL_Keycode buttons_codes[] = {
		SDLK_w, SDLK_a, SDLK_s, SDLK_d, SDLK_q, SDLK_e,
		SDLK_PAGEDOWN, SDLK_LEFT, SDLK_PAGEUP, SDLK_RIGHT, SDLK_UP, SDLK_DOWN,
	};
	// tmp id table:
	// 1 - w
	// 2 - a
	// 3 - s
	// 4 - d 
	// 5 - q
	// 6 - e
	printf("clicked btn with id %d\n", btn_id);
	// TODO create functions pointers array
	if (btn_id < 7)
		e->selected ? e->selected->ft_translate(buttons_codes[btn_id - 1], e->selected->fig, &e->selected->translate) : ft_translate_cam(buttons_codes[btn_id - 1], &(e->scn->cam->origin));
	else if (btn_id < 13)
		e->selected ? e->selected->ft_rotate(buttons_codes[btn_id - 1], e->selected->fig, &e->selected->rotate) : ft_rotate_cam(buttons_codes[btn_id - 1], &(e->scn->cam->angles));
	return (1);
}

int		event_handler(t_env *e)
{
	SDL_Event		event;
	uint32_t		btn_id;

	if (SDL_WaitEvent(&event))
	{
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
		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if ((btn_id = mouse_on_btn(event.button.x, event.button.y, e)))
				return (handle_button(event.button.x, event.button.y, e, btn_id, event.key.keysym.sym));
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
	return (1);
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
