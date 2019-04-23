/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_gui.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:17:16 by mdovhopo          #+#    #+#             */
/*   Updated: 2019/04/23 16:56:39 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static const SDL_Rect g_btn_containers[] = (const SDL_Rect[]){

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
	(SDL_Rect){-1, -1, -1, -1} // terminating rect
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

void		ft_gui(t_env *e)
{
	const SDL_Rect	background = {
		e->sdl->scr_wid - GUI_WIDTH, GUI_HEIGHT, GUI_WIDTH, e->sdl->scr_hei - GUI_HEIGHT
	};
	const SDL_Rect	gui_container = {
		e->sdl->scr_wid - GUI_WIDTH, 0, GUI_WIDTH, GUI_HEIGHT
	};
	if (background.h > 0)
	{
		SDL_SetRenderDrawColor(e->sdl->renderer, 49, 61, 66, 255);
		SDL_RenderFillRect(e->sdl->renderer, &background);
	}
	SDL_RenderCopy(e->sdl->renderer, e->sdl->gui->gui_texture, NULL, &gui_container);
}

uint8_t		mouse_on_btn(const int32_t x, const int32_t y, t_env *e)
{
	uint8_t			i;
	const uint32_t	w = e->sdl->scr_wid;

	i = -1;
	while (++i < BUTTONS_AMOUNT)
	{
		if (x > w - g_btn_containers[i].x && x < w - g_btn_containers[i].x + g_btn_containers[i].w &&
			y > g_btn_containers[i].y && y < g_btn_containers[i].y + g_btn_containers[i].h)
			return (i + 1);
	}
	return (0);
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

void		object_mode_events_handle_2(t_env *e, const uint32_t id)
{
	if (id == T_BLUR_DOWN || id == T_BLUR_UP)
	{
		e->selected->t_blur += (id == T_BLUR_DOWN ? -0.1f : 0.1f);
		e->selected->t_blur = clamp(0, 1, e->selected->t_blur);
	}
	else if (id == R_BLUR_DOWN || id == R_BLUR_UP)
	{
		e->selected->s_blur += (id == R_BLUR_DOWN ? -0.1f : 0.1f);
		e->selected->s_blur = clamp(0, 1, e->selected->s_blur);
	}
	else if (id == TRANSP_DOWN || id == TRANSP_UP)
	{
		e->selected->trans += (id == TRANSP_DOWN ? -0.1f : 0.1f);
		e->selected->trans = clamp(0, 1, e->selected->trans);
	}
	else if (id == DIFFUSE_DOWN || id == DIFFUSE_UP)
	{
		e->selected->diff += (id == DIFFUSE_DOWN ? -0.1f : 0.1f);
		e->selected->diff = clamp(0, 1, e->selected->diff);
	}
	else if (id == AMBIENT_DOWN || id == AMBIENT_UP)
	{
		e->selected->ambnt += (id == AMBIENT_DOWN ? -0.1f : 0.1f);
		e->selected->ambnt = clamp(0, 1, e->selected->ambnt);
	}
}


void		object_mode_events_handle_1(t_env *e, const uint32_t id)
{
	if (id == RADIUS_DOWN || id == RADIUS_UP)
		{} // radius change
	else if (id == HEIGHT_DOWN || id == HEIGHT_UP)
		{} // height change
	else if (id == REFL_DOWN || id == REFL_UP)
		{} // reflection change
	else if (id == REFR_DOWN || id == REFR_UP)
	{
		e->selected->refr += (id == REFR_DOWN ? -0.1f : 0.1f);
		e->selected->refr = clamp(1, 2.4, e->selected->refr);
	}
	else
		object_mode_events_handle_2(e, id);
}

uint8_t		handle_button(t_env *e, const uint32_t id)
{
	printf("clicked btn with id %d\n", id); // remove this test stuff
	if (id ==  SAVE_IMG || id == CAMERA_MODE || id == SKYBOX || id == DELETE_OBJ)
		other_buttons(e, id);
	else if (id >= SAVE_IMG && id <= COLOR_FILTER_TMP_NAME)
		color_filter(e, id);
	else if (id == FOV_DOWN || id == FOV_UP)
		ft_scale_cam((id == FOV_DOWN ? SDLK_z : SDLK_x), &(e->scn->cam->fov));
	else if (id >= TRANS_OX_DOWN && id <= TRANS_OZ_UP)
		translate(e, id);
	else if (id >= ROT_OX_DOWN && id <= ROT_OZ_UP)
		rotate(e, id);
	else if (id > ROT_OZ_UP && id <= AMBIENT_UP && e->selected)
		object_mode_events_handle_1(e, id);
	return (1);
}
