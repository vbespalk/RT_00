/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 21:49:13 by vbespalk          #+#    #+#             */
/*   Updated: 2019/04/24 16:38:40 by mdovhopo         ###   ########.fr       */
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
	while (objs)
	{
		obj = (t_object *)objs->content;
		if (obj->texture_id != NULL)
			obj->texture = init_texture(&textures, sdl, obj->texture_id);
		if (obj->noise != NULL && obj->noise->ramp_id != NULL)
        {
		    printf("RUMP %s to init\n", obj->noise->ramp_id);
		    obj->noise->ramp = init_texture(&textures, sdl, obj->noise->ramp_id)->surface;
		    if (obj->noise->ramp != NULL)
            {
		        printf("RUMP INITIALISED\n");
		        obj->noise->ft_get_color = ft_ramp_noise_col;
            }
        }
		if (obj->checker != NULL)
		{
        	i = -1;
        	while (++i < 2 && obj->checker->noise[i] != NULL)
			{
        		if (obj->checker->noise[i]->ramp_id != NULL)
				{
					obj->checker->noise[i]->ramp = init_texture(&textures, sdl,
							obj->checker->noise[i]->ramp_id)->surface;
					if (obj->checker->noise[i]->ramp != NULL)
					{
						printf("RUMP INITIALISED\n");
						obj->checker->noise[i]->ft_get_color = ft_ramp_noise_col;
					}
				}
			}
		}
		objs = objs->next;
	}
	i = -1;
	if (e->scn->skybox != NULL)
		while (++i < BOX_FACES)
			if (!(e->scn->skybox->textur[i] = init_texture(&textures, sdl,
					e->scn->skybox->textur_id[i])))
				return (-1);
	e->selected = NULL;
	return (0);
}

static void	sdl_draw_screen(t_env *e, t_sdl *sdl, uint32_t btn_id)
{
	ft_render(e);
	SDL_UpdateTexture(
		sdl->screen, NULL, sdl->pixels, sdl->scr_wid * sizeof(Uint32));
	SDL_RenderClear(sdl->renderer);
	SDL_RenderCopy(sdl->renderer, sdl->screen, NULL, NULL);
	ft_gui(e, btn_id);
	SDL_RenderPresent(sdl->renderer);
}

static void	ft_rt_loop(t_env *e)
{
	t_sdl		*sdl;
	uint32_t	btn_id;

	sdl = e->sdl;
	sdl->event_loop = 1;
	sdl_draw_screen(e, e->sdl, 0);
	while (sdl->event_loop)
	{
		int x = SDL_GetTicks();
		if ((btn_id = event_handler(e)))
			sdl_draw_screen(e, e->sdl, btn_id);
		if (!btn_id)
			sdl_draw_screen(e, e->sdl, 0);
		int y = SDL_GetTicks() - x;
		if (y != 0)
			printf("%f\n", 1000 / (float)y);
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
	if (gui_init(&sdl) < 0)
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
