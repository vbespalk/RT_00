/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   illumination.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 13:25:05 by domelche          #+#    #+#             */
/*   Updated: 2018/08/23 13:26:31 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ft_illuminate_with(t_thrarg *parg, t_coll *coll, t_light *l)
{
	float		nl_cos;
	float		bright_coef;
	float		illum;
	float		cl_len;
	t_vector	ldir;

	ldir = (l->type == L_POINT)
		? ft_3_tounitvector(l->origin - coll->coll_pnt)
		: ft_3_vector_invert(l->direct);
	nl_cos = ft_3_vector_cos(coll->norm, ldir);
	if (nl_cos >= 0)
	{
		illum = ft_get_illumination(
			parg->e->scn, coll->coll_pnt + ft_3_vector_scale(coll->norm, SHIFT),
			ldir, l);
		if (illum == 0.0f)
			return ;
		cl_len = (l->type == L_POINT)
			? ft_3_point_point_dist(coll->coll_pnt, l->origin)
			: 10000.0f;
		bright_coef = (cl_len == 0.0f)
			? l->bright
			: l->bright * illum * nl_cos / powf(cl_len / BRIGHT_UNIT, 2);
		ft_affect_illumination(coll, l, ldir, bright_coef);
	}
}

void		ft_illuminate(t_thrarg *parg, t_coll *coll)
{
	t_list		*node;
	t_light		*l;

	coll->illum_color.val = 0;
	coll->phong_color.val = 0;
	coll->phong = 0.0;
	node = parg->e->scn->lights;
	while (node)
	{
		l = (t_light *)(node->content);
		ft_illuminate_with(parg, coll, l);
		node = node->next;
	}
}
