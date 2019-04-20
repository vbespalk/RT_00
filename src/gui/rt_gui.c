/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_gui.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:17:16 by mdovhopo          #+#    #+#             */
/*   Updated: 2019/04/20 20:00:07 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

const SDL_Rect g_arrows_btns[] = (const SDL_Rect[]){
 	(SDL_Rect){180, 75, DEFAULT_BUTTTON_SIZE, DEFAULT_BUTTTON_SIZE},
	(SDL_Rect){125, 75, DEFAULT_BUTTTON_SIZE, DEFAULT_BUTTTON_SIZE},
	(SDL_Rect){180, 100, DEFAULT_BUTTTON_SIZE, DEFAULT_BUTTTON_SIZE},
	(SDL_Rect){125, 100, DEFAULT_BUTTTON_SIZE, DEFAULT_BUTTTON_SIZE},
	(SDL_Rect){180, 125, DEFAULT_BUTTTON_SIZE, DEFAULT_BUTTTON_SIZE},
	(SDL_Rect){125, 125, DEFAULT_BUTTTON_SIZE, DEFAULT_BUTTTON_SIZE},
	(SDL_Rect){90, 75, DEFAULT_BUTTTON_SIZE, DEFAULT_BUTTTON_SIZE},
	(SDL_Rect){35, 75, DEFAULT_BUTTTON_SIZE, DEFAULT_BUTTTON_SIZE},
	(SDL_Rect){90, 100, DEFAULT_BUTTTON_SIZE, DEFAULT_BUTTTON_SIZE},
	(SDL_Rect){35, 100, DEFAULT_BUTTTON_SIZE, DEFAULT_BUTTTON_SIZE},
	(SDL_Rect){90, 125, DEFAULT_BUTTTON_SIZE, DEFAULT_BUTTTON_SIZE},
	(SDL_Rect){35, 125, DEFAULT_BUTTTON_SIZE, DEFAULT_BUTTTON_SIZE},
	(SDL_Rect){90, 35, DEFAULT_BUTTTON_SIZE, DEFAULT_BUTTTON_SIZE},
	(SDL_Rect){35, 35, DEFAULT_BUTTTON_SIZE, DEFAULT_BUTTTON_SIZE},
	(SDL_Rect){65, 230, DEFAULT_BUTTTON_SIZE, LONG_BTN_HEIGHT},
	(SDL_Rect){35, 230, DEFAULT_BUTTTON_SIZE, LONG_BTN_HEIGHT},
	(SDL_Rect){65, 250, DEFAULT_BUTTTON_SIZE, LONG_BTN_HEIGHT},
	(SDL_Rect){35, 250, DEFAULT_BUTTTON_SIZE, LONG_BTN_HEIGHT},
	(SDL_Rect){65, 270, DEFAULT_BUTTTON_SIZE, LONG_BTN_HEIGHT},
	(SDL_Rect){35, 270, DEFAULT_BUTTTON_SIZE, LONG_BTN_HEIGHT},
	(SDL_Rect){65, 290, DEFAULT_BUTTTON_SIZE, LONG_BTN_HEIGHT},
	(SDL_Rect){35, 290, DEFAULT_BUTTTON_SIZE, LONG_BTN_HEIGHT},
	(SDL_Rect){65, 310, DEFAULT_BUTTTON_SIZE, LONG_BTN_HEIGHT},
	(SDL_Rect){35, 310, DEFAULT_BUTTTON_SIZE, LONG_BTN_HEIGHT},
	(SDL_Rect){65, 330, DEFAULT_BUTTTON_SIZE, LONG_BTN_HEIGHT},
	(SDL_Rect){35, 330, DEFAULT_BUTTTON_SIZE, LONG_BTN_HEIGHT},
	(SDL_Rect){65, 350, DEFAULT_BUTTTON_SIZE, LONG_BTN_HEIGHT},
	(SDL_Rect){35, 350, DEFAULT_BUTTTON_SIZE, LONG_BTN_HEIGHT},
	(SDL_Rect){65, 370, DEFAULT_BUTTTON_SIZE, LONG_BTN_HEIGHT},
	(SDL_Rect){35, 370, DEFAULT_BUTTTON_SIZE, LONG_BTN_HEIGHT},
};

const SDL_Rect g_buttons[] = (const SDL_Rect[]) {
 	(SDL_Rect){180, 5, 170, 25},
 	(SDL_Rect){180, 35, 80, 25},
 	(SDL_Rect){180, 155, 170, 25},
 	(SDL_Rect){180, 200, 170, 25}
};

const SDL_Rect g_text_boxes[] = (const SDL_Rect[]){
	(SDL_Rect){175, 60, 70, 15},
	(SDL_Rect){78, 60, 50, 15},
	(SDL_Rect){150, 77, AXIS_TEXT_SIZE, AXIS_TEXT_SIZE},
	(SDL_Rect){150, 103, AXIS_TEXT_SIZE, AXIS_TEXT_SIZE},
	(SDL_Rect){150, 127, AXIS_TEXT_SIZE, AXIS_TEXT_SIZE},
	(SDL_Rect){60, 77, AXIS_TEXT_SIZE, AXIS_TEXT_SIZE},
	(SDL_Rect){60, 103, AXIS_TEXT_SIZE, AXIS_TEXT_SIZE},
	(SDL_Rect){60, 127, AXIS_TEXT_SIZE, AXIS_TEXT_SIZE},
	(SDL_Rect){60, 37, AXIS_TEXT_SIZE + 3, AXIS_TEXT_SIZE},
	(SDL_Rect){140, 8, 90, 17},
 	(SDL_Rect){175, 40, 70, 17},
	(SDL_Rect){130, 158, 60, 17},
 	(SDL_Rect){140, 182, 85, 15},
 	(SDL_Rect){150, 203, 100, 17},
	(SDL_Rect){180, 230, 50, 15},
	(SDL_Rect){180, 250, 50, 15},
	(SDL_Rect){180, 270, 100, 15},
	(SDL_Rect){180, 290, 40, 15},
	(SDL_Rect){180, 310, 110, 15},
	(SDL_Rect){180, 330, 90, 15},
	(SDL_Rect){180, 350, 60, 15},
	(SDL_Rect){180, 370, 60, 15},
};

const char *g_msgs[] = (const char*[]){
	"TRANSLATE", "ROTATE",
	"OX", "OY", "OZ",
	"OX", "OY", "OZ",
	"FOV", "SAVE IMAGE",
	"CAM MODE", "SKYBOX",
	"OBJECT MODE",
	"DELETE OBJECT",
	"RADIUS", "HEIGHT",
	"REFLECTION", "BLUR",
	"TRANSPARENCY", "REFRACTION",
	"DIFFUSE", "AMBIENT"
};

int			ttf_init(t_sdl *sdl)
{
	SDL_Surface *tmp;
	int			i;

	if (TTF_Init() < 0)
		return (sdl_error("TTF could not init! "));
	sdl->gui = (t_gui*)malloc(sizeof(t_gui));
	sdl->gui->messages = (SDL_Texture**)malloc(sizeof(SDL_Texture*) * TEXT_MSGS_AMOUNT);
	sdl->gui->font = TTF_OpenFont("fonts/ARIAL.TTF", 36);
	if (!sdl->gui->font)
		return (-1);
	i = -1;
	while (++i < TEXT_MSGS_AMOUNT)
	{
		tmp = TTF_RenderText_Solid(sdl->gui->font, g_msgs[i], DEFAULT_TEXT_COLOR);
		sdl->gui->messages[i] = NEW_TTF_MSG(sdl->renderer, tmp);
	}
	// tmp = TTF_RenderText_Blended(sdl->gui->font, "Translations", WHITE_TEXT_COLOR);
	// 	sdl->gui->messages[i] = NEW_TTF_MSG(sdl->renderer, tmp);
	// tmp = TTF_RenderText_Blended(sdl->gui->font, "Rotations", WHITE_TEXT_COLOR);
	// 	sdl->gui->messages[i + 1] = NEW_TTF_MSG(sdl->renderer, tmp);
	return 1;
}

int			image_init(t_sdl *sdl)
{
	SDL_Surface *image;

	sdl->gui->imgs = (SDL_Texture**)malloc(sizeof(SDL_Texture*) * 2);
	TEST(image = SDL_LoadBMP("./media/left_arrow.bmp"))
	TEST(sdl->gui->imgs[0] = SDL_CreateTextureFromSurface(sdl->renderer, image))
	SDL_FreeSurface(image);
	TEST(image = SDL_LoadBMP("./media/right_arrow.bmp"))
	TEST(sdl->gui->imgs[1] = SDL_CreateTextureFromSurface(sdl->renderer, image))
	return 1;
}

void		ft_gui(t_env *e)
{
	int				i;
	int				img_id;
	SDL_Rect		tmp;
	const SDL_Rect	back = {e->sdl->scr_wid - GUI_WIDTH, 0, GUI_WIDTH, e->sdl->scr_hei};

	SDL_SetRenderDrawColor(e->sdl->renderer, 33, 39, 43, 255);
	SDL_RenderFillRect(e->sdl->renderer, &back);
	i = -1;
	SDL_SetRenderDrawColor(e->sdl->renderer, 64, 69, 78, 255);
	while (++i < BUTTONS_AMOUNT)
	{
		tmp = (SDL_Rect){e->sdl->scr_wid - g_buttons[i].x, g_buttons[i].y, 
			g_buttons[i].w, g_buttons[i].h};
		SDL_RenderFillRect(e->sdl->renderer, &(tmp));
	}
	i = -1;
	while (++i < ARROW_BTNS_AMOUNT)
	{
		tmp = (SDL_Rect){e->sdl->scr_wid - g_arrows_btns[i].x, g_arrows_btns[i].y,
				g_arrows_btns[i].w, g_arrows_btns[i].h};
		SDL_RenderCopy(e->sdl->renderer, e->sdl->gui->imgs[i % 2 == 0 ? 0 : 1], NULL, &tmp);
	}
	i = -1;
	while (++i < TEXT_MSGS_AMOUNT)
	{
		tmp = (SDL_Rect){e->sdl->scr_wid - g_text_boxes[i].x, g_text_boxes[i].y, 
			g_text_boxes[i].w, g_text_boxes[i].h};
		SDL_RenderCopy(e->sdl->renderer, (e->sdl->gui->messages)[i],
		NULL, &tmp);
	}
}

/*
** buttons events
*/

