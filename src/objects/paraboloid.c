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
	t_prbld	*par;

	par = ft_smemalloc(sizeof(t_prbld), "ft_prbldnew");
	par->o = (t_vector){0.0f, 0.0f, 0.0f};
	par->v = (t_vector){0.0f, 1.0f, 0.0f};
	par->r = 1.f;
	par->maxh = FLT_MAX;
	return (par);
}

char		*ft_parse_prbld(char **content, t_object *o)
{
	t_prbld		*par;
	t_vector	vert;

	o->ft_collide = ft_collide_prbld;
	o->ft_is_reachable = ft_is_reachable_prbld;
	o->ft_is_inside = ft_is_inside_prbld;
	o->ft_get_norm = ft_get_norm_prbld;
	o->ft_translate = ft_translate_prbld;
	o->ft_rotate = ft_rotate_prbld;
	o->ft_scale = ft_scale_prbld;
	par = ft_prbldnew();
	vert = (t_vector){FLT_MIN, FLT_MIN, FLT_MIN};
	ft_get_attr(content, "base", (void *)(&(par->o)), DT_POINT);
	ft_get_attr(content, "vert", (void *)(&(vert)), DT_POINT);
	ft_get_attr(content, "direction", (void *)(&(par->v)), DT_POINT);
	ft_get_attr(content, "radius", (void *)(&(par->r)), DT_FLOAT);
	ft_get_attr(content, "height", (void *)(&(par->maxh)), DT_FLOAT);
	if (!ft_3_isnullpoint(vert))
	{
		par->maxh = ft_3_vector_len(vert - par->o);
		par->v = ft_3_tounitvector(vert - par->o);
	}
	par->n = ft_3_nullpointnew();
	par->v = ft_3_tounitvector(par->v);
	printf("maxh %f\n", par->maxh);
	return ((void *)par);
}

void		ft_translate_prbld(Uint32 key, void *fig, t_vector *transl)
{
	t_prbld	*par;

	par = (t_prbld *)fig;
	*transl = (t_vector){0,0,0};
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
	par->o = par->o + *(transl);
}

void		ft_rotate_prbld(Uint32 key, void *fig, t_vector *rot)
{
	t_prbld *par;

	par = (t_prbld *)fig;
	*rot = (t_vector){0,0,0};
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
	par->v = ft_3_vector_rotate(par->v, (*rot)[0], (*rot)[1], (*rot)[2]);

}

void		ft_scale_prbld(Uint32 key, void *fig, float *scale)
{
	t_prbld *par;

	par = (t_prbld *)fig;
	*scale = 1;
	if (!fig)
		return ;
	if (key == SDLK_z)
	{
		*scale += SCALE_F;
		par->r = par->r * 1.1f * *scale;
		if (par->maxh != FLT_MAX)
			par->maxh = par->maxh * *scale;
	}
	else if (key == SDLK_x && *scale >= 0.0f)
	{
		*scale -= SCALE_F;
		par->r = par->r * 0.9f * *scale;
		if (par->maxh != FLT_MAX)
			par->maxh = par->maxh * *scale;
	}
	else
		*scale = 0;
}
