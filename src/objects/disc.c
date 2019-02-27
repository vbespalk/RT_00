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
	dsk->origin_ini = (t_vector){ 100.0, 0.0, 0.0 };
	dsk->norm_ini = (t_vector){ 1.0, 0.0, 0.0 };
	dsk->out_r_ini = FLT_MAX;
	dsk->in_r_ini = FLT_MIN;
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
	dsk = ft_disknew();
	ft_get_attr(content, "origin", (void *)(&(dsk->origin_ini)), DT_POINT);
	ft_get_attr(content, "normal", (void *)(&(dsk->norm_ini)), DT_POINT);
	ft_get_attr(content, "inner_radius", (void *)(&(dsk->in_r_ini)), DT_FLOAT);
	ft_get_attr(content, "outer_radius", (void *)(&(dsk->out_r_ini)), DT_FLOAT);
	if (ft_3_vector_len(dsk->norm_ini) == 0.0)
		dsk->norm_ini = (t_vector){ 0.0, 1.0, 0.0 };
	if (dsk->in_r_ini > dsk->out_r_ini)
		ft_swap_float(&dsk->in_r_ini, &dsk->out_r_ini);
	dsk->norm_ini = ft_3_tounitvector(dsk->norm_ini);
	dsk->norm = dsk->norm_ini;
	dsk->origin = dsk->origin_ini;
	dsk->in_r = dsk->in_r_ini;
	dsk->out_r = dsk->out_r_ini;
	printf("rad in %f out %f\n", dsk->in_r, dsk->out_r);
	return ((void *)dsk);
}

void		ft_translate_disk(Uint32 key, void *fig, t_vector *transl)
{
	t_disk *dsk;

	dsk = (t_disk *)fig;
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
	dsk->origin = dsk->origin_ini + *(transl);
}

void		ft_rotate_disk(Uint32 key, void *fig, t_vector *rot)
{
	t_disk *dsk;

	dsk = (t_disk *)fig;
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
	dsk->norm = ft_3_vector_rotate(dsk->norm_ini, (*rot)[0], (*rot)[1], (*rot)[2]);
}

void		ft_scale_disk(Uint32 key, void *fig, float *scale)
{
	t_disk *dsk;

	if (!fig)
		return ;
	dsk = (t_disk *)fig;
	if (key == SDLK_z)
		*scale += SCALE_F;
	else if (key == SDLK_x && *scale >= 0.0f)
		*scale -= SCALE_F;
	else
		*scale = 0;
	dsk->in_r = dsk->in_r_ini * *scale;
	dsk->out_r = dsk->out_r_ini * *scale;
}