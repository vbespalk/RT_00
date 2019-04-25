//
// Created by ivoriik on 21.04.19.
//
#include "rt.h"
static void				ft_init_checker(t_checkbrd *tex)
{
	if (tex->color[1] == UINT32_MAX && tex->color[0] != UINT32_MAX)
		ft_swap(&tex->color[0], &tex->color[1], sizeof(Uint32));
	if (tex->noise[0] == NULL && tex->noise[1] != NULL)
		ft_swap(&tex->noise[0], &tex->noise[1], sizeof(t_procedural *));
	tex->color[0] = tex->color[0] == UINT32_MAX ? 0xcccccc : (Uint32)CLAMP(tex->color[0], 0, 0xffffff);
	tex->color[1] = tex->color[1] == UINT32_MAX ? 0x666666 : (Uint32)CLAMP(tex->color[1], 0, 0xffffff);
}
void                    ft_parse_checker(char **content, t_checkbrd **tex)
{
	char	*color[2];
	float 	size;
	int 	i;

	if (!content || !(*content))
		return ;
	color[0] = NULL;
	color[1] = NULL;
	ft_get_attr(content, "color1", (void *)(&color[0]), DT_STRING);
	ft_get_attr(content, "color2", (void *)(&color[1]), DT_STRING);
	ft_get_attr(content, "size", (void *)(&size), DT_FLOAT);
	*tex = (t_checkbrd *)ft_smemalloc(sizeof(t_checkbrd), "ft_parse_checker");
	i = -1;
	while (++i < 2)
	{
		(*tex)->color[i] = UINT32_MAX;
		(*tex)->noise[i] = NULL;
		if (!color[i])
			continue ;
		if (ft_isdigit(color[i][0]))
		{
			((*tex)->color[i]) = ft_limit_uint(
					0, 0xffffff, (unsigned int)ft_atoi_base(color[i], 16));
		}
		else if (!ft_strcmp(color[i], TEX_GR_MRBL) || !ft_strcmp(color[i], TEX_BL_MRBL)
		|| !ft_strcmp(color[i], TEX_WM_MRBL) || !ft_strcmp(color[i], TEX_SANDSTN) ||
		!ft_strcmp(color[i], TEX_LATTICE))
			ft_init_lattice(&((*tex)->noise[i]), color[i], (unsigned int)time(NULL));
		else
			printf("WARNING: WRONG COLOR / TEXTURE VALUE, SET TO DEFAULT\n");
	}
	(*tex)->size = CLAMP((unsigned int)size, 1, 15);
	ft_init_checker(*tex);
}
