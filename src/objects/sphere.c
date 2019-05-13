/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 13:25:05 by domelche          #+#    #+#             */
/*   Updated: 2018/08/23 13:25:05 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_sphere	*ft_spherenew(void)
{
	t_sphere	*sph;

	sph = ft_smemalloc(sizeof(t_sphere), "ft_spherenew");
	sph->radius = 100.0f;
	sph->phi = 0.0f;
	sph->theta = 0.0f;
	return (sph);
}

void		*ft_parse_sphere(char **content, t_object *o)
{
	t_sphere	*sph;

	o->ft_collide = ft_collide_sphere;
//	o->ft_is_reachable = ft_is_reachable_sphere;
	o->ft_is_inside = ft_is_inside_sphere;
	o->ft_get_norm = ft_get_norm_sphere;
	o->ft_translate = ft_translate_sphere;
	o->ft_rotate = ft_rotate_sphere;
	o->ft_scale = ft_scale_sphere;
	o->ft_scale_height = ft_scale_hei_null;
	o->ft_mapping = ft_map_sphere;
	o->ft_checker = ft_checker_sph;
	o->ft_procedural = ft_procedural_sph;
	sph = ft_spherenew();
	ft_get_attr(content, "radius", (void *)(&(sph->radius)), DT_FLOAT);
	ft_3_transform_mat(&(o->transform), o->translate, ft_3_nullpointnew(), sph->radius);
	ft_3_inv_trans_mat(&(o->inverse), -o->translate, ft_3_nullpointnew(), 1.0f / sph->radius);
	printf("MATRIX\n");
	for (int i = 0; i < 4; ++i)
		printf("%f, %f, %f, %f\n", o->transform[i][0], o->transform[i][1], o->transform[i][2], o->transform[i][3]);
	printf("INVERTED\n");
	for (int i = 0; i < 4; ++i)
		printf("%f, %f, %f, %f\n", o->inverse[i][0], o->inverse[i][1], o->inverse[i][2], o->inverse[i][3]);
	return ((void *)sph);
}

int		ft_translate_sphere(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m)
{
	t_sphere	*sph;

	if (!o)
		return (0);
	sph = (t_sphere *)o->fig;
	if (key == SDLK_d)
		o->translate[2] += TRANS_F;
	if (key == SDLK_a)
		o->translate[2] -= TRANS_F;
	if (key == SDLK_w)
		o->translate[1] += TRANS_F;
	if (key == SDLK_s)
		o->translate[1] -= TRANS_F;
	if (key == SDLK_e)
		o->translate[0] += TRANS_F;
	if (key == SDLK_q)
		o->translate[0] -= TRANS_F;
	ft_3_transform_mat(tr_m, o->translate, ft_3_nullpointnew(), sph->radius);
	ft_3_inv_trans_mat(inv_m, -o->translate, ft_3_nullpointnew(), 1.0f / sph->radius);
    return (1);
}

int		ft_rotate_sphere(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m)
{
	t_sphere *sph;

	if (!o)
		return (0);
	sph = (t_sphere *)o->fig;
	if (key == SDLK_DOWN)
		sph->theta -= ROTAT_F;
	else if (key == SDLK_UP)
		sph->theta += ROTAT_F;
	else if (key == SDLK_LEFT)
		sph->phi += ROTAT_F;
	else if (key == SDLK_RIGHT)
		sph->phi -= ROTAT_F;
	else if (key == SDLK_PAGEDOWN)
	{
		sph->phi += 0.5 * ROTAT_F;
		sph->theta += 0.5 * ROTAT_F;
	}
	else if (key == SDLK_PAGEUP)
	{
		sph->phi -= 0.5 * ROTAT_F;
		sph->theta -= 0.5 * ROTAT_F;
	}
	if (!IN_RANGE(sph->phi, 0, 2 * M_PI))
		sph->phi = sph->phi < 0 ? sph->phi + 2 * (float)M_PI : sph->phi - 2 * (float)M_PI;
	if (!IN_RANGE(sph->theta, 0, 2 * M_PI))
		sph->theta = sph->theta < 0 ? sph->theta + 2 * (float)M_PI : sph->theta - 2 * (float)M_PI;
	printf("ANGLES THETA %f, PHI %f\n", sph->theta, sph->phi);
    return (1);
}

int		ft_scale_sphere(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m)
{
	t_sphere *sph;

	if (!o)
		return (0);
	sph = (t_sphere *)o->fig;
	float scale = 1;
	if (key == SDLK_z)
		scale += SCALE_F;
	else if (key == SDLK_x && scale >= 0.0f)
		scale -= SCALE_F;
	else
		scale = 0;
	sph->radius *= scale;
	ft_3_transform_mat(tr_m, o->translate, ft_3_nullpointnew(), sph->radius);
	ft_3_inv_trans_mat(inv_m, -o->translate, ft_3_nullpointnew(), 1.0f / sph->radius);
    return (1);
}
