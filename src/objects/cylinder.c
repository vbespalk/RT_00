/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 13:25:05 by domelche          #+#    #+#             */
/*   Updated: 2018/08/23 13:26:05 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_cylinder		*ft_cylindernew(void)
{
	t_cylinder	*clnd;

	clnd = ft_smemalloc(sizeof(t_cylinder), "ft_cylindernew");
	clnd->r = 10.0f;
	clnd->maxh = FLT_MAX;
	return (clnd);
}

void		*ft_parse_cylinder(char **content, t_object *o)
{
	t_cylinder		*clnd;

	o->ft_collide = ft_collide_cylinder;
	o->ft_is_reachable = ft_is_reachable_plane;
	o->ft_is_inside = ft_is_inside_cylinder;
	o->ft_get_norm = ft_get_norm_cylinder;
	o->ft_translate = ft_translate_cylinder;
	o->ft_rotate = ft_rotate_cylinder;
	o->ft_scale = ft_scale_cylinder;
	o->ft_scale_height = ft_scale_hei_cylinder;
	o->ft_mapping = ft_map_clndr;
	o->ft_checker = ft_checker_cyl;
    o->ft_procedural = ft_procedural_cyl;
	clnd = ft_cylindernew();
	ft_get_attr(content, "radius", (void *)(&(clnd->r)), DT_FLOAT);
	ft_get_attr(content, "height", (void *)(&(clnd->maxh)), DT_FLOAT);
	if (clnd->maxh != FLT_MAX)
		clnd->maxh /= clnd->r * 2.0f;
	ft_3_transform_mat(&(o->transform), o->translate, o->rotate, clnd->r);
	ft_3_inv_trans_mat(&(o->inverse), -o->translate, -o->rotate, 1.0f / clnd->r);
	printf("MAXH %f\n", clnd->maxh);
	return ((void *)clnd);
}

int	    	ft_translate_cylinder(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m)
{
	t_cylinder *clnd;

	if (!o)
		return (0);
	clnd = (t_cylinder *)o->fig;
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
	ft_3_transform_mat(tr_m, o->translate, o->rotate, clnd->r);
	ft_3_inv_trans_mat(inv_m, -o->translate, -o->rotate, 1.0f / clnd->r);
    return (1);
}

int	    	ft_rotate_cylinder(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m)
{
	t_cylinder *clnd;

	if (!o)
		return (0);
	clnd = (t_cylinder *)o->fig;
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
	ft_3_transform_mat(tr_m, o->translate, o->rotate, clnd->r);
	ft_3_inv_trans_mat(inv_m, -o->translate, -o->rotate, 1.0f / clnd->r);
    return (1);
}

int	    	ft_scale_cylinder(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m)
{
	t_cylinder *clnd;

	if (!o)
		return (0);
	clnd = (t_cylinder *)o->fig;
	float scale = 1.0f;
	if (key == SDLK_z)
		scale += SCALE_F;
	else if (key == SDLK_x && scale - SCALE_F >= 0.0f)
		scale -= SCALE_F;
	else
		scale = 0;
	clnd->r = clnd->r * scale > 900000 ? clnd->r : clnd->r * scale;
	if (clnd->maxh != FLT_MAX)
		clnd->maxh = clnd->maxh / scale;
	printf("RAD %f maxh %f\n", clnd->r, clnd->maxh);
	ft_3_transform_mat(tr_m, o->translate, o->rotate, clnd->r);
	ft_3_inv_trans_mat(inv_m, -o->translate, -o->rotate, 1.0f / clnd->r);
    return (1);
}

int	    	ft_scale_hei_cylinder(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m)
{
	t_cylinder *clnd;

	if (!o)
		return (0);
	clnd = (t_cylinder *)o->fig;
	float scale = 1;
	if (key == SDLK_r)
	{
		scale += SCALE_F;
		clnd->maxh = clnd->maxh == FLT_MAX ? FLT_MAX :  clnd->maxh * scale;
	}
	else if (key == SDLK_t)
	{
		scale -= SCALE_F;
		clnd->maxh = clnd->maxh == FLT_MAX ? FLT_MAX :  clnd->maxh * scale;
	}
	else
		scale = 0;
	printf("HEI %f RAD %f\n", clnd->maxh, clnd->r);
    return (1);
}