#include "rt.h"

t_quad		*ft_quadnew(void)
{
	t_quad	*qd;

	qd = ft_smemalloc(sizeof(t_quad), "ft_quadnew");
	// qd->origin_ini = (t_vector){ 0.0, -1000.0, 0.0 };
	// qd->norm_ini = (t_vector){ 0.0, 1.0, 0.0 };
	qd->v0_ini = (t_vector){ 0.0, 0.0, 0.0 };
	qd->v1_ini = (t_vector){ 0.0, 0.0, 100.0 };
	qd->v2_ini = (t_vector){ 100.0, 150.0, 20.0 };
	return (qd);
}


char		*ft_parse_quad(char *attr, t_scene *scn, unsigned int  id)
{
	t_object	*obj;
	t_quad	*qd;

	// obj = ft_parse_object(attr);
	obj = ft_objectnew(id);
	obj->refr = 1.0;
	obj->ft_collide = ft_collide_quad;
	obj->ft_is_reachable = ft_is_reachable_quad;
	obj->ft_is_inside = ft_is_inside_quad;
	obj->ft_get_norm = ft_get_norm_quad;
	obj->ft_translate = ft_translate_quad;
	obj->ft_rotate = ft_rotate_quad;
	obj->ft_scale = ft_scale_quad;
	qd = ft_quadnew();
	// attr = ft_get_curve(attr, '{');
	// ft_get_attr_in_scope(attr, "origin:", (void *)(&(qd->origin_ini)), PNT);
	// ft_get_attr_in_scope(attr, "norm:", (void *)(&(qd->norm_ini)), PNT);
	// if (ft_3_vector_len(qd->norm_ini) == 0.0)
	// 	qd->norm_ini = (t_vector){ 0.0, 1.0, 0.0 };
	qd->v0 = qd->v0_ini;
	qd->v1 = qd->v1_ini;
	qd->v2 = qd->v2_ini;
	qd->norm = ft_3_tounitvector(ft_3_vector_cross(qd->v2 - qd->v0, qd->v1 - qd->v0));
	printf("quad normal %f,%f,%f\n", qd->norm[0], qd->norm[1], qd->norm[2]);
	obj->fig = qd;
	ft_lstpush(&(scn->objs), ft_nodenew((void *)obj, sizeof(obj)));
	return (NULL);
	// return (ft_get_curve(attr, '}'));
}

void		ft_translate_quad(Uint32 key, void *fig, t_vector *transl)
{
	t_quad *qd;

	qd = (t_quad *)fig;
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
	qd->v0 = qd->v0_ini + *(transl);
	qd->v1 = qd->v1_ini + *(transl);
	qd->v2 = qd->v2_ini + *(transl);
}

void		ft_rotate_quad(Uint32 key, void *fig, t_vector *rot)
{
	t_quad *qd;

	qd = (t_quad *)fig;
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
	// qd->norm = ft_3_vector_rotate(qd->norm_ini, (*rot)[0], (*rot)[1], (*rot)[2]);
}

void		ft_scale_quad(Uint32 key, void *fig, float *scale)
{
	t_quad *qd;

	qd = (t_quad *)fig;
	(void)key;
	if (!fig)
		return ;
}