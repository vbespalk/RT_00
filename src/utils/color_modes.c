/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_modes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 18:38:12 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/13 18:38:20 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#define RED_CH 0.212671
#define GRE_CH 0.715160
#define BLU_CH 0.072169

t_color		ft_grayscale_px(t_color in_col)
{
	Uint8	v;
	t_color	col;

	v = (Uint8)(RED_CH * in_col.argb[0] + GRE_CH *
			in_col.argb[1] + BLU_CH * in_col.argb[2]);
	col.argb[0] = v;
	col.argb[1] = v;
	col.argb[2] = v;
	col.argb[3] = in_col.argb[3];
	return (col);
}

t_color		ft_sepia_px(t_color in_col)
{
	t_color col;

	col.argb[0] = (Uint8)L_X(in_col.argb[0] * .393 +
			in_col.argb[1] * .769 + in_col.argb[2] * .189, 0xFF);
	col.argb[1] = (Uint8)L_X(in_col.argb[0] * .349 +
			in_col.argb[1] * .686 + in_col.argb[2] * .168, 0xFF);
	col.argb[2] = (Uint8)L_X(in_col.argb[0] * .272 +
			in_col.argb[1] * .534 + in_col.argb[2] * .131, 0xFF);
	col.argb[3] = in_col.argb[3];
	return (col);
}

t_color		ft_negative_px(t_color in_col)
{
	t_color col;

	col.argb[0] = (Uint8)(0xFF - in_col.argb[0]);
	col.argb[1] = (Uint8)(0xFF - in_col.argb[1]);
	col.argb[2] = (Uint8)(0xFF - in_col.argb[2]);
	col.argb[3] = in_col.argb[3];
	return (col);
}

void		ft_col_mode(t_sdl *sdl, Sint32 id)
{
	t_color col;
	int		x;
	int		y;

	y = -1;
	while (++y < sdl->scr_hei && (x = -1))
	{
		while (++x < sdl->rt_wid)
		{
			col.val = sdl->pixels[y * sdl->rt_wid + x];
			if (id == MD_GRAYSCALE)
				col = ft_grayscale_px(col);
			if (id == MD_SEPIA)
				col = ft_sepia_px(col);
			if (id == MD_NEGATIVE)
				col = ft_negative_px(col);
			if (id == MD_INVERTED)
				col = ft_invert_px(col);
			sdl->pixels[y * sdl->rt_wid + x] = col.val;
		}
	}
}

t_color		ft_px_mode(t_color col, t_mode *mode)
{
	while (mode)
	{
		if (mode->id == MD_GRAYSCALE)
			col = ft_grayscale_px(col);
		if (mode->id == MD_SEPIA)
			col = ft_sepia_px(col);
		if (mode->id == MD_NEGATIVE)
			col = ft_negative_px(col);
		if (mode->id == MD_INVERTED)
			col = ft_invert_px(col);
		mode = mode->next;
	}
	return (col);
}
