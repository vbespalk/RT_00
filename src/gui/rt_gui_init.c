/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_gui_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 12:14:15 by mdovhopo          #+#    #+#             */
/*   Updated: 2019/04/30 13:44:36 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** boxes for all buttons
** all boxes listed in the same order as in e_btn_code enum.
*/

const SDL_Rect g_btn_containers[] = {

	(SDL_Rect){212, 51, DEFAULT_BUTTTON_WIDTH, DEFAULT_BUTTTON_HEIGHT},
	(SDL_Rect){212, 88, DEFAULT_BUTTTON_WIDTH, DEFAULT_BUTTTON_HEIGHT},
	(SDL_Rect){212, 109, DEFAULT_BUTTTON_WIDTH, DEFAULT_BUTTTON_HEIGHT},
	(SDL_Rect){103, 88, DEFAULT_BUTTTON_WIDTH, DEFAULT_BUTTTON_HEIGHT},
	(SDL_Rect){103, 109, DEFAULT_BUTTTON_WIDTH, DEFAULT_BUTTTON_HEIGHT},
	(SDL_Rect){212, 143, DEFAULT_BUTTTON_WIDTH, DEFAULT_BUTTTON_HEIGHT},
	(SDL_Rect){103, 143, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT},
	(SDL_Rect){39, 143, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT},
	(SDL_Rect){212, 179, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT},
	(SDL_Rect){148, 179, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT},
	(SDL_Rect){212, 197, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT},
	(SDL_Rect){148, 197, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT},
	(SDL_Rect){212, 216, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT},
	(SDL_Rect){148, 216, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT},
	(SDL_Rect){102, 179, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT},
	(SDL_Rect){39, 179, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT},
	(SDL_Rect){102, 197, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT},
	(SDL_Rect){39, 197, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT},
	(SDL_Rect){102, 216, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT},
	(SDL_Rect){39, 216, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT},
	(SDL_Rect){212, 239, DEFAULT_BUTTTON_WIDTH, DEFAULT_BUTTTON_HEIGHT},
	(SDL_Rect){212, 278, DEFAULT_BUTTTON_WIDTH, DEFAULT_BUTTTON_HEIGHT},
	(SDL_Rect){75, 298, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT},
	(SDL_Rect){38, 298, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT},
	(SDL_Rect){75, 317, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT},
	(SDL_Rect){38, 317, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT},
	(SDL_Rect){75, 342, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT},
	(SDL_Rect){38, 342, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT},
	(SDL_Rect){75, 360, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT},
	(SDL_Rect){38, 360, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT},
	(SDL_Rect){75, 380, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT},
	(SDL_Rect){38, 380, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT},
	(SDL_Rect){75, 398, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT},
	(SDL_Rect){38, 398, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT},
	(SDL_Rect){75, 415, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT},
	(SDL_Rect){38, 415, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT},
	(SDL_Rect){75, 434, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT},
	(SDL_Rect){38, 434, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT},
	(SDL_Rect){75, 451, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT},
	(SDL_Rect){38, 451, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT},
	(SDL_Rect){212, 493, TEXTURE_EDIT_BTN_W, TEXTURE_EDIT_BTN_H},
	(SDL_Rect){160, 493, TEXTURE_EDIT_BTN_W, TEXTURE_EDIT_BTN_H},
	(SDL_Rect){109, 493, TEXTURE_EDIT_BTN_W, TEXTURE_EDIT_BTN_H},
	(SDL_Rect){57, 493, TEXTURE_EDIT_BTN_W, TEXTURE_EDIT_BTN_H},
	(SDL_Rect){211, 516, 28, 18},
	(SDL_Rect){176, 516, 28, 18},
	(SDL_Rect){141, 516, 28, 18},
	(SDL_Rect){107, 516, 28, 18},
	(SDL_Rect){72, 516, 28, 18},
	(SDL_Rect){37, 516, 28, 18}
};

int			gui_init(t_sdl *sdl)
{
	SDL_Surface *image;

//	if (IMG_Init(IMG_INIT_PNG) < 0)
//		return (-1);
	MLC_TEST((sdl->gui = (t_gui*)malloc(sizeof(t_gui))), "gui alloc failed!");
	MLC_TEST((image = IMG_Load(DEFAULT_GUI_TEX_NAME)),
		"gui texture could not loaded");
	MLC_TEST(sdl->gui->gui_texture = SDL_CreateTextureFromSurface(
		sdl->renderer, image), "Texture could not created");
	SDL_FreeSurface(image);
	SDL_QueryTexture(sdl->gui->gui_texture, NULL, NULL,
		&(sdl->gui->w), &(sdl->gui->h));
	return (1);
}
