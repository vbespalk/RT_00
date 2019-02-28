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
	pln->origin_ini = (t_vector){ 0.0f, -500.0f, 0.0f };
	pln->norm_ini = (t_vector){ 0.0f, 1.0f, 0.0f };
	pln->w_ini = ft_3_nullpointnew();
	pln->h_ini = ft_3_nullpointnew();
	return (pln);
}


void		*ft_parse_plane(char **content, t_object *o)
{
	t_plane		*pln;

	o->ft_collide = ft_collide_plane;
	o->ft_is_reachable = ft_is_reachable_plane;
	o->ft_is_inside = ft_is_inside_plane;
	o->ft_get_norm = ft_get_norm_plane;
	o->ft_translate = ft_translate_plane;
	o->ft_rotate = ft_rotate_sphere;
	o->ft_scale = ft_scale_plane;
	pln = ft_planenew();
	ft_get_attr(content, "origin", (void *)(&(pln->origin_ini)), DT_POINT);
	ft_get_attr(content, "normal", (void *)(&(pln->norm_ini)), DT_POINT);
	ft_get_attr(content, "width", (void *)(&(pln->w_ini)), DT_POINT);
	ft_get_attr(content, "height", (void *)(&(pln->h_ini)), DT_POINT);
	pln->origin = pln->origin_ini;
	pln->w = pln->w_ini;
	pln->h = pln->h_ini;
	if (!ft_3_isnullpoint(pln->w) && !ft_3_isnullpoint(pln->h))
		pln->norm_ini = ft_3_vector_cross(pln->w - pln->origin, pln->h - pln->origin);
	if (ft_3_vector_len(pln->norm_ini) == 0.0)
		pln->norm_ini = (t_vector){ 0.0, 1.0, 0.0 };
	pln->norm_ini = ft_3_tounitvector(pln->norm_ini);
	// pln->norm_ini = ft_3_tounitvector(
	// 	ft_3_vector_rotate(
	// 		pln->norm_ini, o->rotate[0], o->rotate[1], o->rotate[2]));
	// pln->origin_ini += o->translate;
	pln->norm = pln->norm_ini;
	pln->origin = pln->origin_ini;

	o->refr = DEFAULT_REFR;

	return ((void *)pln);
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
	if (!ft_3_isnullpoint(pln->w) && !ft_3_isnullpoint(pln->h))
	{
		pln->w = pln->w_ini + *(transl);
		pln->h = pln->h_ini + *(transl);
	}
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
		(*rot)[1] -= ROTAT_F;
	else if (key == SDLK_RIGHT)
		(*rot)[1] += ROTAT_F;
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