uint8_t		mouse_on_btn(const int32_t x, const int32_t y, t_env *e)
{
	uint8_t			id;
	uint8_t			i;
	const uint16_t	w = e->sdl->scr_wid;

	id = 0;
	i = -1;
	while (++i < ARROW_BTNS_AMOUNT)
	{
		if (x > w - g_arrows_btns[i].x && x < w - g_arrows_btns[i].x + g_arrows_btns[i].w &&
			y > g_arrows_btns[i].y && y < g_arrows_btns[i].y + g_arrows_btns[i].h)
			return (i + 1);
	}
	i = -1;
	while (++i < BUTTONS_AMOUNT)
	{
		if (x > w - g_buttons[i].x && x < w - g_buttons[i].x + g_buttons[i].w &&
			y > g_buttons[i].y && y < g_buttons[i].y + g_buttons[i].h)
			return (i + 1 + ARROW_BTNS_AMOUNT);
	}
	return (id);
}

uint8_t		handle_button(t_env *e, uint32_t btn_id, SDL_Keycode sum)
{
	static const SDL_Keycode s_buttons_codes[] = {
		SDLK_w, SDLK_s, SDLK_a, SDLK_d, SDLK_q, SDLK_e,
		SDLK_PAGEUP, SDLK_PAGEDOWN, SDLK_RIGHT, SDLK_LEFT,
		SDLK_UP, SDLK_DOWN, SDLK_z, SDLK_x
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
	else if (btn_id < 15)
		ft_scale_cam(s_buttons_codes[btn_id - 1], &(e->scn->cam->fov));
	else if (btn_id < 17)
	{
		// radius change
	}
	else if (btn_id < 19)
	{
		// height change
	}
	else if (btn_id < 21)
	{
		// reflection
	}
	else if (btn_id < 23)
	{
		// blur
	}
	else if (btn_id < 25)
	{
		// transparency
	}
	else if (btn_id < 27)
	{
		// refraction
	}
	else if (btn_id < 29)
	{
		// diffuse
	}
	else if (btn_id < 31)
	{
		// ambient
	}
	else if (btn_id == 31 && e->selected)
	{
		// TODO Save image
	}
	else if (btn_id == 32)
	{
		// CAM MODE BTN
	}
	else if (btn_id == 33)
	{
		// SKYBOX
	}
	else if (btn_id == 34 && e->selected)
	{
		delete_obj(&(e->scn->objs), e->selected->id);
		e->selected = NULL;
	}
	return (1);
}
