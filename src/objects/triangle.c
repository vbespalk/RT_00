#include "rt.h"

t_triangle		*ft_trianglenew(void)
{
	t_triangle	*trgl;

	trgl = ft_smemalloc(sizeof(t_triangle), "ft_trianglenew");
	// trgl->origin_ini = (t_vector){ 0.0, -1000.0, 0.0 };
	// trgl->norm_ini = (t_vector){ 0.0, 1.0, 0.0 };
	trgl->v0_ini = (t_vector){ 0.0, 0, -50.0 };
	trgl->v1_ini = (t_vector){ 0.0, 90.0, 0.0 };
	trgl->v2_ini = (t_vector){ 0.0, 0.0, 50.0 };
	return (trgl);
}


char		*ft_parse_triangle(char *attr, t_scene *scn, unsigned int  id)
{
	t_object	*obj;
	t_triangle	*trgl;

	// obj = ft_parse_object(attr);
	obj = ft_objectnew();
	obj->id = id;
	obj->refr = 1.0;
	obj->ft_collide = ft_collide_triangle;
	obj->ft_is_reachable = ft_is_reachable_triangle;
	obj->ft_is_inside = ft_is_inside_triangle;
	obj->ft_get_norm = ft_get_norm_triangle;
	obj->ft_translate = ft_translate_triangle;
	obj->ft_rotate = ft_rotate_triangle;
	obj->ft_scale = ft_scale_triangle;
	trgl = ft_trianglenew();
	// attr = ft_get_curve(attr, '{');
	// ft_get_attr_in_scope(attr, "origin:", (void *)(&(trgl->origin_ini)), PNT);
	// ft_get_attr_in_scope(attr, "norm:", (void *)(&(trgl->norm_ini)), PNT);
	// if (ft_3_vector_len(trgl->norm_ini) == 0.0)
	// 	trgl->norm_ini = (t_vector){ 0.0, 1.0, 0.0 };
	trgl->v0 = trgl->v0_ini;
	trgl->v1 = trgl->v1_ini;
	trgl->v2 = trgl->v2_ini;
	trgl->unorm = ft_3_vector_cross(trgl->v2 - trgl->v0, trgl->v1 - trgl->v0);
	trgl->norm = ft_3_tounitvector(trgl->unorm);
	printf("triangle normal %f,%f,%f\n", trgl->norm[0], trgl->norm[1], trgl->norm[2]);
	obj->fig = trgl;
	ft_lstpush(&(scn->objs), ft_nodenew((void *)obj, sizeof(obj)));
	return (NULL);
	// return (ft_get_curve(attr, '}'));
}

void		ft_translate_triangle(Uint32 key, void *fig, t_vector *transl)
{
	t_triangle *trgl;

	trgl = (t_triangle *)fig;
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
	trgl->v0 = trgl->v0_ini + *(transl);
	trgl->v1 = trgl->v1_ini + *(transl);
	trgl->v2 = trgl->v2_ini + *(transl);
}

void		ft_rotate_triangle(Uint32 key, void *fig, t_vector *rot)
{
	t_triangle *trgl;

	trgl = (t_triangle *)fig;
	if (!fig)
		return ;
	// if (key == SDLK_DOWN)
	// 	(*rot)[2] += ROTAT_F;
	// else if (key == SDLK_UP)
	// 	(*rot)[2] -= ROTAT_F;
	// else if (key == SDLK_LEFT)
	// 	(*rot)[1] -= ROTAT_F;
	// else if (key == SDLK_RIGHT)
	// 	(*rot)[1] += ROTAT_F;
	// else if (key == SDLK_PAGEDOWN)
	// 	(*rot)[0] += ROTAT_F;
	// else if (key == SDLK_PAGEUP)
	// 	(*rot)[0] -= ROTAT_F;
	// trgl->norm = ft_3_vector_rotate(trgl->norm_ini, (*rot)[0], (*rot)[1], (*rot)[2]);
}

void		ft_scale_triangle(Uint32 key, void *fig, float *scale)
{
	t_triangle *trgl;

	trgl = (t_triangle *)fig;
	(void)key;
	if (!fig)
		return ;
}