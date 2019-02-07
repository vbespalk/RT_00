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

t_plane		*ft_planenew(void)
{
	t_plane	*pln;

	pln = ft_smemalloc(sizeof(t_plane), "ft_planenew");
	pln->origin_ini = (t_vector){ 0.0, -1000.0, 0.0 };
	pln->norm_ini = (t_vector){ 0.0, 1.0, 0.0 };
	return (pln);
}


char		*ft_parse_plane(char *attr, t_scene *scn, unsigned int  id)
{
	t_object	*obj;
	t_plane		*pln;

	obj = ft_parse_object(attr);
	obj->id = id;
	obj->refr = 1.0;
	obj->ft_collide = ft_collide_plane;
	obj->ft_is_reachable = ft_is_reachable_plane;
	obj->ft_is_inside = ft_is_inside_plane;
	obj->ft_get_norm = ft_get_norm_plane;
	obj->ft_translate = ft_translate_plane;
	obj->ft_rotate = ft_rotate_plane;
	obj->ft_scale = ft_scale_plane;
	pln = ft_planenew();
	attr = ft_get_curve(attr, '{');
	ft_get_attr_in_scope(attr, "origin:", (void *)(&(pln->origin_ini)), PNT);
	ft_get_attr_in_scope(attr, "norm:", (void *)(&(pln->norm_ini)), PNT);
	if (ft_3_vector_len(pln->norm_ini) == 0.0)
		pln->norm_ini = (t_vector){ 0.0, 1.0, 0.0 };
	pln->norm_ini = ft_3_tounitvector(ft_3_vector_rotate(
			pln->norm_ini, obj->rotate[0], obj->rotate[1], obj->rotate[2]));
	pln->origin_ini += obj->translate;
	pln->norm = pln->norm_ini;
	pln->origin = pln->origin_ini;
	obj->fig = pln;
	ft_lstpush(&(scn->objs), ft_nodenew((void *)obj, sizeof(obj)));
	return (ft_get_curve(attr, '}'));
}

void		ft_translate_plane(Uint32 key, void *fig, t_vector *transl)
{
	t_plane *pln;

	pln = (t_plane *)fig;
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
	pln->origin = pln->origin_ini + *(transl);
}

void		ft_rotate_plane(Uint32 key, void *fig, t_vector *rot)
{
	t_plane *pln;

	pln = (t_plane *)fig;
	if (!fig)
		return ;
	if (key == SDLK_DOWN)
		(*rot)[2] += ROTAT_F;
	else if (key == SDLK_UP)
		(*rot)[2] -= ROTAT_F;
	else if (key == SDLK_LEFT)
		(*rot)[1] += ROTAT_F;
	else if (key == SDLK_RIGHT)
		(*rot)[1] -= -ROTAT_F;
	else if (key == SDLK_PAGEDOWN)
		(*rot)[0] += ROTAT_F;
	else if (key == SDLK_PAGEUP)
		(*rot)[0] -= ROTAT_F;
	pln->norm = ft_3_vector_rotate(pln->norm_ini, (*rot)[0], (*rot)[1], (*rot)[2]);
}

void		ft_scale_plane(Uint32 key, void *fig, float *scale)
{
	t_plane *pln;

	pln = (t_plane *)fig;
	(void)key;
	if (!fig)
		return ;
}