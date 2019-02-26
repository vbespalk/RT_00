#include "rt.h"

t_box		*ft_boxnew(void)
{
	t_box	*bx;

	bx = ft_smemalloc(sizeof(t_box), "ft_boxnew");
	bx->bounds_ini[0] = (t_vector){-50, -50, -50};
	bx->bounds_ini[1] = (t_vector){ 50, 50, 50.0 };
	return (bx);
}


char		*ft_parse_box(char *attr, t_scene *scn, unsigned int  id)
{
	t_object	*obj;
	t_box		*bx;

	// printf("here\n");
	// obj = ft_parse_object(attr);
	obj = ft_objectnew();
	obj->id = id;
	obj->refr = 1.0;
	obj->ft_collide = ft_collide_box;
	obj->ft_is_reachable = ft_is_reachable_box;
	obj->ft_is_inside = ft_is_inside_box;
	obj->ft_get_norm = ft_get_norm_box;
	obj->ft_translate = ft_translate_box;
	obj->ft_rotate = ft_rotate_box;
	obj->ft_scale = ft_scale_box;
	bx = ft_boxnew();
	// attr = ft_get_curve(attr, '{');
	// ft_get_attr_in_scope(attr, "origin:", (void *)(&(bx->origin_ini)), PNT);
	// ft_get_attr_in_scope(attr, "norm:", (void *)(&(bx->norm_ini)), PNT);
	// if (ft_3_vector_len(bx->norm_ini) == 0.0)
	// 	bx->norm_ini = (t_vector){ 0.0, 1.0, 0.0 };
	// bx->norm_ini = ft_3_tounitvector(ft_3_vector_rotate(
	// 		bx->norm_ini, obj->rotate[0], obj->rotate[1], obj->rotate[2]));
	// bx->origin_ini += obj->translate;
	bx->norm = (t_vector){-1, 0, 0};
	bx->bounds[0] = bx->bounds_ini[0];
	bx->bounds[1] = bx->bounds_ini[1];
	obj->fig = bx;
	// printf("box normal %f,%f,%f\n", bx->norm[0], bx->norm[1], bx->norm[2]);
	ft_lstpush(&(scn->objs), ft_nodenew((void *)obj, sizeof(obj)));
	return (NULL);
	// return (ft_get_curve(attr, '}'));
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