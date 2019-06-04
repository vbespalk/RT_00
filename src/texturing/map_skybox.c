/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_skybox.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 15:28:55 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/10 15:29:56 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#define BIAS 1.000001f

static t_vector	ft_get_rst(t_vector vec, t_vector norm)
{
	t_vector	rst;

	rst = ZERO_PNT;
	if (fabsf(norm[0]) >= 0.7)
	{
		rst[0] = norm[0] > 0 ? 3 : 0;
		rst[1] = norm[0] > 0 ? ((vec[2]) + 1) * 0.5f :
			1 - ((vec[2]) + 1) * 0.5f;
		rst[2] = 1 - ((vec[1]) + 1) * 0.5f;
	}
	else if (fabsf(norm[1]) >= 0.7)
	{
		rst[0] = norm[1] > 0 ? 4 : 1;
		rst[1] = ((vec[2]) + 1) * 0.5f;
		rst[2] = norm[1] > 0 ? ((vec[0]) + 1) * 0.5f :
			1 - ((vec[0]) + 1) * 0.5f;
	}
	else if (fabsf(norm[2]) >= 0.7)
	{
		rst[0] = norm[2] > 0 ? 5 : 2;
		rst[1] = norm[2] > 0 ? 1 - ((vec[0]) + 1) * 0.5f :
			((vec[0]) + 1) * 0.5f;
		rst[2] = 1 - ((vec[1]) + 1) * 0.5f;
	}
	return (rst);
}

Uint32			ft_map_skybox(t_aabb *bbx, SDL_Surface *tex[6], t_vector hit)
{
	t_vector	rst;
	Uint32		col;
	int			xy[2];
	t_vector	vec;
	t_vector	norm;

	vec = (hit - bbx->cntr) /
		ft_3_fabsf_vector(ft_3_vector_scale(bbx->dgnl, 0.5f));
	norm = ft_3_tounitvector((t_vector){(int)(vec[0] * BIAS),
			(int)(vec[1] * BIAS), (int)(vec[2] * BIAS)});
	rst = ft_get_rst(vec, norm);
	xy[0] = (int)((tex[(int)rst[0]]->w - 1) * fabsf(rst[1]));
	xy[1] = (int)((tex[(int)rst[0]]->h - 1) * fabsf(rst[2]));
	if (!(IN_RANGE(xy[0], 0, tex[(int)rst[0]]->w - 1) &&
		IN_RANGE(xy[1], 0, tex[(int)rst[0]]->h - 1)))
		return (0xff0000);
	ft_memcpy(&col, (Uint32 *)tex[(int)rst[0]]->pixels + xy[1] *
		tex[(int)rst[0]]->w + xy[0], sizeof(Uint32));
	return (col);
}
