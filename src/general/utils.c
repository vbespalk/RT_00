/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 13:25:05 by domelche          #+#    #+#             */
/*   Updated: 2018/09/19 12:17:52 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color		ft_apply_phong(t_color color, float phong, t_color light_color)
{
	color.argb[2] += (t_byte)((255.0 - color.argb[2]) * phong *
		((float)light_color.argb[2] / 255.0));
	color.argb[1] += (t_byte)((255.0 - color.argb[1]) * phong *
		((float)light_color.argb[1] / 255.0));
	color.argb[0] += (t_byte)((255.0 - color.argb[0]) * phong *
		((float)light_color.argb[0] / 255.0));
	return (color);
}

t_color		ft_scale_color(t_color color, float k)
{
	color.argb[2] = (t_byte)((float)(color.argb[2]) * k);
	color.argb[1] = (t_byte)((float)(color.argb[1]) * k);
	color.argb[0] = (t_byte)((float)(color.argb[0]) * k);
	return (color);
}

t_color		ft_add_colors(t_color c1, t_color c2)
{
	c1.argb[2] = (t_byte)ft_limit(0, 255, c1.argb[2] + c2.argb[2]);
	c1.argb[1] = (t_byte)ft_limit(0, 255, c1.argb[1] + c2.argb[1]);
	c1.argb[0] = (t_byte)ft_limit(0, 255, c1.argb[0] + c2.argb[0]);
	return (c1);
}
