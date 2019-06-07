/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 17:34:01 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/14 17:34:03 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		ft_init_checker(t_checkbrd *tex)
{
	if (tex->color[1] == UINT32_MAX && tex->color[0] != UINT32_MAX)
		ft_swap(&tex->color[0], &tex->color[1], sizeof(Uint32));
	if (tex->noise[0] == NULL && tex->noise[1] != NULL)
		ft_swap(&tex->noise[0], &tex->noise[1], sizeof(t_procedural *));
	tex->color[0] = tex->color[0] == UINT32_MAX ? 0xffffff :
			(Uint32)MINV(tex->color[0], (unsigned int)0xffffff);
	tex->color[1] = tex->color[1] == UINT32_MAX ? 0x666666 :
			(Uint32)MINV(tex->color[1], (unsigned int)0xffffff);
}

static void		ft_set_checker_color(t_checkbrd *tex, const char *color, int i)
{
	tex->color[i] = UINT32_MAX;
	tex->noise[i] = NULL;
	if (!color)
		return ;
	if (ft_isdigit(color[0]))
		tex->color[i] = SDL_Swap32(ft_limit_uint(
		0, 0xffffff, ft_atoi_base(color, 16)) << 8);
	else if (!ft_strcmp(color, TEX_GR_MRBL) || !ft_strcmp(color, TEX_BL_MRBL)
		|| !ft_strcmp(color, TEX_WM_MRBL) || !ft_strcmp(color, TEX_SANDSTN) ||
		!ft_strcmp(color, TEX_RD_MRBL) || !ft_strcmp(color, TEX_GN_MRBL) ||
		!ft_strcmp(color, TEX_LATTICE))
		ft_set_procedural(&(tex->noise[i]), color, 0xFFFFFF);
	else
		ft_putendl(ON_WARN "ft_set_checker_color: unknown color / "
			"texture description. Value set to default\n");
}

void			ft_parse_checker(char **content, t_checkbrd **tex)
{
	char	*color[2];
	float	size;
	int		i;

	if (!content || !(*content))
		return ;
	ft_bzero(color, sizeof(char *) * 2);
	ft_get_attr(content, "color1", (void *)(&color[0]), DT_STRING);
	ft_get_attr(content, "color2", (void *)(&color[1]), DT_STRING);
	ft_get_attr(content, "size", (void *)(&size), DT_FLOAT);
	*tex = (t_checkbrd *)ft_smemalloc(sizeof(t_checkbrd), "ft_parse_checker");
	i = -1;
	while (++i < 2)
	{
		ft_set_checker_color(*tex, color[i], i);
		ft_memdel((void **)&color[i]);
	}
	(*tex)->size = CLAMP((unsigned int)size, 1, 15);
	ft_init_checker(*tex);
}

void			ft_set_checker(t_checkbrd **chkr, Uint32 col)
{
	(*chkr) = (t_checkbrd *)ft_smemalloc(sizeof(t_checkbrd),
			"ft_parse_checker");
	ft_bzero(*chkr, sizeof(t_checkbrd));
	(*chkr)->color[0] = col;
	(*chkr)->color[1] = 0xFFFFFF;
	(*chkr)->size = 2;
}

void			ft_checker_del(t_checkbrd **checker)
{
	if (!checker || !(*checker))
		return ;
	if ((*checker)->noise[0])
		ft_noise_del(&(*checker)->noise[0]);
	if ((*checker)->noise[1])
		ft_noise_del(&(*checker)->noise[1]);
	ft_memdel((void **)checker);
}
