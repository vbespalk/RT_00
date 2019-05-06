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

static int ft_init_smpl(t_sdl *sdl, t_list **tex, t_procedural *dst[6])
{
	int i;

	ft_bzero(dst, sizeof(t_procedural *) * 6);
	ft_set_procedural(&(dst[0]), TEX_BL_MRBL, 0xFFFFFF);
	ft_set_procedural(&(dst[1]), TEX_GN_MRBL, 0xFFFFFF);
	ft_set_procedural(&(dst[2]), TEX_SANDSTN, 0xFFFFFF);
	ft_set_procedural(&(dst[3]), TEX_RD_MRBL, 0xFFFFFF);
	ft_set_procedural(&(dst[4]), TEX_GR_MRBL, 0xFFFFFF);
	ft_set_procedural(&(dst[5]), TEX_WM_MRBL, 0xFFFFFF);
	i = -1;
	while (++i < SMPL_NMB)
	{
		if ((dst[i])->ramp_id != NULL)
			ft_load_noise_ramp(dst[i], tex, sdl);
	}
}

static int	init_env(t_env *e, t_scene *scene, t_object **obj_pix, t_sdl *sdl)
{
	t_list		*textures;
	t_list		*objs;
	t_object	*obj;
	int 		i;

	e->scn = scene;
	e->asp_rat = (float)sdl->rt_wid / (float)sdl->scr_hei;
	e->pix_obj = obj_pix;
	e->sdl = sdl;
	textures = NULL;
	e->scn->textures = textures;
	ft_bzero(e->color_mode, sizeof(bool) * 5);
//	e->color_mode[0] = true;
	e->col_mode = NULL;
	ft_init_smpl(sdl, &(e->scn->textures), e->smpl);
	objs = e->scn->objs;
	while (objs)
	{
		obj = (t_object *)objs->content;
		if (obj->texture_id != NULL)
			obj->texture = init_texture(&textures, sdl, obj->texture_id);
		if (obj->noise != NULL && obj->noise->ramp_id != NULL)
        {
		    printf("RUMP %s to init\n", obj->noise->ramp_id);
			ft_load_noise_ramp(obj->noise, &(e->scn->textures), e->sdl);
        }
		if (obj->checker != NULL)
		{
        	i = -1;
        	while (++i < 2 && obj->checker->noise[i] != NULL)
			{
        		if (obj->checker->noise[i]->ramp_id != NULL)
				{
					obj->checker->noise[i]->ramp = init_texture(&textures, sdl,
							obj->checker->noise[i]->ramp_id);
					if (obj->checker->noise[i]->ramp != NULL)
					{
						printf("RUMP INITIALISED\n");
						obj->checker->noise[i]->ft_get_color = ft_ramp_noise_col;
					}
				}
			}
		}
		obj->tex_pnt = NULL;
		if (obj->texture != NULL)
		{
			printf("SET TEXTURE\n");
			obj->tex_pnt = obj->texture;
			obj->exposure = EXP_TEXTR;
		}
		else if (obj->noise != NULL)
		{
			printf("SET NOISE\n");
			obj->tex_pnt = obj->noise;
			obj->exposure = EXP_NOISE;
		}
		else if (obj->checker != NULL)
		{
			printf("SET CHCKR\n");
			obj->tex_pnt = obj->checker;
			obj->exposure = EXP_CHCKR;
		}
		objs = objs->next;
	}
	i = -1;
	if (e->scn->skybox != NULL)
		while (++i < BOX_FACES)
			if (!(e->scn->skybox->textur[i] = init_texture(&textures, sdl,
					e->scn->skybox->textur_id[i])))
			{
				ft_skybox_del(&(e->scn->skybox));
				break ;
			}
	printf("HERE\n");
	e->scn->skybox_on = (e->scn->skybox != NULL) ? true : false;
	e->selected = NULL;
	return (0);
}

static void	sdl_draw_screen(t_env *e, t_sdl *sdl, uint32_t btn_id, bool redraw)
{
	if (redraw)
	{
		printf("NEW RENDER\n");
		ft_render(e);
	}
	sdl->rt_cont = (SDL_Rect){0, 0,
							  e->sdl->rt_wid, e->sdl->scr_hei};
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
			sdl_draw_screen(e, e->sdl, btn_id, btn_id > (INVERTED + BTN_ID_SHIFT));
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
	sdl.scr_wid = SCR_WID;
	sdl.rt_wid = sdl.scr_wid - GUI_WIDTH;
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
		sizeof(t_object) * sdl.rt_wid * sdl.scr_hei, "main");
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
