/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 17:35:53 by vbespalk          #+#    #+#             */
/*   Updated: 2019/04/20 15:26:31 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_event.h"

int		on_key_down(SDL_Keycode sum, Uint16 mod, t_env *e)
{
	if (sum == SDLK_w || sum == SDLK_a \
		|| sum == SDLK_s || sum == SDLK_d \
		|| sum == SDLK_q || sum == SDLK_e)
	{
		e->selected ? e->selected->ft_translate(sum, e->selected->fig, &e->selected->translate) : \
	ft_translate_cam(sum, &(e->scn->cam->origin)); //<-----------------------------CAMERA TRANSLATION??????
	}
	if (sum == SDLK_UP || sum == SDLK_DOWN || \
		sum == SDLK_LEFT || sum == SDLK_RIGHT || \
		sum == SDLK_PAGEDOWN|| sum == SDLK_PAGEUP)
	{
		e->selected ? e->selected->ft_rotate(sum, e->selected->fig, &e->selected->rotate) : \
	ft_rotate_cam(sum, &(e->scn->cam->angles));
	}
	if (sum == SDLK_z || sum == SDLK_x)
	{
		e->selected ? e->selected->ft_scale(sum, e->selected->fig, &e->selected->scale) : \
	ft_scale_cam(sum, &(e->scn->cam->fov)); //<------------------SCALING!!! DO SMTH WITH THIS!!!!!!
	}
	if (sum == SDLK_DELETE && e->selected)
	{
		delete_obj(&(e->scn->objs), e->selected->id);
		e->selected = NULL;
	}
	if (sum == SDLK_r)
		reset(e);
	if (sum == SDLK_c)
	{
		e->selected = NULL;
		return (0);
	}
	return (1);
}

int		on_mouse_wheel(Sint32 y, Uint32 dir, t_env *e)
{
	Uint32	sum;

	if (dir == SDL_MOUSEWHEEL_NORMAL)
		sum = (y > 0) ? SDLK_z : SDLK_x;
	else
		sum = (y < 0) ? SDLK_z : SDLK_x;
	e->selected ? e->selected->ft_scale(sum, e->selected->fig, &e->selected->scale) : \
	ft_scale_cam(sum, &(e->scn->cam->fov)); //<------------------SCALING!!! DO SMTH WITH THIS!!!!!!
	return (1);
}

int		on_key_up(SDL_Keycode sum, Uint16 mod, t_env *e)
{
	printf("key_up\n");
	return (0);
}

//static void	ft_highlight_object(int x, int y, t_env *e)
//{
//	t_object	*o;
//
//	o = e->pix_obj[y * e->sdl->scr_wid + x];
//	if (o == e->pointed)
//		return ;
//
//	e->pointed = o;
//}

int		on_mouse_move(int x, int y, int rel_x, int rel_y, t_env *e, int left, int right, int middle)
{
	printf("mouse_move pos:%d,%d, rel %d,%d left %i, right %i, middle %i\n", x, y, rel_x, rel_y, left, right, middle);
	return (0);
}

int		on_lbutton_down(int x, int y, t_env *e)
{
	if (e->pix_obj[y * e->sdl->scr_wid + x])
	{
		printf("selected pix %d\n", x * y);
		e->selected = (e->pix_obj)[y * e->sdl->scr_wid + x];
		printf("selected obj, id %d\n", e->selected->id);
	}
	else
	{
		printf("unselected, cum\n");
		e->selected = NULL;
	}
	return (0);
	// printf("left but_down %d,%d\n", x, y);
}

int		on_rbutton_down(int x, int y, t_env *e)
{
	e->selected = NULL;
	return (0);
	// printf("right but_down %d,%d\n", x, y);
}

int		on_lbutton_up(int x, int y, t_env *e)
{
	// printf("left but_up %d,%d\n", x, y);
	return (0);
}

int		on_resize(Sint32 w, Sint32 h, t_env *e)
{
	e->sdl->scr_wid = w;
	e->sdl->scr_hei = h;
	ft_memdel((void **)&(e->sdl->format));
	get_format_data(e->sdl);
	SDL_DestroyTexture(e->sdl->screen);
	//Init texture
	e->sdl->screen = SDL_CreateTexture(e->sdl->renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, e->sdl->scr_wid, e->sdl->scr_hei);
	if(e->sdl->screen == NULL)
	{
		sdl_close(e->sdl);
		sdl_error("Surface could not be created! ");
		// return (sdl_error("Surface could not be created! "));
	}
	ft_memdel((void **)&(e->sdl->pixels));
	if (!(e->sdl->pixels = (Uint32 *)malloc(sizeof(Uint32) * e->sdl->scr_hei * e->sdl->scr_wid)))
		sdl_close(e->sdl);
	ft_memset(e->sdl->pixels, 0, e->sdl->scr_hei * e->sdl->scr_wid * sizeof(Uint32));
	ft_memdel((void **)&(e->pix_obj));
	e->pix_obj = (t_object **)malloc(sizeof(t_object) * e->sdl->scr_wid * e->sdl->scr_hei);
	ft_memset(e->pix_obj, 0, e->sdl->scr_hei * e->sdl->scr_wid * sizeof(Uint32));
	return (1);
}

int		ft_on_exit(t_env *e)
{
	e->sdl->event_loop = 0; //on_quit(): destroy_all_data, exit;
	sdl_close(e->sdl);
	// system("leaks RT");
	return (0);
}
