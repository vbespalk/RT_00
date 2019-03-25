/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 21:49:13 by vbespalk          #+#    #+#             */
/*   Updated: 2018/08/17 21:49:15 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	init_env(t_env *e, t_scene *scene, t_object **obj_pix, t_sdl *sdl)
{
	t_list		*textures;
	t_list		*objs;
	t_object	*obj;
	int 		i;

	e->scn = scene;
	e->asp_rat = (float)sdl->scr_wid / (float)sdl->scr_hei;
	e->pix_obj = obj_pix;
	e->sdl = sdl;
	textures = NULL;
	e->scn->textures = textures;
	objs = e->scn->objs;
//	while (objs)
//	{
//		obj = (t_object *)objs->content;
//		if (obj->texture_id != NULL)
//			obj->texture = init_texture(&textures, sdl, obj->texture_id);
//		objs = objs->next;
//	}
//	i = -1;
//	if (e->scn->skybox != NULL)
//		while (++i < BOX_FACES)
//			if (!(e->scn->skybox->textur[i] = init_texture(&textures, sdl,
//					e->scn->skybox->textur_id[i])))
//				return (-1);
	e->selected = NULL;
	return (0);
}

static void	ft_rt_loop(t_env *e)
{
	t_sdl	*sdl;

	sdl = e->sdl;
	sdl->event_loop = 1;
	ft_render(e);
	SDL_UpdateTexture(
		sdl->screen, NULL, sdl->pixels, sdl->scr_wid * sizeof(Uint32));
	SDL_RenderClear(sdl->renderer);
	SDL_RenderCopy(sdl->renderer, sdl->screen, NULL, NULL);
	SDL_RenderPresent(sdl->renderer);
	while (sdl->event_loop)
	{
		if (event_handler(e))
		{
			ft_render(e);
			SDL_UpdateTexture(
				sdl->screen, NULL, sdl->pixels, sdl->scr_wid * sizeof(Uint32));
			SDL_RenderClear(sdl->renderer);
			SDL_RenderCopy(sdl->renderer, sdl->screen, NULL, NULL);
			SDL_RenderPresent(sdl->renderer);
		}
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
	sdl.scr_wid = SCR_WID;
	sdl.scr_hei = SCR_HEI;
	if (sdl_init(&sdl) < 0)
		exit(-1);
//	SDL_UpdateTexture(
//		sdl.screen, NULL, sdl.pixels, sdl.scr_wid * sizeof(Uint32));
//	SDL_RenderClear(sdl.renderer);
//	SDL_RenderCopy(sdl.renderer, sdl.screen, NULL, NULL);
//	SDL_RenderPresent(sdl.renderer);
	if (!(scene = ft_parse_json(argv[1])))
		ft_error("Scene is incomplete or incorrect\n");
	obj_pix = (t_object **)ft_smemalloc(
		sizeof(t_object) * sdl.scr_wid * sdl.scr_hei, "main");
	if (init_env(&e, scene, &obj_pix[0], &sdl))
	{
		// struct_del(scene);
		exit(-1);
	}
	ft_rt_loop(&e);
//	printf("Works\n");
	sdl_close(&sdl);
	return (0);
}
