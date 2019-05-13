/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inv_mode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 16:18:02 by vbespalk          #+#    #+#             */
/*   Updated: 2019/02/05 16:18:05 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Value S,V must be in range [0,1], H must be in range [0, 360]
*/

t_vector	hsv_to_rgb(float h, float s, float v)
{
	t_vector	pqt;
	t_vector	rgb;
	float		fract;

	h = h == 360.0f ? 0 : h / 60.0f;
	fract = h - floorf(h);
	pqt = (t_vector){v * (1.0 - s), v * (1.0 - s * fract),
				  v * (1.0 - s * (1.0 - fract))};
	if (s <= 0.0f)
		rgb = (t_vector) {v * 255, v * 255, v * 255};
	else if ((int)h == 0)
		rgb = (t_vector){v * 255, pqt[2] * 255, pqt[0] * 255};
	else if ((int)h == 1)
		rgb = (t_vector){pqt[1] * 255, v * 255, pqt[0] * 255};
	else if ((int)h == 2)
		rgb = (t_vector){pqt[0] * 255, v * 255, pqt[2] * 255};
	else if ((int)h == 3)
		rgb = (t_vector){pqt[0] * 255, pqt[1] * 255, v * 255};
	else if ((int)h == 4)
		rgb = (t_vector){pqt[2] * 255, pqt[0] * 255, v * 255};
	else
		rgb = (t_vector){v * 255, pqt[0] * 255, pqt[1] * 255};
	return (rgb);
}

/*
** Value R,G,B must be in range [0,1]
*/

t_vector	rgb_to_hsv(float r, float g, float b)
{
    float 		delta;
    t_vector	hsv;

	hsv = ZERO_PNT;
	hsv[1] = MIN_V(r, MIN_V(g, b));
    hsv[2] = MAX_V(r, MAX_V(g, b));
    delta = hsv[2] - hsv[1];
    if (delta == 0)
    	hsv[0] = 0;
    else if (hsv[2] == r)
        hsv[0] = 60.0f * ((g - b) / delta);
    else if (hsv[2] == g)
        hsv[0] = 60.0f * (2.0f + (b - r) / delta);
    else if (hsv[2] == b)
        hsv[0] = 60.0f * (4.0f + (r - g) / delta);
    if (hsv[0] < 0)
        hsv[0] += 360;
    hsv[1] = (hsv[2] == 0.0f) ? 0 : delta / hsv[2];
    return (hsv);
}

t_color		ft_invert_px(t_color in_col)
{
	t_vector	hsv;
	t_vector	rgb;
	t_color		col;

	hsv = rgb_to_hsv(in_col.argb[0] / 255.f, in_col.argb[1] / 255.f,
			in_col.argb[2] / 255.f);
	hsv[0] = (float)((int)(hsv[0] + 180.0f + .5) % 360);
	rgb = hsv_to_rgb(hsv[0], hsv[1], hsv[2]);
	col.argb[0] = (Uint8)(L_X(rgb[0], 255));
	col.argb[1] = (Uint8)(L_X(rgb[1], 255));
	col.argb[2] = (Uint8)(L_X(rgb[2], 255));
	col.argb[3] = in_col.argb[3];
	return (col);
}
