/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 21:49:13 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/26 15:34:11 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static uint32_t	sdl_draw_screen(t_env *e, t_sdl *sdl, uint32_t btn_id,
	uint32_t status)
{
	static uint32_t btn_pressed = 0;

	btn_pressed = btn_id > 0 ? 1 : 0;
	if (status == 1)
		ft_render(e);
	SDL_UpdateTexture(
		sdl->screen, NULL, sdl->pixels, sdl->rt_wid * sizeof(Uint32));
	SDL_RenderClear(sdl->renderer);
	SDL_RenderCopy(sdl->renderer, sdl->screen, NULL, &(sdl->rt_cont));
	ft_gui(e, btn_id);
	SDL_RenderPresent(sdl->renderer);
	return (btn_pressed);
}

static void		ft_rt_loop(t_env *e)
{
	t_sdl		*sdl;
	uint32_t	btn_id;
	uint32_t	status;
	int32_t		btn_status;

	sdl = e->sdl;
	sdl->event_loop = 1;
	sdl_draw_screen(e, e->sdl, 0, 1);
	btn_status = -1;
	while (sdl->event_loop)
	{
		status = event_handler(e, &btn_id);
		if (status)
			btn_status = sdl_draw_screen(e, e->sdl, btn_id, status);
		else
			sdl_draw_screen(e, e->sdl, 0, status);
		if (btn_status != -1 && btn_id == 0)
		{
			sdl_draw_screen(e, e->sdl, 0, 2);
			btn_status = -1;
		}
	}
}

int				main(int argc, char **argv)
{
	t_scene		*scene;
	t_env		e;
	t_sdl		sdl;
	t_object	**obj_pix;
	char		*window_name;

	if (argc != 2)
		ft_usage("RT scn\n");
	if (!(scene = ft_parse_json(argv[1])))
		ft_error("Scene is incomplete or incorrect\n");
	window_name = ft_strjoin("RayTracer - ", scene->name);
	ft_bzero(&e, sizeof(t_env));
	ft_bzero(&sdl, sizeof(t_sdl));
	if (sdl_init(&sdl, window_name) < 0)
		exit(-1);
	free(window_name);
	if (gui_init(&sdl) < 0)
		exit(-1);
	obj_pix = (t_object **)ft_smemalloc(
		sizeof(t_object) * sdl.rt_wid * sdl.scr_hei, "main");
	init_env(&e, scene, &obj_pix[0], &sdl);
	ft_rt_loop(&e);
	return (0);
}
