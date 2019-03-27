/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                             :+:      :+:    :+:   */
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
	clnd->o = (t_vector){ 0.0f, 0.0f, -200.0f };
	clnd->v = (t_vector){ 0.0f, 1.0f, 0.0f };
	clnd->r = 10.0f;
	clnd->maxh = FLT_MAX;
	return (clnd);
}

void		*ft_parse_cylinder(char **content, t_object *o)
{
	t_cylinder		*clnd;
	t_vector 		vert;

	vert = (t_vector){FLT_MIN, FLT_MIN, FLT_MIN};
	o->ft_collide = ft_collide_cylinder;
	o->ft_is_reachable = ft_is_reachable_plane;
	o->ft_is_inside = ft_is_inside_cylinder;
	o->ft_get_norm = ft_get_norm_cylinder;
	o->ft_translate = ft_translate_cylinder;
	o->ft_rotate = ft_rotate_cylinder;
	o->ft_scale = ft_scale_cylinder;
	o->ft_mapping = ft_map_clndr;
	o->ft_checker = ft_checker_cyl;
//	o->ft_mapping = NULL;
	clnd = ft_cylindernew();
	ft_get_attr(content, "base", (void *)(&(clnd->o)), DT_POINT);
	ft_get_attr(content, "direction", (void *)(&(clnd->v)), DT_POINT);
	ft_get_attr(content, "radius", (void *)(&(clnd->r)), DT_FLOAT);
	ft_get_attr(content, "height", (void *)(&(clnd->maxh)), DT_FLOAT);
	ft_get_attr(content, "vert", (void *)(&(vert)), DT_POINT);
	ft_get_attr(content, "base_rad", (void *)(&(clnd->r)), DT_FLOAT);
	if (!ft_3_isnullpoint(vert))
	{
		clnd->maxh = ft_3_vector_len(vert - clnd->o);
		clnd->v =vert - clnd->o;
	}
	clnd->v = ft_3_tounitvector(clnd->v);
	return ((void *)clnd);
}

void		ft_translate_cylinder(Uint32 key, void *fig, t_vector *transl)
{
	t_cylinder *clnd;

	clnd = (t_cylinder *)fig;
	if (!fig)
		return ;
	*transl = (t_vector){0.0f,0.0f,0.0f};
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
	clnd->o = clnd->o + *(transl);
}

void		ft_rotate_cylinder(Uint32 key, void *fig, t_vector *rot)
{
	t_cylinder *clnd;

	if (!fig)
		return ;
	clnd = (t_cylinder *)fig;
	*rot = (t_vector){FLT_MIN,FLT_MIN,FLT_MIN};
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
	clnd->v = ft_3_vector_rotate(clnd->v, (*rot)[0], (*rot)[1], (*rot)[2]);
}

void		ft_scale_cylinder(Uint32 key, void *fig, float *scale)
{
	t_cylinder *clnd;

	clnd = (t_cylinder *)fig;
	*scale = 1.0f;
	if (!fig)
		return ;
	if (key == SDLK_z)
		*scale += SCALE_F;
	else if (key == SDLK_x && *scale - SCALE_F >= 0.0f)
		*scale -= SCALE_F;
	else
		*scale = 0;
	clnd->r = clnd->r * *scale;
	if (clnd->maxh != FLT_MAX)
		clnd->maxh = clnd->maxh * *scale;
}
