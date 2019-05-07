//
// Created by ivoriik on 19.03.19.
//


#include "rt.h"

t_torus		*ft_torusnew(void)
{
	t_torus	*trs;

	trs = ft_smemalloc(sizeof(t_torus), "ft_torusnew");
	trs->r_inner = 10.f;
	trs->r_outer = 500.f;
	return (trs);
}

char		*ft_parse_torus(char **content, t_object *o)
{
	t_torus		*trs;

	o->ft_collide = ft_collide_torus;
	o->ft_is_reachable = ft_is_reachable_torus;
	o->ft_is_inside = ft_is_inside_torus;
	o->ft_get_norm = ft_get_norm_torus;
	o->ft_translate = ft_translate_torus;
	o->ft_rotate = ft_rotate_torus;
	o->ft_scale = ft_scale_torus;
	o->ft_scale_height = ft_scale_hei_null;
	o->ft_mapping = ft_map_torus;
	o->ft_checker =  ft_checker_tor;
	o->ft_procedural = ft_procedural_tor;
	trs = ft_torusnew();
	ft_get_attr(content, "inner_radius", (void *)(&(trs->r_inner)), DT_FLOAT);
	ft_get_attr(content, "outer_radius", (void *)(&(trs->r_outer)), DT_FLOAT);
	if (trs->r_inner > trs->r_outer)
		ft_swap_float(&(trs->r_inner), &(trs->r_outer));
	ft_3_transform_mat(&(o->transform), o->translate, o->rotate, FLT_MIN);
	ft_3_inv_trans_mat(&(o->inverse), -o->translate, -o->rotate, FLT_MIN);
	printf("MATRIX\n");
	for (int i = 0; i < 4; ++i)
		printf("%f, %f, %f, %f\n", o->transform[i][0], o->transform[i][1], o->transform[i][2], o->transform[i][3]);
	printf("INVERTED\n");
	for (int i = 0; i < 4; ++i)
		printf("%f, %f, %f, %f\n", o->inverse[i][0], o->inverse[i][1], o->inverse[i][2], o->inverse[i][3]);

	return ((void *)trs);
}

void		ft_translate_torus(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m)
{
	t_torus	*trs;

	if (!o)
		return ;
	trs = (t_torus *)o->fig;
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
	ft_3_transform_mat(tr_m, o->translate, o->rotate, FLT_MIN);
	ft_3_inv_trans_mat(inv_m, -o->translate, -o->rotate, FLT_MIN);
}

void		ft_rotate_torus(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m)
{
	t_torus *trs;

	if (!o)
		return ;
	trs = (t_torus *)o->fig;
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
	ft_3_transform_mat(tr_m, o->translate, o->rotate, FLT_MIN);
	ft_3_inv_trans_mat(inv_m, -o->translate, -o->rotate, FLT_MIN);
}

void		ft_scale_torus(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m)
{
	t_torus *trs;

	if (!o)
		return ;
	(void)tr_m;
	(void)inv_m;
	trs = (t_torus *)o->fig;
	float scale = 1;
	if (key == SDLK_z)
	{
		scale += SCALE_F;
	}
	else if (key == SDLK_x && scale - SCALE_F >= FLT_MIN)
		scale -= SCALE_F;
	trs->r_inner = trs->r_inner * scale;
	trs->r_outer = trs->r_outer * scale;
}
