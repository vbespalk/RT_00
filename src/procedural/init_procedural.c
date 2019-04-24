//
// Created by Viktoriia BESPALKO on 2019-03-27.
//

#include "rt.h"

static void     ft_init_mrbl(t_procedural *tex, char *ramp)
{
    if (tex->ramp_id == NULL)
        tex->ramp_id = ft_strdup(ramp);
	tex->ramp = NULL;
	tex->octaves = 7.f;
	tex->scale = 2.5f;
	tex->gain = 0.5f;
    tex->lacunarity = 2;
    tex->pertubation = 10;
}

static void     ft_init_sandstn(t_procedural *tex, char *ramp)
{
    if (tex->ramp_id == NULL)
        tex->ramp_id = ft_strdup(ramp);
	tex->ramp = NULL;
	tex->octaves = 5;
	tex->scale = 1.f;
	tex->gain = 0.5f;
	tex->lacunarity = 2.0f;
    tex->pertubation = 0.05f;
}

static void             ft_null_lattice(t_procedural *tex)
{
	tex->ramp_id = NULL;
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

static void		ft_init_type(t_procedural *tex, char *name)
{
	if (ft_strcmp(name, TEX_GR_MRBL) == 0)
		ft_init_mrbl(tex, RAMP_GR_MRBL);
	else if (ft_strcmp(name, TEX_BL_MRBL) == 0)
		ft_init_mrbl(tex, RAMP_BL_MRBL);
	else if (ft_strcmp(name, TEX_WM_MRBL) == 0)
		ft_init_mrbl(tex, RAMP_WM_MRBL);
	else if (ft_strcmp(name, TEX_SANDSTN) == 0)
		ft_init_sandstn(tex, RAMP_SANDSTN);
	else if (ft_strcmp(name, TEX_LATTICE) == 0)
		ft_null_lattice(tex);
	else
	{
		printf("WARNING: UNKNOWN TYPE, VALUE SET TO DEFAULT\n");
		ft_null_lattice(tex);
	}
}

void            ft_init_lattice(t_procedural **tex, char *function, unsigned int seed)
{
	if (*tex == NULL)
	{
		printf("LATTICE TEX IS ZERO\n");
		*tex = (t_procedural *)ft_smemalloc(sizeof(t_procedural), "ft_init_lattice");
		(*tex)->ramp = NULL;
		if (function != NULL)
			ft_init_type(*tex, function);
	}
	(*tex)->noise_ptr = (t_lattice *)ft_smemalloc(sizeof(t_lattice), "ft_init_lattice");
    ft_init_value_table(&((*tex)->noise_ptr->value_table), seed);
	(*tex)->noise_ptr->ft_generate_noise = ft_cubic_noise;
	(*tex)->ft_get_color = ft_wrapped_noise_col;
	(*tex)->ft_noise_value = function != NULL && ft_strcmp(function, TURBULANCE) == 0 ?
                ft_turbulance_noise : ft_fractal_noise;
	(*tex)->scale = CLAMP(fabsf((*tex)->scale), 1, 99);
	(*tex)->octaves = CLAMP(fabsf((*tex)->octaves), 1, 7);
	(*tex)->gain = CLAMP(fabsf((*tex)->gain), 0, 1.2f);
	(*tex)->lacunarity = CLAMP((*tex)->lacunarity, 0, 20);
	(*tex)->pertubation = CLAMP((*tex)->pertubation, 0, 99);
    ft_lattice_bounds((int)(*tex)->octaves, (*tex)->gain, (*tex)->bounds);
}

void                    ft_parse_procedural(char **content, t_procedural **tex)
{
    char    *name;
    char    *function;
    float    seed;

    if (!content || !(*content))
        return ;
    name = NULL;
    function = NULL;
    seed = (float)time(NULL);
    *tex = (t_procedural *)ft_smemalloc(sizeof(t_procedural), "ft_parse_procedural");
	ft_get_attr(content, "name", (void *)(&name),  DT_STRING);
	ft_get_attr(content, "ramp", (void *)(&(*tex)->ramp_id), DT_STRING);
	name != NULL ? ft_init_type(*tex, name) : ft_null_lattice(*tex);
    ft_get_attr(content, "seed", (void *)(&seed), DT_FLOAT);
    ft_get_attr(content, "scale", (void *)(&(*tex)->scale), DT_FLOAT);
    ft_get_attr(content, "function", (void *)(&function),  DT_STRING);
    ft_get_attr(content, "octaves", (void *)(&(*tex)->octaves), DT_FLOAT);
    ft_get_attr(content, "gain", (void *)(&(*tex)->gain), DT_FLOAT);
    ft_get_attr(content, "lacunarity", (void *)(&(*tex)->lacunarity), DT_FLOAT);
    ft_get_attr(content, "perturbation", (void *)(&(*tex)->pertubation), DT_FLOAT);
    ft_get_attr(content, "level_min", (void *)(&(*tex)->min_max[0]), DT_FLOAT);
    ft_get_attr(content, "level_max", (void *)(&(*tex)->min_max[1]), DT_FLOAT);
    ft_get_attr(content, "color", (void *)(&(*tex)->color), DT_COLOR);
    ft_init_lattice(tex, function, (unsigned int) seed);
    ft_memdel((void **)&name);
    ft_memdel((void **)&function);
}
