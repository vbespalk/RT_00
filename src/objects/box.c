#include "rt.h"

t_box		*ft_boxnew(void)
{
	t_box	*bx;

	bx = ft_smemalloc(sizeof(t_box), "ft_boxnew");
	bx->whl[0] = 10;
	bx->whl[1] = 10;
	bx->whl[2] = 10;
	return (bx);
}

void		ft_init_box(t_box *bx, t_vector transl, t_vector rot)
{
	t_vector	max_pnt;
	t_plane		*pln[BOX_FACES];
	t_vector	dir_whl[3];
	float 		len_whl[3];
	int			i;

	i = -1;
	while (++i < BOX_FACES)
	{
		bx->face[i] = ft_smemalloc(sizeof(t_object), "ft_init_box");
		bx->face[i]->ft_collide = ft_collide_plane;
		bx->face[i]->ft_is_reachable = ft_is_reachable_plane;
		bx->face[i]->ft_is_inside = ft_is_inside_plane;
		bx->face[i]->ft_get_norm = ft_get_norm_plane;
		bx->face[i]->ft_translate = ft_translate_plane;
		bx->face[i]->ft_rotate = ft_rotate_plane;
		bx->face[i]->ft_scale = ft_scale_plane;
		bx->face[i]->ft_scale_height = ft_scale_hei_null;
		bx->face[i]->ft_mapping = ft_map_plane;
		bx->face[i]->ft_checker = ft_checker_pln;
		bx->face[i]->ft_procedural = ft_procedural_pln;
		bx->face[i]->fig = ft_smemalloc(sizeof(t_plane), "ft_init_box");
		pln[i] = (t_plane *)bx->face[i]->fig;
	}
	bx->face[0]->translate = (t_vector){-bx->whl[0], 0, 0};
	pln[0]->len_wh[0] = bx->whl[2];
	pln[0]->len_wh[1] = bx->whl[1];
	pln[0]->ratio = pln[0]->len_wh[1] / pln[0]->len_wh[0];
	bx->face[0]->rotate = (t_vector){FLT_MIN, FLT_MIN, DEG_TO_RAD(90)};
	bx->face[3]->translate = (t_vector){bx->whl[0], 0, 0};
	pln[3]->len_wh[0] = bx->whl[2];
	pln[3]->len_wh[1] = bx->whl[1];
	pln[3]->ratio = pln[3]->len_wh[1] / pln[3]->len_wh[0];
	bx->face[3]->rotate = (t_vector){FLT_MIN, FLT_MIN, DEG_TO_RAD(90)};
	bx->face[1]->translate = (t_vector){0, -bx->whl[1], 0};
	pln[1]->len_wh[0] = bx->whl[2];
	pln[1]->len_wh[1] = bx->whl[0];
	pln[1]->ratio = pln[1]->len_wh[1] / pln[1]->len_wh[0];
	bx->face[1]->rotate = (t_vector){FLT_MIN, FLT_MIN, FLT_MIN};
	bx->face[4]->translate = (t_vector){0, bx->whl[1], 0};
	pln[4]->len_wh[0] = bx->whl[2];
	pln[4]->len_wh[1] = bx->whl[0];
	pln[4]->ratio = pln[4]->len_wh[1] / pln[4]->len_wh[0];
	bx->face[4]->rotate = (t_vector){FLT_MIN, FLT_MIN, FLT_MIN};
	bx->face[2]->translate = (t_vector){0, 0, -bx->whl[2]};
	pln[2]->len_wh[0] = bx->whl[1];
	pln[2]->len_wh[1] = bx->whl[0];
	pln[2]->ratio = pln[2]->len_wh[1] / pln[2]->len_wh[0];
	bx->face[2]->rotate = (t_vector){DEG_TO_RAD(90), FLT_MIN, FLT_MIN};
	bx->face[5]->translate = (t_vector){0, 0, bx->whl[2]};
	pln[5]->len_wh[0] = bx->whl[1];
	pln[5]->len_wh[1] = bx->whl[0];
	pln[5]->ratio = pln[5]->len_wh[1] / pln[5]->len_wh[0];
	bx->face[5]->rotate = (t_vector){DEG_TO_RAD(90), FLT_MIN, FLT_MIN};
	i = -1;
	while (++i < BOX_FACES)
	{
		ft_3_transform_mat(&(bx->face[i]->transform), bx->face[i]->translate,
				bx->face[i]->rotate, pln[i]->len_wh[0]);
		ft_3_inv_trans_mat(&(bx->face[i]->inverse), -bx->face[i]->translate,
				-bx->face[i]->rotate, 1.0f / pln[i]->len_wh[0]);
	}
//	while (++i < BOX_FACES)
//	{
//		bx->face[i] = ft_smemalloc(sizeof(t_plane), "ft_init_box");
//		bx->face[i]->origin[i % 3] = i < 3 ? -bx->whl[i] * 0.5f : bx->whl[i % 3] * 0.5f;
//		bx->face[i]->len_wh[0] = len_whl[(i + 1) % 3];
//		bx->face[i]->len_wh[1] = len_whl[(i + 2) % 3];
//		bx->face[i]->cntr = ft_3_nullpointnew();
//		bx->face[i]->norm = ft_3_vector_cross(bx->face[i]->dir_wh[0], bx->face[i]->dir_wh[1]);
//	}
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
	o->ft_mapping = ft_map_box;
	o->ft_checker = ft_checker_box;
	bx = ft_boxnew();
	ft_get_attr(content, "length", (void *)(&(bx->whl[2])), DT_FLOAT);
	ft_get_attr(content, "width", (void *)(&(bx->whl[0])), DT_FLOAT);
	ft_get_attr(content, "height", (void *)(&(bx->whl[1])), DT_FLOAT);
	ft_init_box(bx, o->translate, o->rotate);
	bx->scale = 1;
	ft_3_transform_mat(&(o->transform), o->translate, o->rotate, FLT_MIN);
	ft_3_inv_trans_mat(&(o->inverse), -o->translate, -o->rotate, FLT_MIN);
	return ((void *)bx);
}

