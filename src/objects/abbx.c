#include "rt.h"

t_aabb		*ft_init_aabb(t_vector min, t_vector max)
{
    t_aabb		*bbx;

    bbx = ft_smemalloc(sizeof(t_aabb), "ft_init_aabb");
    bbx->ft_collide = ft_collide_aabb;
    bbx->ft_is_reachable = ft_is_reachable_aabb;
    bbx->ft_translate = ft_translate_aabb;
    bbx->ft_scale = ft_scale_aabb;
    if (ft_3_iszeropoint(min) || ft_3_iszeropoint(max))
    {
        bbx->bounds[0] = (t_vector) {-100000, -100000, -100000};
        bbx->bounds[1] = (t_vector) {100000, 100000, 100000};
    }
    bbx->bounds[0] = min;
    bbx->bounds[1] = max;
    bbx->dgnl = bbx->bounds[1] - bbx->bounds[0];
    bbx->cntr = ft_3_vector_scale(bbx->bounds[0] + bbx->bounds[1], 0.5f);
    return ((void *)bbx);
}

int			ft_is_reachable_aabb(void *fig, t_vector origin, t_vector direct)
{
    (void)fig;
    (void)origin;
    (void)direct;
    return (1);
}

t_vector	ft_collide_aabb(void *fig, t_vector origin, t_vector direct)
{
    int 		i;
    float 		odd;
    float		minmax[2];
    float		t[2];

    t[0] = -FLT_MAX;
    t[1] = FLT_MAX;
    i = -1;
    while (++i < 3)
    {
        odd = 1.0f / direct[i];
        minmax[0] = (((t_aabb *)fig)->bounds[0][i] - origin[i]) * odd;
        minmax[1] = (((t_aabb *)fig)->bounds[1][i] - origin[i]) * odd;
        if (minmax[0] > minmax[1])
            ft_swap_float(&minmax[0], &minmax[1]);
        t[0] = minmax[0] > t[0] ? minmax[0] : t[0];
        t[1] = minmax[1] < t[1] ? minmax[1] : t[1];
        if (t[0] > t[1])
            return (ft_3_zeropointnew());
    }
    if (t[0] < 0 || (t[0] > t[1] && t[1] > FLT_MIN))
        ft_swap_float(&t[0], &t[1]);
    return (origin + ft_3_vector_scale(direct, t[0]));
//	return (t[0] > FLT_MIN ? origin + ft_3_vector_scale(direct, t[0]) : ft_3_zeropointnew());
}

void		ft_translate_aabb(Uint32 key, void *fig, t_vector *transl)
{
    t_aabb *bbx;

    if (!fig)
        return ;
    bbx = (t_aabb *)fig;
    if (key != UINT32_MAX)
        *transl = (t_vector){FLT_MIN, FLT_MIN, FLT_MIN};
    if (key == SDLK_d)
        (*transl)[2] += TRANS_F;
    if (key == SDLK_a)
        (*transl)[2] -= TRANS_F;
    if (key == SDLK_w)
        (*transl)[1] += TRANS_F;
    if (key == SDLK_s)
        (*transl)[1] -= TRANS_F;
    if (key == SDLK_e)
        (*transl)[0] += TRANS_F;
    if (key == SDLK_q)
        (*transl)[0] -= TRANS_F;
    bbx->bounds[0] += *(transl);
    bbx->bounds[1] += *(transl);
    bbx->cntr += *(transl);
}

void		ft_scale_aabb(Uint32 key, void *fig, float *scale)
{
    t_aabb		*bbx;
    t_vector	dir;
    float 		len;

    if (!fig)
        return ;
    bbx = (t_aabb *) fig;
    *scale = 1.0f;
    if (key == SDLK_z)
        *scale = (*scale + SCALE_F);
    else if (key == SDLK_x )
        *scale = (*scale - SCALE_F);
    dir = ft_3_tounitvector(bbx->dgnl);
    len = ft_3_vector_len(bbx->dgnl) * 0.5f * *scale;
    bbx->bounds[0] = bbx->cntr - ft_3_vector_scale(dir, len);
    bbx->bounds[1] = bbx->cntr + ft_3_vector_scale(dir, len);
    bbx->dgnl = bbx->bounds[1] - bbx->bounds[0];
}