//
// Created by Viktoriia BESPALKO on 2019-03-27.
//

#include "rt.h"
static void             ft_init_procedural(t_procedural *tex, char *name, char *function)
{
    tex->noise_ptr = (t_lattice *)ft_smemalloc(sizeof(t_lattice), "ft_init_procedural");
    ft_init_value_table(&(tex->noise_ptr->value_table));
    tex->noise_ptr->ft_generate_noise = ft_cubic_noise;
    tex->ft_get_color = ft_wrapped_noise_col;
    tex->ft_noise_value = function != NULL && ft_strcmp(function, TURBULANCE) == 0 ?
                ft_turbulance_noise : ft_fractal_noise;
    if (name != NULL)
        printf("NAME OF NOISE %s. SET VALUES ACCORDINGLY\n", name);
    tex->octaves = (int)tex->octaves == 0 ? 6 : tex->octaves;
    tex->gain = tex->gain <= FLT_MIN ? 0.5f : tex->gain;
    tex->lacunarity = tex->lacunarity <= FLT_MIN ? 2.0f : CLAMP(tex->lacunarity, 0, 20);
    tex->pertubation = tex->pertubation <= FLT_MIN ? 1.0f : tex->pertubation;
    tex->color.val = 0xff0000;
    ft_lattice_bounds((int)tex->octaves, tex->gain, tex->bounds);
}

void                    ft_parse_procedural(char **content, t_procedural **tex)
{
    char    *name;
    char    *function;

    if (!content || !(*content))
        return ;
    name = NULL;
    function = NULL;
    *tex = (t_procedural *)ft_smemalloc(sizeof(t_procedural), "ft_parse_procedural");
    (*tex)->ramp_id = NULL;
    (*tex)->octaves = 0;
    (*tex)->gain = FLT_MIN;
    (*tex)->lacunarity = FLT_MIN;
    (*tex)->pertubation = FLT_MIN;
    (*tex)->expansion = 1;
    (*tex)->min_max[0] = 0;
    (*tex)->min_max[1] = 1;
    ft_get_attr(content, "name", (void *)(&name),  DT_STRING);
    ft_get_attr(content, "function", (void *)(&function),  DT_STRING);
    ft_get_attr(content, "ramp", (void *)(&(*tex)->ramp_id), DT_STRING);
    ft_get_attr(content, "octaves", (void *)(&(*tex)->octaves), DT_FLOAT);
    ft_get_attr(content, "gain", (void *)(&(*tex)->gain), DT_FLOAT);
    ft_get_attr(content, "lacunarity", (void *)(&(*tex)->lacunarity), DT_FLOAT);
    ft_get_attr(content, "perturbation", (void *)(&(*tex)->pertubation), DT_FLOAT);
    ft_get_attr(content, "expansion", (void *)(&(*tex)->expansion), DT_FLOAT);
    ft_get_attr(content, "scale_min", (void *)(&(*tex)->min_max[0]), DT_FLOAT);
    ft_get_attr(content, "scale_max", (void *)(&(*tex)->min_max[1]), DT_FLOAT);
    ft_init_procedural(*tex, name, function);
    ft_memdel((void **)&name);
    ft_memdel((void **)&function);
    printf("PROEDURAL: ramp: %s, octav %d, gain %f, lacun %f, pert %f, expans %f, scale %f : %f,"
           "color %u\n",
           (*tex)->ramp_id, (int)(*tex)->octaves, (*tex)->gain, (*tex)->lacunarity, (*tex)->pertubation,
           (*tex)->expansion, (*tex)->min_max[0], (*tex)->min_max[1],  (*tex)->color.val);
}
