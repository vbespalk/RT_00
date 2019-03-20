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
	pln->dir_wh[0] = ft_3_nullpointnew();
	pln->dir_wh[1] = ft_3_nullpointnew();
	pln->len_wh[0] = FLT_MIN;
	pln->len_wh[1] = FLT_MIN;
	pln->dgnl = ft_3_nullpointnew();
	pln->cntr = ft_3_nullpointnew();
	return (pln);
}

static void		init_quad(t_plane *pln)
{
	if(ft_3_isnullpoint(pln->w_ini) || ft_3_isnullpoint(pln->h_ini) ||
		fabsf(ft_3_vector_dot(pln->w_ini - pln->origin, pln->h_ini - pln->origin)) > 1e-6)
		return ;
	pln->len_wh[0] = ft_3_vector_len(pln->w_ini - pln->origin);
	pln->len_wh[1] = ft_3_vector_len(pln->h_ini - pln->origin);
	pln->dir_wh[0] = ft_3_tounitvector(pln->w_ini - pln->origin);
	pln->dir_wh[1] = ft_3_tounitvector(pln->h_ini - pln->origin);
	pln->dgnl = pln->w_ini + pln->h_ini - ft_3_vector_scale(pln->origin, 2.0f);
	pln->cntr = pln->origin + ft_3_vector_scale(ft_3_tounitvector(pln->dgnl),
			ft_3_vector_len(pln->dgnl) * 0.5f);
	pln->norm_ini = ft_3_vector_cross(pln->dir_wh[0], pln->dir_wh[1]);
}

void		*ft_parse_plane(char **content, t_object *o)
{
	t_plane		*pln;

	o->ft_collide = ft_collide_plane;
	o->ft_is_reachable = ft_is_reachable_plane;
	o->ft_is_inside = ft_is_inside_plane;
	o->ft_get_norm = ft_get_norm_plane;
	o->ft_translate = ft_translate_plane;
	o->ft_rotate = ft_rotate_plane;
	o->ft_scale = ft_scale_plane;
	o->ft_mapping = ft_map_plane;
	pln = ft_planenew();
	ft_get_attr(content, "origin", (void *)(&(pln->origin_ini)), DT_POINT);
	ft_get_attr(content, "norm", (void *)(&(pln->norm_ini)), DT_POINT);
	ft_get_attr(content, "width", (void *)(&(pln->w_ini)), DT_POINT);
	ft_get_attr(content, "height", (void *)(&(pln->h_ini)), DT_POINT);
	pln->origin = pln->origin_ini;
	init_quad(pln);
	if (ft_3_vector_len(pln->norm_ini) == 0.0)
		pln->norm_ini = (t_vector){ 0.0, 1.0, 0.0 };
	pln->norm = ft_3_tounitvector(pln->norm_ini);
	if (!ft_3_isnullpoint(o->rotate))
		ft_rotate_plane(UINT32_MAX, pln, &o->rotate);
	if (!ft_3_isnullpoint(o->translate))
		ft_translate_plane(UINT32_MAX, pln, &o->translate);
	return ((void *)pln);
}

void		ft_translate_plane(Uint32 key, void *fig, t_vector *transl)
{
	t_plane *pln;

	if (!fig)
		return ;
	pln = (t_plane *)fig;
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
	pln->origin += *(transl);
	if (!ft_3_isnullpoint(pln->cntr))
		pln->cntr += *(transl);
//	printf("AFTER_TRANSLATION DOT %f \n",ft_3_vector_dot(pln->dir_wh[0], pln->dir_wh[1]));
}

void		ft_rotate_plane(Uint32 key, void *fig, t_vector *rot)
{
	t_plane		*pln;

	if (!fig)
		return ;
	pln = (t_plane *)fig;
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
	if (pln->len_wh[0] == FLT_MIN || pln->len_wh[1] == FLT_MIN)
	{
		pln->norm = ft_3_vector_rotate(pln->norm, (*rot)[0], (*rot)[1], (*rot)[2]);
		return ;
	}
	if (!ft_3_isnullpoint(pln->cntr))
	{
		pln->origin = pln->cntr - ft_3_vector_rotate(pln->cntr - pln->origin,
				(*rot)[0], (*rot)[1], (*rot)[2]);
		pln->dgnl = ft_3_vector_rotate(pln->dgnl, (*rot)[0], (*rot)[1], (*rot)[2]);
	}
	pln->dir_wh[0] = ft_3_tounitvector(ft_3_vector_rotate(pln->dir_wh[0], (*rot)[0], (*rot)[1], (*rot)[2]));
	pln->dir_wh[1] = ft_3_tounitvector(ft_3_vector_rotate(pln->dir_wh[1], (*rot)[0], (*rot)[1], (*rot)[2]));
	pln->norm = ft_3_tounitvector(ft_3_vector_cross(pln->dir_wh[0], pln->dir_wh[1]));
//	printf("AFTER_ROTATING DOT %f \n",ft_3_vector_dot(pln->dir_wh[0], pln->dir_wh[1]));
}

void		ft_scale_plane(Uint32 key, void *fig, float *scale)
{
	t_plane		*pln;
	t_vector	dir;
	float 		len;

	if (!fig)
		return ;
	pln = (t_plane *)fig;
	if (pln->len_wh[0] == FLT_MIN || pln->len_wh[1] == FLT_MIN)
		return;
	*scale = 1.0f;
	if (key == SDLK_z)
		*scale += SCALE_F;
	else if (key == SDLK_x )
		*scale -= SCALE_F;
//	else
//		*scale = 0;
	dir = ft_3_tounitvector(pln->dgnl);
	len = ft_3_vector_len(pln->dgnl) * *scale;
	if (!ft_3_isnullpoint(pln->cntr))
	{
		pln->origin = pln->cntr - ft_3_vector_scale(dir, 0.5f * len);
		pln->dgnl = ft_3_vector_scale(dir, len);
	}
	pln->len_wh[0] *= (*scale);
	pln->len_wh[1] *= (*scale);
//	printf("AFTER SCALING DOT %f\n",ft_3_vector_dot(pln->dir_wh[0], pln->dir_wh[1]));
}
