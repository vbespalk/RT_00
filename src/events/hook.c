/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 17:35:53 by vbespalk          #+#    #+#             */
/*   Updated: 2019/04/27 16:29:19 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_event.h"

int		on_key_down(SDL_Keycode sum, Uint16 mod, t_env *e)
{
	if (sum == SDLK_w || sum == SDLK_a \
		|| sum == SDLK_s || sum == SDLK_d \
		|| sum == SDLK_q || sum == SDLK_e)
	{
        return (e->selected ? e->selected->ft_translate(sum, e->selected, &(e->selected->transform), &(e->selected->inverse)) : \
	ft_translate_cam(sum, &(e->scn->cam->origin))); //<-----------------------------CAMERA TRANSLATION??????
	}
	if (sum == SDLK_UP || sum == SDLK_DOWN || \
		sum == SDLK_LEFT || sum == SDLK_RIGHT || \
		sum == SDLK_PAGEDOWN|| sum == SDLK_PAGEUP)
	{
        return (e->selected ? e->selected->ft_rotate(sum, e->selected, &(e->selected->transform), &(e->selected->inverse)) : \
	ft_rotate_cam(sum, &(e->scn->cam->angles)));
	}
	if (sum == SDLK_z || sum == SDLK_x)
	{
        return (e->selected ? e->selected->ft_scale(sum, e->selected, &(e->selected->transform), &(e->selected->inverse)) : \
	ft_scale_cam(sum, &(e->scn->cam->fov))); //<------------------SCALING!!! DO SMTH WITH THIS!!!!!!
	}
	if (e->selected && (sum == SDLK_r || sum == SDLK_t))
        return (e->selected->ft_scale_height(sum, e->selected, &(e->selected->transform), &(e->selected->inverse)));
	if (sum == SDLK_DELETE && e->selected)
	{
		delete_obj(&(e->scn->objs), e->selected->id);
		e->selected = NULL;
        return (1);
	}
	if (sum == SDLK_g || sum == SDLK_u || sum == SDLK_h || sum == SDLK_i)
        return (ft_switch_col_mode(e, sum));
	if (sum == SDLK_b)
        return (ft_switch_skybox(e->sdl, e->scn));
	if (e->selected && (sum >= SDLK_0 && sum <= SDLK_9))
        return (ft_set_exposure(sum, e->selected, e));
//	if (sum == SDLK_r)
//		reset(e);
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
	e->selected ? e->selected->ft_scale(sum, e->selected, &(e->selected->transform), &(e->selected->inverse)) : \
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
	if (x >= e->sdl->rt_wid || y >= e->sdl->scr_hei)
		return (0);
	if (e->pix_obj[y * e->sdl->scr_wid + x])
	{
		// printf("selected pix %d\n", x * y);
		e->selected = (e->pix_obj)[y * e->sdl->scr_wid + x];
		// printf("selected obj, id %d\n", e->selected->id);
	}
	else
	{
		// printf("unselected, cum\n");
		e->selected = NULL;
	}
	return (0);
	// printf("left but_down %d,%d\n", x, y);
}

int		on_rbutton_down(int x, int y, t_env *e)
{
	e->selected = NULL;
	return (0);
}

int		on_lbutton_up(int x, int y, t_env *e)
{
	// printf("left but_up %d,%d\n", x, y);
	return (0);
}

int		on_resize(Sint32 w, Sint32 h, t_env *e)
{
	e->sdl->scr_wid = w;
    e->sdl->rt_wid = e->sdl->scr_wid - GUI_WIDTH;
	e->sdl->scr_hei = h;
	ft_memdel((void **)&(e->sdl->format));
	get_format_data(e->sdl);
//	SDL_DestroyTexture(e->sdl->screen);
	cleanup(&e->sdl->screen);
	e->sdl->screen = SDL_CreateTexture(e->sdl->renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, e->sdl->scr_wid - GUI_WIDTH, e->sdl->scr_hei);
	if(e->sdl->screen == NULL)
	{
//		sdl_close(e->sdl);
		on_sdl_close("wr", &e->sdl->window, &e->sdl->renderer);
		sdl_error("Surface could not be created! ");
		// return (sdl_error("Surface could not be created! "));
	}
	ft_memdel((void **)&(e->sdl->pixels));
	if (!(e->sdl->pixels = (Uint32 *)malloc(sizeof(Uint32) * e->sdl->scr_hei * e->sdl->rt_wid)))
//		sdl_close(e->sdl);
	{
		on_sdl_close("wrt", &e->sdl->window, &e->sdl->renderer, &e->sdl->screen);
		exit (-1);
	}
	ft_memset(e->sdl->pixels, 0, e->sdl->scr_hei * e->sdl->rt_wid * sizeof(Uint32));
	ft_memdel((void **)&(e->pix_obj));
	e->pix_obj = (t_object **)ft_smemalloc(sizeof(t_object) * e->sdl->rt_wid * e->sdl->scr_hei, "on_resize");
	ft_memset(e->pix_obj, 0, e->sdl->scr_hei * e->sdl->rt_wid * sizeof(Uint32));
	return (1);
}

int		ft_on_exit(t_env *e)
{
	e->sdl->event_loop = 0; //on_quit(): destroy_all_data, exit;
//	sdl_close(e->sdl);
    system("leaks RT");
    on_sdl_close("wrttvv", &e->sdl->window, &e->sdl->renderer, &e->sdl->screen,
			&e->sdl->gui->gui_texture, &e->sdl->pixels, &e->sdl->format);
	// system("leaks RT");
	return (0);
}
