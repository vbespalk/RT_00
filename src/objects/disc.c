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
	dsk->radius_ini = 1500.0f;
	return (dsk);
}


// char		*ft_parse_plane(char *attr, t_scene *scn, unsigned int  id)
// {
// 	t_object	*obj;
// 	t_disk		*dsk;

// 	// printf("here\n");
// 	obj = ft_parse_object(attr);
// 	obj->id = id;
// 	obj->refr = 1.0;
// 	obj->ft_collide = ft_collide_disk;
// 	obj->ft_is_reachable = ft_is_reachable_disk;
// 	obj->ft_is_inside = ft_is_inside_disk;
// 	obj->ft_get_norm = ft_get_norm_disk;
// 	obj->ft_translate = ft_translate_disk;
// 	obj->ft_rotate = ft_rotate_disk;
// 	obj->ft_scale = ft_scale_disk;
// 	dsk = ft_disknew();
// 	attr = ft_get_curve(attr, '{');
// 	ft_get_attr_in_scope(attr, "origin:", (void *)(&(dsk->origin_ini)), PNT);
// 	ft_get_attr_in_scope(attr, "norm:", (void *)(&(dsk->norm_ini)), PNT);
// 	if (ft_3_vector_len(dsk->norm_ini) == 0.0)
// 		dsk->norm_ini = (t_vector){ 0.0, 1.0, 0.0 };
// 	dsk->norm_ini = ft_3_tounitvector(ft_3_vector_rotate(
// 			dsk->norm_ini, obj->rotate[0], obj->rotate[1], obj->rotate[2]));
// 	dsk->origin_ini += obj->translate;
// 	dsk->norm = dsk->norm_ini;
// 	dsk->origin = dsk->origin_ini;
// 	dsk->radius = dsk->radius_ini;
// 	obj->fig = dsk;
// 	ft_lstpush(&(scn->objs), ft_nodenew((void *)obj, sizeof(obj)));
// 	return (ft_get_curve(attr, '}'));
// }

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
	dsk->radius = dsk->radius_ini * *scale;
}