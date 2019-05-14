/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_procedural.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 18:41:31 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/14 18:41:33 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_init_lattice(t_procedural **tex, char *function, unsigned int seed)
{
	(*tex)->noise_ptr = (t_lattice *)ft_smemalloc(sizeof(t_lattice),
			"ft_init_lattice");
	ft_init_value_table(&((*tex)->noise_ptr->value_table), seed);
	(*tex)->noise_ptr->ft_generate_noise = ft_cubic_noise;
	(*tex)->ft_get_color = ft_wrapped_noise_col;
	(*tex)->ft_noise_value = function != NULL &&
			ft_strcmp(function, TURBULANCE) == 0 ?
			ft_turbulance_noise : ft_fractal_noise;
	(*tex)->scale = CLAMP(fabsf((*tex)->scale), 1, 99);
	(*tex)->octaves = CLAMP(fabsf((*tex)->octaves), 1, 7);
	(*tex)->gain = CLAMP(fabsf((*tex)->gain), 0, 1.2f);
	(*tex)->lacunarity = CLAMP((*tex)->lacunarity, 0, 20);
	(*tex)->pertubation = CLAMP((*tex)->pertubation, 0, 99);
	ft_lattice_bounds((int)(*tex)->octaves, (*tex)->gain, (*tex)->bounds);
}

void	ft_parse_procedural(char **cont, t_procedural **tex)
{
	char	*str[2];
	float	seed;

	if (!cont || !(*cont))
		return ;
	ft_bzero(str, sizeof(char *) * 2);
	seed = (float)time(NULL);
	*tex = (t_procedural *)ft_smemalloc(sizeof(t_procedural),
			"ft_parse_procedural");
	ft_get_attr(cont, "name", (void *)(&str[0]), DT_STRING);
	ft_get_attr(cont, "ramp", (void *)(&(*tex)->ramp_id), DT_STRING);
	str[0] != NULL ? ft_init_type(*tex, str[0]) : ft_null_lattice(*tex);
	ft_get_attr(cont, "seed", (void *)(&seed), DT_FLOAT);
	ft_get_attr(cont, "scale", (void *)(&(*tex)->scale), DT_FLOAT);
	ft_get_attr(cont, "function", (void *)(&str[1]), DT_STRING);
	ft_get_attr(cont, "octaves", (void *)(&(*tex)->octaves), DT_FLOAT);
	ft_get_attr(cont, "gain", (void *)(&(*tex)->gain), DT_FLOAT);
	ft_get_attr(cont, "lacunarity", (void *)(&(*tex)->lacunarity), DT_FLOAT);
	ft_get_attr(cont, "perturbation", (void *)(&(*tex)->pertubation), DT_FLOAT);
	ft_get_attr(cont, "level_min", (void *)(&(*tex)->min_max[0]), DT_FLOAT);
	ft_get_attr(cont, "level_max", (void *)(&(*tex)->min_max[1]), DT_FLOAT);
	ft_get_attr(cont, "color", (void *)(&(*tex)->color), DT_COLOR);
	ft_init_lattice(tex, str[1], (unsigned int)seed);
	ft_memdel((void **)&str[0]);
	ft_memdel((void **)&str[1]);
}

void	ft_set_procedural(t_procedural **tex, const char *smpl, Uint32 col)
{
	if (*tex == NULL)
	{
		*tex = (t_procedural *)ft_smemalloc(sizeof(t_procedural),
				"ft_set_procedural");
		ft_bzero(*tex, sizeof(t_procedural));
		if (smpl != NULL)
			ft_init_type(*tex, smpl);
		(*tex)->color.val = col;
		ft_init_lattice(tex, FRACTAL_SUM, (unsigned int)time(NULL));
	}
}

void	ft_load_noise_ramp(t_procedural *n, t_list **textures, t_sdl *sdl)
{
	n->ramp = init_texture(textures, sdl, n->ramp_id);
	if (n->ramp != NULL)
		n->ft_get_color = ft_ramp_noise_col;
	else
	{
		ft_memdel((void **)&(n->ramp_id));
		n->ft_get_color = ft_wrapped_noise_col;
	}
}

void	ft_noise_del(t_procedural **noise)
{
	if (!noise || !(*noise))
	{
		printf("NULL NOISE\n");
		return ;
	}
	if ((*noise)->noise_ptr)
		ft_memdel((void **)&((*noise)->noise_ptr->value_table));
	ft_memdel((void **)&(*noise)->noise_ptr);
	ft_memdel((void **)&(*noise)->ramp_id);
	ft_memdel((void **)noise);
	printf("DEL NOISE AT FT_NOISE_DEL\n");
}
