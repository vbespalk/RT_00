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
	cone->o = (t_vector){ 100.0f, 0.0f, 0.0f };
	cone->v = (t_vector){0.0f, 1.0f, 0.0f};
	cone->tan = 90;
	cone->minh = FLT_MIN;
	cone->maxh = FLT_MAX;
	cone->r[0] = FLT_MIN;
	cone->r[1] = FLT_MIN;
	return (cone);
}

void		ft_cone_init(t_cone *cone, t_vector base)
{
	cone->r[0] = fabsf(cone->r[0]);
	cone->r[1] = fabsf(cone->r[1]);
	if (cone->minh > cone->maxh)
		ft_swap_float(&cone->minh, &cone->maxh);
	if (cone->minh == cone->maxh)
		ft_bzero(&cone->r, sizeof(float) * 2);
	cone->tan = fabsf(cone->tan);
	if (cone->tan >= 175)
		cone->tan = (int)cone->tan % 175;
	cone->tan = (int)cone->tan == 180 ? 0.0f : tanf(DEG_TO_RAD(cone->tan / 2.0f));
	if (!ft_3_isnullpoint(base))
		cone->v = ft_3_tounitvector(base - cone->o);
	if (cone->r[1] == FLT_MIN)
	{
		cone->r[0] = fabsf(cone->minh * cone->tan);
		cone->r[1] = fabsf(cone->maxh * cone->tan);
	}
}

void		*ft_parse_cone(char **content, t_object *o)
{
	t_cone		*cone;
	t_vector	base;

	o->ft_collide = ft_collide_cone;
	o->ft_is_reachable = ft_is_reachable_plane;
	o->ft_is_inside = ft_is_inside_cone;
	o->ft_get_norm = ft_get_norm_cone;
	o->ft_translate = ft_translate_cone;
	o->ft_rotate = ft_rotate_cone;
	o->ft_scale = ft_scale_cone;
	cone = ft_conenew();
	base = (t_vector){FLT_MIN, FLT_MIN, FLT_MIN};
	ft_get_attr(content, "vert", (void *)(&(cone->o)), DT_POINT);
	ft_get_attr(content, "base_rad", (void *)(&(cone->r[1])), DT_FLOAT);
	ft_get_attr(content, "vert_rad", (void *)(&(cone->r[0])), DT_FLOAT);
	ft_get_attr(content, "base", (void *)(&base), DT_POINT);

	ft_get_attr(content, "direction", (void *)&(cone->v), DT_POINT);
	ft_get_attr(content, "min_height", (void *)(&(cone->minh)), DT_FLOAT);
	ft_get_attr(content, "max_height", (void *)(&(cone->maxh)), DT_FLOAT);
	ft_get_attr(content, "angle", (void *)(&(cone->tan)), DT_FLOAT);
	ft_cone_init(cone, base);
	return ((void *)cone);
}

void		ft_translate_cone(Uint32 key, void *fig, t_vector *transl)
{
	t_cone *cone;

	if (!fig)
		return ;
	cone = (t_cone *)fig;
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
	cone->o = cone->o + *(transl);
}

void		ft_rotate_cone(Uint32 key, void *fig, t_vector *rot)
{
	t_cone *cone;

	if (!fig)
		return ;
	cone = (t_cone *)fig;
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
	cone->v = ft_3_vector_rotate(cone->v, (*rot)[0], (*rot)[1], (*rot)[2]);
}

void		ft_scale_cone(Uint32 key, void *fig, float *scale)
{
	t_cone *cone;

	if (!fig)
		return ;
	cone = (t_cone *)fig;
	*scale = FLT_MIN;
	if (key == SDLK_z)
		*scale += SCALE_F;
	else if (key == SDLK_x && *scale - SCALE_F >= 0.0f)
		*scale -= SCALE_F;
	else
		*scale = 0;
	cone->tan = cone->tan * *scale;
	cone->maxh = cone->maxh * *scale * 0.5f;
	cone->minh = cone->minh / *scale * 0.5f;
}
