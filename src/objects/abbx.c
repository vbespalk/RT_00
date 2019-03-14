#include "rt.h"

t_aabb		*ft_aabbnew(void)
{
	t_aabb	*bbx;

	bbx = ft_smemalloc(sizeof(t_aabb), "ft_aabbnew");
	bbx->bounds[0] = (t_vector){-100, -100, -100};
	bbx->bounds[1] = (t_vector){ 100, 100, 100 };
	return (bbx);
}


char		*ft_parse_aabb(char **content, t_object *o)
{
	t_aabb		*bbx;

	o->ft_collide = ft_collide_aabb;
	o->ft_is_reachable = ft_is_reachable_aabb;
	o->ft_is_inside = ft_is_inside_aabb;
	o->ft_get_norm = ft_get_norm_aabb;
	o->ft_translate = ft_translate_aabb;
	o->ft_rotate = ft_rotate_aabb;
	o->ft_scale = ft_scale_aabb;
	o->ft_mapping = NULL;
	bbx = ft_aabbnew();
	ft_get_attr(content, "min", (void *)(&(bbx->bounds[0])), DT_POINT);
	ft_get_attr(content, "max", (void *)(&(bbx->bounds[1])), DT_POINT);
	bbx->norm = (t_vector){-1, 0, 0};
	bbx->bounds[0] += o->translate;
	bbx->bounds[1] += o->translate;
	bbx->dgnl = bbx->bounds[1] - bbx->bounds[0];
	bbx->cntr = bbx->bounds[0] + ft_3_vector_scale(bbx->dgnl, 0.5f);
	return ((void *)bbx);
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

void		ft_rotate_aabb(Uint32 key, void *fig, t_vector *rot)
{
	(void)key;
	(void)fig;
	(void)rot;
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