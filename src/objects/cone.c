/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 13:25:05 by domelche          #+#    #+#             */
/*   Updated: 2018/08/23 13:26:05 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_cone		*ft_conenew(void)
{
	t_cone	*cone;

	cone = ft_smemalloc(sizeof(t_cone), "ft_conenew");
	cone->base_ini = (t_vector){ 0.0f, 0.0f, -200.0f };
	cone->base_rad_ini = 100;
	cone->vert = (t_vector){ 0.0f, 0.0f, 200.0f };
	cone->vert_rad_ini = 100;
	return (cone);
}

void		ft_cone_init(t_object *obj, t_cone *cone)
{
	obj->fig = cone;
	cone->bv_dist_ini = ft_3_point_point_dist(cone->base_ini, cone->vert);
	cone->bv_dist = cone->bv_dist_ini;
	cone->base_ini += obj->translate;
	cone->vert += obj->translate;
	cone->base = cone->base_ini;
	cone->base_rad = cone->base_rad_ini;
	cone->vert_rad = cone->vert_rad_ini;
	cone->bv_ini = ft_3_vector_rotate(
		ft_3_unitvectornew(cone->base, cone->vert),
		obj->rotate[0], obj->rotate[1], obj->rotate[2]);
	cone->bv = cone->bv_ini;
	cone->vert = cone->base + ft_3_vector_scale(cone->bv, cone->bv_dist);
	cone->side_norm_angle = (float)acos(
		(cone->bv_dist * sin(atan((cone->base_rad_ini - cone->vert_rad_ini) /
			cone->bv_dist))) / (cone->base_rad - cone->vert_rad));
	cone->main_vert = cone->base + ft_3_vector_scale(
		cone->bv,
		cone->base_rad * cone->bv_dist / (cone->base_rad - cone->vert_rad));
}

char		*ft_parse_cone(char *attr, t_scene *scn, unsigned int id)
{
	t_object	*obj;
	t_cone		*cone;

	obj = ft_parse_object(attr);
	obj->id = id; 
	obj->ft_collide = ft_collide_cone;
	obj->ft_is_reachable = ft_is_reachable_plane;
	obj->ft_is_inside = ft_is_inside_cone;
	obj->ft_get_norm = ft_get_norm_cone;
	obj->ft_translate = ft_translate_cone;
	obj->ft_rotate = ft_rotate_cone;
	obj->ft_scale = ft_scale_cone;
	cone = ft_conenew();
	attr = ft_get_curve(attr, '{');
	ft_get_attr_in_scope(attr, "base:", (void *)(&(cone->base_ini)), PNT);
	ft_get_attr_in_scope(attr, "base_rad:", (void *)(&(cone->base_rad_ini)), FLT);
	ft_get_attr_in_scope(attr, "vert:", (void *)(&(cone->vert)), PNT);
	ft_get_attr_in_scope(attr, "vert_rad:", (void *)(&(cone->vert_rad_ini)), FLT);
	if (cone->base_rad < 0 && cone->vert_rad < 0)
	{
		cone->base_rad *= -1.0f;
		cone->vert_rad *= -1.0f;
	}
	ft_cone_init(obj, cone);
	ft_lstpush(&(scn->objs), ft_nodenew((void *)obj, sizeof(obj)));
	return (ft_get_curve(attr, '}'));
}

void		ft_translate_cone(Uint32 key, void *fig, t_vector *transl)
{
	t_cone *cone;

	cone = (t_cone *)fig;
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
	cone->base = cone->base_ini + *(transl);
	cone->vert = cone->base + ft_3_vector_scale(cone->bv, cone->bv_dist);
	cone->main_vert = cone->base + ft_3_vector_scale(
		cone->bv,
		cone->base_rad * cone->bv_dist / (cone->base_rad - cone->vert_rad));
}

void		ft_rotate_cone(Uint32 key, void *fig, t_vector *rot)
{
	t_cone *cone;

	cone = (t_cone *)fig;
	if (!fig)
		return ;
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
	cone->bv = ft_3_vector_rotate(cone->bv_ini, (*rot)[0], (*rot)[1], (*rot)[2]);
	cone->vert = cone->base + ft_3_vector_scale(cone->bv, cone->bv_dist);
	cone->main_vert = cone->base + ft_3_vector_scale(
		cone->bv,
		cone->base_rad * cone->bv_dist / (cone->base_rad - cone->vert_rad));
}

void		ft_scale_cone(Uint32 key, void *fig, float *scale)
{
	t_cone *cone;

	cone = (t_cone *)fig;
	if (!fig)
		return ;
	if (key == SDLK_z)
		*scale += SCALE_F;
	else if (key == SDLK_x && *scale - SCALE_F >= 0.0f)
		*scale -= SCALE_F;
	else
		*scale = 0;
	cone->base_rad = cone->base_rad_ini * *scale;
	cone->vert_rad = cone->vert_rad_ini * *scale;
	cone->bv_dist = cone->bv_dist_ini * *scale;
	cone->vert = cone->base + ft_3_vector_scale(cone->bv, cone->bv_dist);
	cone->main_vert = cone->base + ft_3_vector_scale(
	cone->bv,
	cone->base_rad * cone->bv_dist / (cone->base_rad - cone->vert_rad));
}
