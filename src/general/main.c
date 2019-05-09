/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 21:49:13 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/06 18:56:00 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	sdl_draw_screen(t_env *e, t_sdl *sdl, uint32_t btn_id,
	t_bool redraw)
{
	if (redraw)
	{
		printf("NEW RENDER\n");
		ft_render(e);
	}
	sdl->rt_cont = (SDL_Rect){0, 0, e->sdl->rt_wid, e->sdl->scr_hei};
	SDL_UpdateTexture(
		sdl->screen, NULL, sdl->pixels, sdl->rt_wid * sizeof(Uint32));
	SDL_RenderClear(sdl->renderer);
	SDL_RenderCopy(sdl->renderer, sdl->screen, NULL, &(sdl->rt_cont));
	ft_gui(e, btn_id);
	SDL_RenderPresent(sdl->renderer);
}

static void	ft_rt_loop(t_env *e)
{
	t_sdl		*sdl;
	uint32_t	btn_id;

	sdl = e->sdl;
	sdl->event_loop = 1;
	sdl_draw_screen(e, e->sdl, 0, true);
	while (sdl->event_loop)
	{
//		int x = SDL_GetTicks();
		if ((btn_id = event_handler(e)))
			sdl_draw_screen(e, e->sdl, btn_id,
				btn_id > (INVERTED + BTN_ID_SHIFT));
		if (!btn_id)
			sdl_draw_screen(e, e->sdl, 0, false);
//		int y = SDL_GetTicks() - x;
//		if (y != 0)
//			printf("%f\n", 1000 / (float)y);
	}
}

int			main(int argc, char **argv)
{
	t_scene		*scene;
	t_env		e;
	t_sdl		sdl;
	t_object	**obj_pix;

	if (argc != 2)
		ft_usage("RT scn\n");
	ft_bzero(&e, sizeof(t_env));
	ft_bzero(&sdl, sizeof(t_sdl));
	if (sdl_init(&sdl) < 0)
		exit(-1);
	if (gui_init(&sdl) < 0)
		exit(-1);
	if (!(scene = ft_parse_json(argv[1])))
		ft_error("Scene is incomplete or incorrect\n");
	obj_pix = (t_object **)ft_smemalloc(
		sizeof(t_object) * sdl.rt_wid * sdl.scr_hei, "main");
	init_env(&e, scene, &obj_pix[0], &sdl);
	ft_rt_loop(&e);
	return (0);
}
