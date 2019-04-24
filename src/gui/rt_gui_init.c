/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_gui_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 12:14:15 by mdovhopo          #+#    #+#             */
/*   Updated: 2019/04/24 12:14:54 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** boxes for all buttons
*/

const SDL_Rect g_btn_containers[] = (const SDL_Rect[]){

	(SDL_Rect){212, 51, DEFAULT_BUTTTON_WIDTH, DEFAULT_BUTTTON_HEIGHT}, // save 
	// colors
	(SDL_Rect){212, 88, DEFAULT_BUTTTON_WIDTH, DEFAULT_BUTTTON_HEIGHT}, // grayscale 
	(SDL_Rect){212, 109, DEFAULT_BUTTTON_WIDTH, DEFAULT_BUTTTON_HEIGHT}, // inverted
	(SDL_Rect){103, 88, DEFAULT_BUTTTON_WIDTH, DEFAULT_BUTTTON_HEIGHT}, // sepia
	(SDL_Rect){103, 109, DEFAULT_BUTTTON_WIDTH, DEFAULT_BUTTTON_HEIGHT}, // ...
	// cam
	(SDL_Rect){212, 143, DEFAULT_BUTTTON_WIDTH, DEFAULT_BUTTTON_HEIGHT}, // cam mode
	(SDL_Rect){103, 143, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // fov - 
	(SDL_Rect){39, 143, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // fov +
	// translation
	(SDL_Rect){212, 179, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // ox -
	(SDL_Rect){148, 179, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // ox +
	(SDL_Rect){212, 197, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // oy +
	(SDL_Rect){148, 197, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // oy +
	(SDL_Rect){212, 216, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // oz +
	(SDL_Rect){148, 216, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // oz +
	// rotation
	(SDL_Rect){102, 179, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // ox -
	(SDL_Rect){39, 179, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // ox +
	(SDL_Rect){102, 197, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // oy +
	(SDL_Rect){39, 197, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // oy +
	(SDL_Rect){102, 216, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // oz +
	(SDL_Rect){39, 216, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // oz +
	// skybox
	(SDL_Rect){212, 239, DEFAULT_BUTTTON_WIDTH, DEFAULT_BUTTTON_HEIGHT},
	// obj mode 
	(SDL_Rect){212, 278, DEFAULT_BUTTTON_WIDTH, DEFAULT_BUTTTON_HEIGHT}, // delete
	(SDL_Rect){75, 298, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // radius -
	(SDL_Rect){38, 298, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // radius +
	(SDL_Rect){75, 317, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // height -
	(SDL_Rect){38, 317, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // height +
	(SDL_Rect){75, 342, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // reflection -
	(SDL_Rect){38, 342, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // reflection +
	(SDL_Rect){75, 360, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // refl blur -
	(SDL_Rect){38, 360, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // refl blur +
	(SDL_Rect){75, 380, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // transp -
	(SDL_Rect){38, 380, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // transp +
	(SDL_Rect){75, 398, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // transp blur -
	(SDL_Rect){38, 398, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // transp blur +
	(SDL_Rect){75, 415, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // refract -
	(SDL_Rect){38, 415, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // refract +
	(SDL_Rect){75, 434, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // diffuse -
	(SDL_Rect){38, 434, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // diffuse +
	(SDL_Rect){75, 451, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // ambient -
	(SDL_Rect){38, 451, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // ambient +
	// TODO Texturing
};

int			gui_init(t_sdl *sdl)
{
	SDL_Surface *image;

	if (IMG_Init(IMG_INIT_PNG) < 0)
		return -1;
	MLC_TEST((sdl->gui = (t_gui*)malloc(sizeof(t_gui))), "gui alloc failed!");
	MLC_TEST((image = IMG_Load("./media/gui_texture.png")),
	"gui texture could not loaded");
	MLC_TEST((sdl->gui->gui_texture =
	SDL_CreateTextureFromSurface(sdl->renderer, image)), "Texture could not created")
	SDL_FreeSurface(image);
	return 1;
}