void		ft_translate_box(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m)
{
	t_box	*bx;
	int 	i;

	if (!o)
		return ;
	bx = (t_box *)o->fig;
	if (key == SDLK_d)
		o->translate[2] += TRANS_F;
	if (key == SDLK_a)
		o->translate[2] -= TRANS_F;
	if (key == SDLK_w)
		o->translate[1] += TRANS_F;
	if (key == SDLK_s)
		o->translate[1] -= TRANS_F;
	if (key == SDLK_e)
		o->translate[0] += TRANS_F;
	if (key == SDLK_q)
		o->translate[0] -= TRANS_F;
	ft_3_transform_mat(tr_m, o->translate, o->rotate, bx->scale);
	ft_3_inv_trans_mat(inv_m, -o->translate, -o->rotate, 1.f / bx->scale);
}

void		ft_rotate_box(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m)
{
	t_box	*bx;
	int 	i;
	float 	len;

	if (!o)
		return ;
	bx = (t_box *)o->fig;
	if (key == SDLK_DOWN)
		o->rotate[2] += ROTAT_F;
	else if (key == SDLK_UP)
		o->rotate[2] -= ROTAT_F;
	else if (key == SDLK_LEFT)
		o->rotate[1] -= ROTAT_F;
	else if (key == SDLK_RIGHT)
		o->rotate[1] += ROTAT_F;
	else if (key == SDLK_PAGEDOWN)
		o->rotate[0] += ROTAT_F;
	else if (key == SDLK_PAGEUP)
		o->rotate[0] -= ROTAT_F;
	ft_3_transform_mat(tr_m, o->translate, o->rotate, bx->scale);
	ft_3_inv_trans_mat(inv_m, -o->translate, -o->rotate, 1.f / bx->scale);
}

void		ft_scale_box(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m)
{
	t_box		*bx;

	if (!o)
		return ;
	bx = (t_box *)o->fig;
	if (key == SDLK_z)
		bx->scale *= (1.f + SCALE_F);
	else if (key == SDLK_x )
		bx->scale *= (1.f - SCALE_F);
	ft_3_transform_mat(tr_m, o->translate, o->rotate, bx->scale);
	ft_3_inv_trans_mat(inv_m, -o->translate, -o->rotate, 1.f / bx->scale);
}

void		ft_scale_hei_null(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m)
{
	(void)key;
	(void)o;
	(void)tr_m;
	(void)inv_m;
}