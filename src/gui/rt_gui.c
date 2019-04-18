/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_gui.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:17:16 by mdovhopo          #+#    #+#             */
/*   Updated: 2019/04/18 16:33:47 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

const SDL_Rect g_buttons[] = (const SDL_Rect[]){
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
		(SDL_Rect){80, 110, DEFAULT_BUTTTON_SIZE, DEFAULT_BUTTTON_SIZE},
		(SDL_Rect){10, 190, DELETE_BUTTON_WIDTH, DELETE_BUTTON_HEIGHT}
};

static const SDL_Rect g_text_boxes[] = (const SDL_Rect[]){
	(SDL_Rect){7, 0, 100, 20},
	(SDL_Rect){7, 85, 85, 20}
};

static const char *g_msgs[] = (const char*[]){
	"UP", "LEFT", "DOWN", "RIGHT",
	" + ", " - ", "OX", "OY", "OX",
	"OY", "OZ", "OZ", "DELETE"
};

int			ttf_init(t_sdl *sdl)
{
	SDL_Surface *tmp;
	int			i;

	if (TTF_Init() < 0)
		return (sdl_error("TTF could not init! "));
	sdl->ttf = (t_ttf*)malloc(sizeof(t_ttf));
	sdl->ttf->messages = (SDL_Texture**)malloc(sizeof(SDL_Texture*) * BTN_TEXT_AMOUNT);
	sdl->ttf->rects = (SDL_Rect*)malloc(sizeof(SDL_Rect) * BTN_TEXT_AMOUNT);
	sdl->ttf->font = TTF_OpenFont("fonts/ARIAL.TTF", 24);
	if (!sdl->ttf->font)
		return (-1);
	i = -1;
	while (++i < BTN_TEXT_AMOUNT)
	{
		tmp = TTF_RenderText_Blended(sdl->ttf->font, g_msgs[i], BLACK_TEXT_COLOR);
		sdl->ttf->messages[i] = NEW_TTF_MSG(sdl->renderer, tmp);
	}
	tmp = TTF_RenderText_Blended(sdl->ttf->font, "Translations", WHITE_TEXT_COLOR);
		sdl->ttf->messages[i] = NEW_TTF_MSG(sdl->renderer, tmp);
	tmp = TTF_RenderText_Blended(sdl->ttf->font, "Rotations", WHITE_TEXT_COLOR);
		sdl->ttf->messages[i + 1] = NEW_TTF_MSG(sdl->renderer, tmp);
	return 1;
}

void		ft_gui(t_env *e)
{
	int i;

	SDL_SetRenderDrawColor(e->sdl->renderer, 200, 245, 218, 255);
	SDL_RenderFillRects(e->sdl->renderer, g_buttons, 6);
	SDL_SetRenderDrawColor(e->sdl->renderer, 143, 68, 218, 173);
	SDL_RenderFillRects(e->sdl->renderer, &(g_buttons[6]), 6);
	SDL_SetRenderDrawColor(e->sdl->renderer, 231, 76, 60, 255);
	SDL_RenderFillRect(e->sdl->renderer, &(g_buttons[12]));
	i = -1;
	while (++i < BTN_TEXT_AMOUNT)
		SDL_RenderCopy(e->sdl->renderer, (e->sdl->ttf->messages)[i],
		NULL, &(g_buttons[i]));
	SDL_RenderCopy(e->sdl->renderer, (e->sdl->ttf->messages)[BTN_TEXT_AMOUNT],
		NULL, &(g_text_boxes[0]));
	SDL_RenderCopy(e->sdl->renderer, (e->sdl->ttf->messages)[BTN_TEXT_AMOUNT + 1],
		NULL, &(g_text_boxes[1]));
}

/*
** buttons events
*/

uint8_t		mouse_on_btn(const int32_t x, const int32_t y, t_env *e)
{
	uint8_t id;
	uint8_t i;

	id = 0;
	i = 0;
	while (i < BUTTONS_AMOUNT)
	{
		if (x > g_buttons[i].x && x < g_buttons[i].x + g_buttons[i].w &&
			y > g_buttons[i].y && y < g_buttons[i].y + g_buttons[i].h)
			return (i + 1);
		i++;
	}
	return (id);
}

uint8_t		handle_button(t_env *e, uint32_t btn_id, SDL_Keycode sum)
{
	static const SDL_Keycode s_buttons_codes[] = {
		SDLK_w, SDLK_a, SDLK_s, SDLK_d, SDLK_q, SDLK_e,
		SDLK_PAGEDOWN, SDLK_LEFT, SDLK_PAGEUP, SDLK_RIGHT, SDLK_UP, SDLK_DOWN,
	};

	printf("clicked btn with id %d\n", btn_id); // remove this test stuff
	if (btn_id < 7)
		e->selected ?
		e->selected->ft_translate(s_buttons_codes[btn_id - 1], e->selected->fig,
		&e->selected->translate) :
		ft_translate_cam(s_buttons_codes[btn_id - 1], &(e->scn->cam->origin));
	else if (btn_id < 13)
		e->selected ?
		e->selected->ft_rotate(s_buttons_codes[btn_id - 1],
		e->selected->fig, &e->selected->rotate) :
		ft_rotate_cam(s_buttons_codes[btn_id - 1], &(e->scn->cam->angles));
	else if (btn_id == 13 && e->selected)
	{
		delete_obj(&(e->scn->objs), e->selected->id);
		e->selected = NULL;
	}
	return (1);
}
