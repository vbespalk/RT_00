//
// Created by ivoriik on 27.03.19.
//

#include "rt.h"

float 	ft_fractal_noise(t_procedural *tex, t_vector hit)
{
	int		i;
	float 	noise;
	float 	gain;
	float 	lacunarity;

	i = -1;
	noise = 0.f;
	gain = 1.0f;
	lacunarity = 1.0f;
	while (++i < tex->octaves)
	{
		noise += gain * tex->noise_ptr->ft_generate_noise(ft_3_vector_scale(hit, lacunarity),
				tex->noise_ptr->value_table);
		gain *= tex->gain;
		lacunarity *= tex->lacunarity;
	}
	noise = (noise - tex->bounds[0]) / (tex->bounds[1] - tex->bounds[0]);
	return (noise);
}

float 	ft_turbulance_noise(t_procedural *tex, t_vector hit)
{
	int		i;
	float 	noise;
	float 	gain;
	float 	lacunarity;

	i = -1;
	noise = 0.f;
	gain = 1.0f;
	lacunarity = 1.0f;
	while (++i < tex->octaves)
	{
		noise += gain * fabsf(tex->noise_ptr->ft_generate_noise(ft_3_vector_scale(hit, lacunarity),
				tex->noise_ptr->value_table));
		gain *= 0.5;
		lacunarity *= 2;
	}
	noise /= tex->bounds[1];
	return (noise);
}

Uint32 	ft_noise_col(t_procedural *tex, t_vector hit)
{
	float noise_val;

	noise_val = tex->ft_noise_value(tex, hit);
	noise_val = (noise_val - tex->min_max[0]) / (tex->min_max[1] - tex->min_max[0]);
	tex->color.argb[0] = (t_byte)(tex->color.argb[0] * noise_val);
	tex->color.argb[1] = (t_byte)(tex->color.argb[1] * noise_val);
	tex->color.argb[2] = (t_byte)(tex->color.argb[2] * noise_val);
	tex->color.argb[3] = (t_byte)(tex->color.argb[3] * noise_val);
	return (tex->color.val);
}

Uint32 	ft_wrapped_noise_col(t_procedural *tex, t_vector hit)
{
	float noise_val;

	noise_val = tex->expansion * tex->ft_noise_value(tex, hit);
	noise_val -= floorf(noise_val);
	tex->color.argb[0] = (t_byte)(tex->color.argb[0] * noise_val);
	tex->color.argb[1] = (t_byte)(tex->color.argb[1] * noise_val);
	tex->color.argb[2] = (t_byte)(tex->color.argb[2] * noise_val);
	tex->color.argb[3] = (t_byte)(tex->color.argb[3] * noise_val);
	return (tex->color.val);
}

Uint32 	ft_ramp_noise_col(t_procedural *tex, t_vector hit)
{
	float			noise_val;
	Uint32			col;
	int 			x;
	float			u;

	noise_val = tex->ft_noise_value(tex, hit);
	u = hit[1] + tex->pertubation * noise_val;
	u = (1.0f + sinf(u)) * 0.5f;
	x = (int)(u * (tex->ramp->w - 1));
	if (!(IN_RANGE(x, 0, tex->ramp->w)))
		return (0xff0000);
	ft_memcpy(&col, (Uint32 *)tex->ramp->pixels + x, sizeof(Uint32));
	return (col);
}