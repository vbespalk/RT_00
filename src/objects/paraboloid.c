/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paraboloid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 18:12:39 by vbespalk          #+#    #+#             */
/*   Updated: 2019/02/19 18:12:42 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_prbld		*ft_prbldnew(void)
{
	t_prbld	*prbl;

	prbl = ft_smemalloc(sizeof(t_prbld), "ft_prbldnew");
	prbl->r = 1.f;
	prbl->maxh = FLT_MAX;
	return (prbl);
}

char		*ft_parse_prbld(char **content, t_object *o)
{
	t_prbld		*prbl;

	o->ft_collide = ft_collide_prbld;
	o->ft_is_reachable = ft_is_reachable_prbld;
	o->ft_is_inside = ft_is_inside_prbld;
	o->ft_get_norm = ft_get_norm_prbld;
	o->ft_translate = ft_translate_prbld;
	o->ft_rotate = ft_rotate_prbld;
	o->ft_scale = ft_scale_prbld;
	o->ft_mapping = ft_map_prbld;
	o->ft_checker = ft_checker_prbld;
	o->ft_procedural = ft_procedural_prbld;
	prbl = ft_prbldnew();
	ft_get_attr(content, "radius", (void *)(&(prbl->r)), DT_FLOAT);
	ft_get_attr(content, "height", (void *)(&(prbl->maxh)), DT_FLOAT);
	prbl->maxh = prbl->maxh == FLT_MAX ? FLT_MAX : prbl->maxh / prbl->r;
//	prbl->tex_h = prbl->maxh;
	ft_3_transform_mat(&(o->transform),o->translate, o->rotate, prbl->r);
	ft_3_inv_trans_mat(&(o->inverse), -o->translate, -o->rotate, 1.0f / prbl->r);
//	ft_3_transform_mat(&(o->transform), o->translate, o->rotate, FLT_MIN);
//	ft_3_inv_trans_mat(&(o->inverse), -o->translate, -o->rotate, FLT_MIN);
	printf("RAD %f\n", prbl->r);
	printf("maxh %f\n", prbl->maxh);
	return ((void *)prbl);
}

void		ft_translate_prbld(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m)
{
	t_prbld	*prbl;

	if (!o)
		return ;
	prbl = (t_prbld *)o->fig;
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
	ft_3_transform_mat(tr_m, o->translate, o->rotate, prbl->r);
	ft_3_inv_trans_mat(inv_m, -o->translate, -o->rotate, 1.f / prbl->r);
//	ft_3_transform_mat(tr_m, o->translate, o->rotate, FLT_MIN);
//	ft_3_inv_trans_mat(inv_m, -o->translate, -o->rotate, FLT_MIN);
}

void		ft_rotate_prbld(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m)
{
	t_prbld *prbl;

	if (!o)
		return ;
	prbl = (t_prbld *)o->fig;
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
	ft_3_transform_mat(tr_m, o->translate, o->rotate, prbl->r);
	ft_3_inv_trans_mat(inv_m, -o->translate, -o->rotate, 1.f / prbl->r);
//	ft_3_transform_mat(tr_m, o->translate, o->rotate, FLT_MIN);
//	ft_3_inv_trans_mat(inv_m, -o->translate, -o->rotate, FLT_MIN);
}

void		ft_scale_prbld(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m)
{
	t_prbld *prbl;

	if (!o)
		return ;
	prbl = (t_prbld *)o->fig;
	float scale = 1;
	if (key == SDLK_z && prbl->r * scale < 800000.f)
	{
		scale += SCALE_F;
		prbl->r = prbl->r * scale;
		prbl->maxh = prbl->maxh == FLT_MAX ? FLT_MAX :  prbl->maxh / scale;
	}
	else if (key == SDLK_x && prbl->r * scale >= 1.0f)
	{
		scale -= SCALE_F;
		prbl->r = prbl->r * scale;
		prbl->maxh = prbl->maxh == FLT_MAX ? FLT_MAX :  prbl->maxh / scale;
	}
	else
		scale = 0;
	printf("RAD %f\n", prbl->r);
	ft_3_transform_mat(tr_m, o->translate, o->rotate, prbl->r);
	ft_3_inv_trans_mat(inv_m, -o->translate, -o->rotate, 1.f / prbl->r);
////	ft_3_transform_mat(tr_m, o->translate, o->rotate, FLT_MIN);
////	ft_3_inv_trans_mat(inv_m, -o->translate, -o->rotate, FLT_MIN);
}
