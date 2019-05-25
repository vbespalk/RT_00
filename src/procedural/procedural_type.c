/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procedural_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 18:43:31 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/14 18:44:11 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ft_init_mrbl(t_procedural *tex, char *ramp)
{
	if (tex->ramp_id == NULL && ramp)
		tex->ramp_id = ft_strdup(ramp);
	tex->ramp = NULL;
	tex->octaves = 7.0f;
	tex->scale = 8.0f;
	tex->gain = 0.5f;
	tex->lacunarity = 2;
	tex->min_max[0] = 0;
	tex->min_max[1] = 1;
	tex->pertubation = 10;
}

static void	ft_init_sandstn(t_procedural *tex, char *ramp)
{
	if (tex->ramp_id == NULL)
		tex->ramp_id = ft_strdup(ramp);
	tex->ramp = NULL;
	tex->octaves = 5;
	tex->scale = 1.f;
	tex->gain = 0.5f;
	tex->lacunarity = 2.0f;
	tex->min_max[0] = 0;
	tex->min_max[1] = 1;
	tex->pertubation = 0.05f;
}

void		ft_null_lattice(t_procedural *tex)
{
	tex->ramp = NULL;
	tex->octaves = 5;
	tex->gain = 0.5f;
	tex->lacunarity = 2.0f;
	tex->pertubation = 1;
	tex->min_max[0] = 0;
	tex->min_max[1] = 1;
	tex->color.val = 0xffffff;
	tex->scale = 10;
}

void		ft_init_type(t_procedural *tex, const char *name)
{
	if (ft_strcmp(name, TEX_GR_MRBL) == 0)
		ft_init_mrbl(tex, RAMP_GR_MRBL);
	else if (ft_strcmp(name, TEX_BL_MRBL) == 0)
		ft_init_mrbl(tex, RAMP_BL_MRBL);
	else if (ft_strcmp(name, TEX_WM_MRBL) == 0)
		ft_init_mrbl(tex, RAMP_WM_MRBL);
	else if (ft_strcmp(name, TEX_RD_MRBL) == 0)
		ft_init_mrbl(tex, RAMP_RD_MRBL);
	else if (ft_strcmp(name, TEX_GN_MRBL) == 0)
		ft_init_mrbl(tex, RAMP_GN_MRBL);
	else if (ft_strcmp(name, TEX_SANDSTN) == 0)
		ft_init_sandstn(tex, RAMP_SANDSTN);
	else if (ft_strcmp(name, TEX_LATTICE) == 0)
		ft_null_lattice(tex);
	else
	{
		ft_putendl(ON_WARN "ft_init_type. Unknown noise type. "
				   "Value set to default\n");
		ft_null_lattice(tex);
	}
}
