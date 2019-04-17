/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 13:25:05 by domelche          #+#    #+#             */
/*   Updated: 2018/08/23 13:27:24 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_disk		*ft_disknew(void)
{
	t_disk	*dsk;

	dsk = ft_smemalloc(sizeof(t_disk), "ft_disknew");
	dsk->out_r = FLT_MAX;
	dsk->in_r = FLT_MIN;
	return (dsk);
}

char		*ft_parse_disk(char **content, t_object *o)
{
	t_object	*obj;
	t_disk		*dsk;

	o->ft_collide = ft_collide_disk;
	o->ft_is_reachable = ft_is_reachable_disk;
	o->ft_is_inside = ft_is_inside_disk;
	o->ft_get_norm = ft_get_norm_disk;
	o->ft_translate = ft_translate_disk;
	o->ft_rotate = ft_rotate_disk;
	o->ft_scale = ft_scale_disk;
	o->ft_mapping = NULL;
	o->ft_checker = NULL;
	o->ft_procedural = ft_procedural_dsc;
	dsk = ft_disknew();
	ft_get_attr(content, "inner_radius", (void *)(&(dsk->in_r)), DT_FLOAT);
	ft_get_attr(content, "outer_radius", (void *)(&(dsk->out_r)), DT_FLOAT);
	if (dsk->in_r > dsk->out_r)
		ft_swap_float(&dsk->in_r, &dsk->out_r);
	dsk->sq_in_r = dsk->in_r * dsk->in_r;
	dsk->sq_out_r = dsk->out_r * dsk->out_r;
	printf(" INN %f\n OUTER %f\n",  dsk->sq_in_r, dsk->sq_out_r);
	ft_3_transform_mat(&(o->transform), o->translate, o->rotate, FLT_MIN);
	ft_3_inv_trans_mat(&(o->inverse), -o->translate, -o->rotate, FLT_MIN);
	printf("MATRIX\n");
	for (int i = 0; i < 4; ++i)
		printf("%f, %f, %f, %f\n", o->transform[i][0], o->transform[i][1], o->transform[i][2], o->transform[i][3]);
	printf("INVERTED\n");
	for (int i = 0; i < 4; ++i)
		printf("%f, %f, %f, %f\n", o->inverse[i][0], o->inverse[i][1], o->inverse[i][2], o->inverse[i][3]);
	return ((void *)dsk);
}

void		ft_translate_disk(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m)
{
	t_disk *dsk;

	if (!o)
		return ;
	dsk = (t_disk *)o->fig;
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

void		ft_rotate_disk(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m)
{
	t_disk *dsk;

	if (!o)
		return ;
	dsk = (t_disk *)o->fig;
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
	printf("ROT %f,%f,%f\n", RAD_TO_DEG(o->rotate[0]), RAD_TO_DEG(o->rotate[1]), RAD_TO_DEG(o->rotate[2]));
	ft_3_transform_mat(tr_m, o->translate, o->rotate, FLT_MIN);
	ft_3_inv_trans_mat(inv_m, -o->translate, -o->rotate, FLT_MIN);
}

void		ft_scale_disk(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m)
{
	t_disk *dsk;

	if (!o)
		return ;
	dsk = (t_disk *)o->fig;
	float scale = 1;
	if (key == SDLK_z)
		scale += SCALE_F;
	else if (key == SDLK_x && scale >= 0.0f)
		scale -= SCALE_F;
	else
		scale = 0;
	dsk->in_r *= scale;
	dsk->out_r *= scale;
	dsk->sq_in_r = dsk->in_r * dsk->in_r;
	dsk->sq_out_r = dsk->out_r * dsk->out_r;
	ft_3_transform_mat(tr_m, o->translate, o->rotate, FLT_MIN);
	ft_3_inv_trans_mat(inv_m, -o->translate, -o->rotate, FLT_MIN);
}
