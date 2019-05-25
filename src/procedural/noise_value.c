/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 19:23:40 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/14 19:23:42 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float	ft_fractal_noise(t_procedural *tex, t_vector hit)
{
	int		i;
	float	noise;
	float	ampl;
	float	freq;

	i = -1;
	noise = 0.0f;
	ampl = 1.0f;
	freq = 1.0f;
	while (++i < (int)tex->octaves)
	{
		noise += ampl * tex->noise_ptr->ft_generate_noise
(ft_3_vector_scale(hit, freq), tex->noise_ptr->value_table);
		ampl *= tex->gain;
		freq *= tex->lacunarity;
	}
	return ((noise - tex->bounds[0]) / (tex->bounds[1] - tex->bounds[0]));
}

float	ft_turbulance_noise(t_procedural *tex, t_vector hit)
{
	int		i;
	float	noise;
	float	ampl;
	float	freq;

	i = -1;
	noise = 0.0f;
	ampl = 1.0f;
	freq = 1.0f;
	while (++i < (int)tex->octaves)
	{
		noise += ampl * fabsf(tex->noise_ptr->ft_generate_noise
(ft_3_vector_scale(hit, freq), tex->noise_ptr->value_table));
		ampl *= 0.5;
		freq *= 2;
	}
	return (noise / tex->bounds[1]);
}

/*
** EFFECTS: SINUS PERTURBATION
**
** noise_val = (sinf((noise_val * 100.0f) * 2 *
** (float)M_PI / 200.f) + 1) * 0.5f;
*/

Uint32	ft_wrapped_noise_col(t_procedural *tex, t_vector hit)
{
	float	val;
	t_color	color;

	val = tex->ft_noise_value(tex, hit);
	if (tex->pertubation != 1.0f)
	{
		val *= tex->pertubation;
		val -= floorf(val);
	}
	val = tex->min_max[0] + (tex->min_max[1] - tex->min_max[0]) * val;
	val = CLAMP(val, 0, 1);
	color.argb[0] = (t_byte)(tex->color.argb[0] * val);
	color.argb[1] = (t_byte)(tex->color.argb[1] * val);
	color.argb[2] = (t_byte)(tex->color.argb[2] * val);
	color.argb[3] = (t_byte)(tex->color.argb[3] * val);
	return (color.val);
}

Uint32	ft_ramp_noise_col(t_procedural *tex, t_vector hit)
{
	float	noise_val;
	Uint32	col;
	int		x;
	float	y;
	float	u;

	noise_val = tex->ft_noise_value(tex, hit);
	y = (hit[1] + hit[2] + hit[0]) * 0.6f;
	u = y + tex->pertubation * noise_val;
	u = 0.5f * (1.0f + sinf(u));
	x = (int)(u * (tex->ramp->w - 1));
	if (!(IN_RANGE(x, 0, tex->ramp->w-1)))
		return (UINT32_MAX);
	ft_memcpy(&col, (Uint32 *)tex->ramp->pixels + x, sizeof(Uint32));
	return (col);
}
