/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 18:07:18 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/08 18:07:21 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	ft_init_smpl(t_sdl *sdl, t_list **tex, t_procedural *dst[6])
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
	return (1);
}

static void	ft_obj_exposure(t_object *obj)
{
	if (obj == NULL)
		return ;
	obj->exposure = EXP_COLOR;
	if (obj->texture != NULL)
	{
		obj->tex_pnt = obj->texture;
		obj->exposure = EXP_TEXTR;
	}
	else if (obj->noise != NULL)
	{
		obj->tex_pnt = obj->noise;
		obj->exposure = EXP_NOISE;
	}
	else if (obj->checker != NULL)
	{
		obj->tex_pnt = obj->checker;
		obj->exposure = EXP_CHCKR;
	}
}

static void	ft_load_textures(t_list *objs, t_list **textures, t_sdl *sdl)
{
	t_object	*obj;
	int			i;

	while (objs)
	{
		obj = (t_object *)objs->content;
		if (obj->texture_id != NULL)
			obj->texture = init_texture(textures, sdl, obj->texture_id);
		if (obj->noise != NULL && obj->noise->ramp_id != NULL)
			ft_load_noise_ramp(obj->noise, textures, sdl);
		if (obj->checker != NULL)
		{
			i = -1;
			while (++i < 2 && obj->checker->noise[i] != NULL)
				if (obj->checker->noise[i]->ramp_id != NULL)
					ft_load_noise_ramp(obj->checker->noise[i], textures, sdl);
		}
		ft_obj_exposure(obj);
		objs = objs->next;
	}
}

int			init_env(t_env *e, t_scene *scene, t_object **obj_pix, t_sdl *sdl)
{
	e->scn = scene;
	e->asp_rat = (float)sdl->rt_wid / (float)sdl->scr_hei;
	e->pix_obj = obj_pix;
	e->sdl = sdl;
	ft_init_smpl(sdl, &(e->scn->textures), e->smpl);
	ft_load_textures(e->scn->objs, &e->scn->textures, sdl);
	if (e->scn->skybox != NULL)
		e->scn->skybox_on = ft_load_sky_tex(&e->scn->skybox,
			&e->scn->textures, sdl);
	e->selected = NULL;
	return (0);
}
