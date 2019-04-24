/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 13:25:05 by domelche          #+#    #+#             */
/*   Updated: 2018/08/23 13:26:05 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_cone		*ft_conenew(void)
{
	t_cone	*cone;

	cone = ft_smemalloc(sizeof(t_cone), "ft_conenew");
	cone->tan = 90;
	cone->minh = -FLT_MAX;
	cone->maxh = FLT_MAX;
	cone->r[0] = FLT_MIN;
	cone->r[1] = FLT_MIN;
	return (cone);
}

void		ft_cone_init(t_cone *cone)
{
	if (cone->minh > cone->maxh)
		ft_swap_float(&cone->minh, &cone->maxh);
	if (cone->minh == cone->maxh)
	{
		cone->minh = -FLT_MAX;
		cone->maxh = FLT_MAX;
	}
	if ((cone->tan = fabsf(cone->tan)) >= 175)
		cone->tan = (int)cone->tan % 175;
	cone->tan = cone->tan < 1 ? tanf(DEG_TO_RAD(1)) : tanf(DEG_TO_RAD(cone->tan / 2.0f));
	cone->r[0] = cone->minh != -FLT_MAX ? fabsf(cone->minh * cone->tan) : FLT_MIN;
	cone->r[1] = cone->maxh != FLT_MAX ? fabsf(cone->maxh * cone->tan) : FLT_MIN;
	printf("MINH %f, R %f, MAXH %f, R %f\n", cone->minh, cone->r[0], cone->maxh, cone->r[1]);
}

void		*ft_parse_cone(char **content, t_object *o)
{
	t_cone		*cone;

	o->ft_collide = ft_collide_cone;
	o->ft_is_reachable = ft_is_reachable_plane;
	o->ft_is_inside = ft_is_inside_cone;
	o->ft_get_norm = ft_get_norm_cone;
	o->ft_translate = ft_translate_cone;
	o->ft_rotate = ft_rotate_cone;
	o->ft_scale = ft_scale_cone;
	o->ft_mapping = ft_map_cone;
	o->ft_checker = ft_checker_cone;
	o->ft_procedural = ft_procedural_cone;
	cone = ft_conenew();
	ft_get_attr(content, "minh", (void *)(&(cone->minh)), DT_FLOAT);
	ft_get_attr(content, "maxh", (void *)(&(cone->maxh)), DT_FLOAT);
	ft_get_attr(content, "angle", (void *)(&(cone->tan)), DT_FLOAT);
	ft_cone_init(cone);
	ft_3_transform_mat(&(o->transform), o->translate, o->rotate, FLT_MIN);
	ft_3_inv_trans_mat(&(o->inverse), -o->translate, -o->rotate, FLT_MIN);
	printf("MATRIX\n");
	for (int i = 0; i < 4; ++i)
		printf("%f, %f, %f, %f\n", o->transform[i][0], o->transform[i][1], o->transform[i][2], o->transform[i][3]);
	printf("INVERTED\n");
	for (int i = 0; i < 4; ++i)
		printf("%f, %f, %f, %f\n", o->inverse[i][0], o->inverse[i][1], o->inverse[i][2], o->inverse[i][3]);
	return ((void *)cone);
}

void		ft_translate_cone(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m)
{
	t_cone *cone;

	if (!o)
		return ;
	cone = (t_cone *)o->fig;
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

void		ft_rotate_cone(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m)
{
	t_cone *cone;

	if (!o)
		return ;
	cone = (t_cone *)o->fig;
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

void		ft_scale_cone(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m)
{
	t_cone 	*cone;

	if (!o)
		return ;
	(void)tr_m;
	(void)inv_m;
	cone = (t_cone *)o->fig;
	if (key == SDLK_z)
		cone->tan = cone->tan * (1.0f + SCANG_F);
	else if (key == SDLK_x)
			cone->tan = cone->tan *  (1.0f - SCANG_F);
	cone->r[0] = cone->minh != -FLT_MAX ? fabsf(cone->minh * cone->tan) : FLT_MIN;
	cone->r[1] = cone->maxh != FLT_MAX ? fabsf(cone->maxh * cone->tan) : FLT_MIN;
//	ft_3_transform_mat(tr_m, cone->o, cone->v, FLT_MIN);
//	ft_3_inv_trans_mat(inv_m, -cone->o, -cone->v, FLT_MIN);
}
