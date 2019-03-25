#include "rt.h"

t_box		*ft_boxnew(void)
{
	t_box	*bx;

	bx = ft_smemalloc(sizeof(t_box), "ft_boxnew");
	bx->o = (t_vector){-100, -100, -100};
	bx->lwh[0] = (t_vector){ -100, -100, 100 };
	bx->lwh[1] = (t_vector){ 400, -100, -100 };
	bx->lwh[2] = (t_vector){ -100, 100, -100 };
	return (bx);
}

void		ft_init_box(t_box *bx)
{
	t_vector	max_pnt;
	t_vector	dir_lwh[3];
	float 		len_lwh[3];
	int			i;

	max_pnt = bx->lwh[0] + bx->lwh[1] + bx->lwh[2] - ft_3_vector_scale(bx->o, 2);
	bx->dgnl = max_pnt - bx->o;
	bx->cntr = bx->o + ft_3_vector_scale(bx->dgnl, 0.5f);
	i = -1;
	while (++i < 3)
	{
		dir_lwh[i] = ft_3_tounitvector(bx->lwh[i] - bx->o);
		len_lwh[i] = ft_3_vector_len(bx->lwh[i] - bx->o);
		bx->lwh[i] -= bx->o;
	}
	printf("ORI %F,%F,%F MAX BOX PNT %f,%f,%f\n", bx->o[0], bx->o[1], bx->o[2], max_pnt[0], max_pnt[1], max_pnt[2]);
	i = -1;
	while (++i < BOX_FACES)
	{
		bx->face[i] = ft_smemalloc(sizeof(t_plane), "ft_init_box");
		bx->face[i]->origin = i < 3 ? bx->o : max_pnt;
		bx->face[i]->dir_wh[0] = i < 3 ? dir_lwh[i % 3] : -dir_lwh[i % 3];
		bx->face[i]->dir_wh[1] = i < 3 ? dir_lwh[(i + 1) % 3] : -dir_lwh[(i + 1) % 3];
		bx->face[i]->len_wh[0] = len_lwh[i % 3];
		bx->face[i]->len_wh[1] = len_lwh[(i + 1) % 3];
		bx->face[i]->cntr = ft_3_nullpointnew();
		bx->face[i]->norm = ft_3_vector_cross(bx->face[i]->dir_wh[0], bx->face[i]->dir_wh[1]);
	}
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
	ft_get_attr(content, "origin", (void *)(&(bx->o)), DT_POINT);
	ft_get_attr(content, "l_vector", (void *)(&(bx->lwh[0])), DT_POINT);
	ft_get_attr(content, "w_vector", (void *)(&(bx->lwh[1])), DT_POINT);
	ft_get_attr(content, "h_vector", (void *)(&(bx->lwh[2])), DT_POINT);
	if (fabsf(ft_3_vector_dot(bx->lwh[0] - bx->o, bx->lwh[1] - bx->o)) > 1e-6 ||
		fabsf(ft_3_vector_dot(bx->lwh[1] - bx->o, bx->lwh[2] - bx->o)) > 1e-6 ||
		fabsf(ft_3_vector_dot(bx->lwh[2] - bx->o, bx->lwh[0] - bx->o)) > 1e-6)
		printf("INVALID CUBOID DESCRIPTION: PLANES ARE NOT PERPENDICULAR\n");
//		ft_error("Invalid cuboid: planes are not perpendicular");
	ft_init_box(bx);
	if (!ft_3_isnullpoint(o->rotate))
		ft_rotate_box(UINT32_MAX, bx, &o->rotate);
	if (!ft_3_isnullpoint(o->translate))
		ft_translate_box(UINT32_MAX, bx, &o->translate);
	return ((void *)bx);
}

void		ft_translate_box(Uint32 key, void *fig, t_vector *transl)
{
	t_box	*bx;
	int 	i;

	if (!fig)
		return ;
	bx = (t_box *)fig;
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
	bx->cntr += *transl;
	bx->o += *transl;
	i = -1;
	while (++i < BOX_FACES)
		ft_translate_plane(key, ((t_box *) fig)->face[i], transl);

}

void		ft_rotate_box(Uint32 key, void *fig, t_vector *rot)
{
	t_box	*bx;
	int 	i;
	float 	len;

	if (!fig)
		return ;
	bx = (t_box *)fig;
	if (key != UINT32_MAX)
		*rot = (t_vector){FLT_MIN, FLT_MIN, FLT_MIN};
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
	len = ft_3_vector_len(bx->dgnl);
	bx->dgnl = ft_3_vector_rotate(bx->dgnl, (*rot)[0], (*rot)[1], (*rot)[2]);
	t_vector new_max = bx->cntr + ft_3_vector_scale(ft_3_tounitvector(bx->dgnl),
			len * 0.5f);
	bx->o = bx->cntr - ft_3_vector_scale(ft_3_tounitvector(bx->dgnl),
													  len * 0.5f);
	i = -1;
	while (++i < BOX_FACES)
	{
		bx->face[i]->origin = i < 3 ?  bx->o : new_max;
		ft_rotate_plane(key, ((t_box *) fig)->face[i], rot);
	}
	bx->lwh[0] = ft_3_vector_rotate(bx->lwh[0], (*rot)[0], (*rot)[1], (*rot)[2]);
	bx->lwh[1] = ft_3_vector_rotate(bx->lwh[1], (*rot)[0], (*rot)[1], (*rot)[2]);
	bx->lwh[2] = ft_3_vector_rotate(bx->lwh[2], (*rot)[0], (*rot)[1], (*rot)[2]);
}

void		ft_scale_box(Uint32 key, void *fig, float *scale)
{
	t_box		*bx;
	t_vector	dir;
	float 		len;
	int 		i;

	if (!fig)
		return ;
	bx = (t_box *) fig;
	*scale = 1.0f;
	if (key == SDLK_z)
		*scale = (*scale + SCALE_F);
	else if (key == SDLK_x )
		*scale = (*scale - SCALE_F);
	dir = ft_3_tounitvector(bx->dgnl);
	len = ft_3_vector_len(bx->dgnl) * 0.5f * *scale;
	bx->o = bx->cntr - ft_3_vector_scale(dir, len);
	bx->dgnl = ft_3_vector_scale(dir, len * 2.0f);
	i = -1;
	while (++i < BOX_FACES)
	{
		bx->face[i]->origin = i < 3 ? bx->cntr - ft_3_vector_scale(dir, len)
									: bx->cntr + ft_3_vector_scale(dir, len);
		ft_scale_plane(key, ((t_box *) fig)->face[i], scale);
	}
	bx->lwh[0] = ft_3_vector_scale(bx->lwh[0], *scale);
	bx->lwh[1] = ft_3_vector_scale(bx->lwh[1], *scale);
	bx->lwh[2] = ft_3_vector_scale(bx->lwh[2], *scale);
}
