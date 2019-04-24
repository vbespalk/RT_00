/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_man.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 16:18:02 by vbespalk          #+#    #+#             */
/*   Updated: 2019/02/05 16:18:05 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

# define V_MAX 1
# define V_MIN 0

/*
** Value S,V must be in range [0,1], H must be in range [0, 360]
*/

t_color      hsv_to_rgb(float h, float s, float v)
{
    t_vector	rgb;
    long		i;
    float		hh;
    t_color     col;

    if (s <= 0.0f)
    {
        col.argb[0] = (Uint8) (L_X(v * 255, 255));
        col.argb[1] = (Uint8) (L_X(v * 255, 255));
        col.argb[2] = (Uint8) (L_X(v * 255, 255));
        return (col);
    }
    h = h == 360.0f ? 0 : h / 60.0f;
    i = (long)h;
    hh = h - i;
    rgb[0] = v * (1.0 - s);
    rgb[1] = v * (1.0 - s * hh);
    rgb[2] = v * (1.0 - s * (1.0 - hh));
    if (i == 0)
    {
        col.argb[0] = (Uint8) (L_X(v * 255, 255));
        col.argb[1] = (Uint8) (L_X(rgb[2] * 255, 255));
        col.argb[2] = (Uint8) (L_X(rgb[0] * 255, 255));
    }
    if (i == 1)
    {
        col.argb[0] = (Uint8) (L_X(rgb[1] * 255, 255));
        col.argb[1] = (Uint8) (L_X(v * 255, 255));
        col.argb[2] = (Uint8) (L_X(rgb[0] * 255, 255));
    }
    if (i == 2)
    {
        col.argb[0] = (Uint8) (L_X(rgb[0] * 255, 255));
        col.argb[1] = (Uint8) (L_X(v * 255, 255));
        col.argb[2] = (Uint8) (L_X(rgb[2] * 255, 255));
    }
    if (i == 3)
    {
        col.argb[0] = (Uint8) (L_X(rgb[0] * 255, 255));
        col.argb[1] = (Uint8) (L_X(rgb[1] * 255, 255));
        col.argb[2] = (Uint8) (L_X(v * 255, 255));
    }
    if (i == 4)
    {
        col.argb[0] = (Uint8) (L_X(rgb[2] * 255, 255));
        col.argb[1] = (Uint8) (L_X(rgb[0] * 255, 255));
        col.argb[2] = (Uint8) (L_X(v * 255, 255));
    }
    else
    {
        col.argb[0] = (Uint8) (L_X(v * 255, 255));
        col.argb[1] = (Uint8) (L_X(rgb[0] * 255, 255));
        col.argb[2] = (Uint8) (L_X(rgb[1] * 255, 255));
    }
    return (col);
}

float       min_max(float r, float g, float b, Uint32 flag)
{
    float result;

    if (flag == V_MIN)
    {
        result = r < g ? r : g;
        result = result < b ? result : b;
    }
    else
    {
        result = r > g ? r : g;
        result = result > b ? result : b;
    }
    return (result);
}
/*
** Value R,G,B must be in range [0,1]
*/
t_vector    rgb_to_hsv(float r, float g, float b)
{
    float		max;
    float		min;
    t_vector	hsv;

    min = min_max(r, g, b, V_MIN);
    max = min_max(r, g, b, V_MAX);
    if (max == min)
        hsv[0] = 0;
    else if (max == r)
        hsv[0] = 60.0f * ((g - b) / (max - min));
    else if (max == g)
        hsv[0] = 60.0f * (2.0f + (b - r) / (max - min));
    else if (max == b)
        hsv[0] = 60.0f * (4.0f + (r - g) / (max - min));
    if (hsv[0] < 0)
        hsv[0] += 360;
    if (max == 0.0f)
        hsv[1] = 0;
    else
        hsv[1] = (max - min) / max;
    hsv[2] = max;
    return (hsv);
}