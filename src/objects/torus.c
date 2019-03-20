//
// Created by ivoriik on 19.03.19.
//


#include "rt.h"

t_torus		*ft_torusnew(void)
{
	t_torus	*trs;

	trs = ft_smemalloc(sizeof(t_torus), "ft_torusnew");
	trs->o = (t_vector){0.0f, 0.0f, 0.0f};
	trs->v = (t_vector){0.0f, 1.0f, 0.0f};
	trs->r_inner = 10.f;
	trs->r_outer = 500.f;
	trs->n = ft_3_nullpointnew();
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
	o->ft_mapping = NULL;
	trs = ft_torusnew();
	ft_get_attr(content, "origin", (void *)(&(trs->o)), DT_POINT);
	ft_get_attr(content, "direct", (void *)(&(trs->v)), DT_POINT);
	ft_get_attr(content, "inner_radius", (void *)(&(trs->r_inner)), DT_FLOAT);
	ft_get_attr(content, "outer_radius", (void *)(&(trs->r_outer)), DT_FLOAT);
	trs->v = ft_3_tounitvector(trs->v);
	if (trs->r_inner > trs->r_outer)
		ft_swap_float(&(trs->r_inner), &(trs->r_outer));
	if (!ft_3_isnullpoint(o->rotate))
		trs->v = ft_3_tounitvector(ft_3_vector_rotate(trs->v, (o->rotate)[0],
				(o->rotate)[1], (o->rotate)[2]));
	if (!ft_3_isnullpoint(o->translate))
		trs->o = trs->o + o->translate;
	printf("ORI %f,%f,%f DIR %f,%f,%f, inner %f, outer %f\n", trs->o[0], trs->o[1], trs->o[2],
		   trs->v[0], trs->v[1], trs->v[2], trs->r_inner, trs->r_outer);
	return ((void *)trs);
}

void		ft_translate_torus(Uint32 key, void *fig, t_vector *transl)
{
	t_torus	*trs;

	trs = (t_torus *)fig;
	*transl = (t_vector){0,0,0};
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
	trs->o = trs->o + *(transl);
}

void		ft_rotate_torus(Uint32 key, void *fig, t_vector *rot)
{
	t_torus *trs;

	trs = (t_torus *)fig;
	*rot = (t_vector){0,0,0};
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
	trs->v = ft_3_tounitvector(ft_3_vector_rotate(trs->v, (*rot)[0], (*rot)[1], (*rot)[2]));
}

void		ft_scale_torus(Uint32 key, void *fig, float *scale)
{
	t_torus *trs;

	trs = (t_torus *)fig;
	*scale = 1;
	if (!fig)
		return ;
	if (key == SDLK_z)
	{
		*scale += SCALE_F;
	}
	else if (key == SDLK_x && *scale >= 0.0f)
	{
		*scale -= SCALE_F;
	}
	else
		*scale = 0;
	trs->r_inner = trs->r_inner * *scale;
	trs->r_outer = trs->r_outer * *scale;
}
