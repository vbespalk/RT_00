#include "rt.h"

t_box		*ft_boxnew(void)
{
	t_box	*bx;

	bx = ft_smemalloc(sizeof(t_box), "ft_boxnew");
	bx->bounds_ini[0] = (t_vector){-1, -1, -1};
	bx->bounds_ini[1] = (t_vector){ 1, 1, 1 };
	return (bx);
}


char		*ft_parse_box(char **content, t_object *o)
{
	t_box		*bx;

	o->ft_collide = ft_collide_box;
	o->ft_is_reachable = ft_is_reachable_box;
	o->ft_is_inside = ft_is_inside_box;
	o->ft_get_norm = ft_get_norm_box;
	o->ft_translate = ft_translate_box;
	o->ft_rotate = ft_rotate_box;
	o->ft_scale = ft_scale_box;
	o->ft_mapping = NULL;
	bx = ft_boxnew();
	ft_get_attr(content, "min", (void *)(&(bx->bounds_ini[0])), DT_POINT);
	ft_get_attr(content, "max", (void *)(&(bx->bounds_ini[1])), DT_POINT);
	bx->norm = (t_vector){-1, 0, 0};
	bx->bounds[0] = bx->bounds_ini[0] + o->translate;
	bx->bounds[1] = bx->bounds_ini[1] + o->translate;
	return ((void *)bx);
}

void		ft_translate_box(Uint32 key, void *fig, t_vector *transl)
{
	t_box *bx;

	bx = (t_box *)fig;
	if (!fig)
		return ;
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
	bx->bounds[0] = bx->bounds_ini[0] + *(transl);
	bx->bounds[1] = bx->bounds_ini[1] + *(transl);
}

void		ft_rotate_box(Uint32 key, void *fig, t_vector *rot)
{
	t_box *bx;

	bx = (t_box *)fig;
	if (!fig)
		return ;
	if (key == SDLK_DOWN)
		(*rot)[2] += ROTAT_F;
	else if (key == SDLK_UP)
		(*rot)[2] -= ROTAT_F;
	else if (key == SDLK_LEFT)
		(*rot)[1] -= ROTAT_F;
	else if (key == SDLK_RIGHT)
		(*rot)[1] += ROTAT_F;
	else if (key == SDLK_PAGEDOWN)
		(*rot)[0] += ROTAT_F;
	else if (key == SDLK_PAGEUP)
		(*rot)[0] -= ROTAT_F;
	// bx->norm = ft_3_vector_rotate(bx->norm_ini, (*rot)[0], (*rot)[1], (*rot)[2]);
}

void		ft_scale_box(Uint32 key, void *fig, float *scale)
{
	t_box		*bx;

	if (!fig)
		return ;

}