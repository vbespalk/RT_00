/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 16:03:58 by vbespalk          #+#    #+#             */
/*   Updated: 2018/09/04 16:04:16 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector		get_spec(t_light *light, t_ray *ray, t_object *obj, t_vector l_dir)
{
	t_vector	r_dir;
	t_vector	col;
	float		intencity;
	float		rdotv;
	float		ks;

	ks = 0.004f * L_X(obj->reflect / 5, (unsigned int)100);
	col = (t_vector){0.0f, 0.0f, 0.0f};
	r_dir = vec_scalar_mult(ray->hit_n, 2.0f * \
		dot_product(ray->hit_n, l_dir)) - l_dir;
	normilize_vec(&r_dir);
	rdotv = dot_product(r_dir, vec_scalar_mult(ray->dir, -1.0f));
	if (rdotv < 0.0f)
		return (col);
	intencity = light->rad * pow(rdotv, \
		(L_X(obj->reflect, (unsigned int)1024)));
	col[0] = light->col[0] / 255.0f * intencity * ks;
	col[1] = light->col[1] / 255.0f * intencity * ks;
	col[2] = light->col[2] / 255.0f * intencity * ks;
	return (col);
}

t_vector		get_diff(t_light *light, t_ray *ray, t_vector l_dir)
{
	float		intencity;
	t_vector	col;
	float		rad;

	col = (t_vector){0.0f, 0.0f, 0.0f};
	rad = light->rad > 100.0f ? 1.0f : light->rad / 100.0f;
	if ((intencity = rad * dot_product(l_dir, ray->hit_n)) < 0)
		intencity = 0;
	col[0] = light->col[0] / 255.0f * intencity;
	col[1] = light->col[1] / 255.0f * intencity;
	col[2] = light->col[2] / 255.0f * intencity;
	return (col);
}

int				trace_shad(t_vector l_dir, t_ray *ray, t_object *objs, float dis)
{
	float		t;
	t_object		*ptr;
	t_vector	vec;

	vec = ray->hit_p + vec_scalar_mult(ray->hit_n, 0.001f);
	ptr = objs;
	while ((ptr))
	{
		if (ptr->intersect(l_dir, vec, *ptr, &t) && (t * t) < dis)
			return (0);
		ptr = ptr->next;
	}
	return (1);
}

t_vector		get_normal(t_ray *ray, t_object *obj)
{
	t_vector	hit_n;
	float		m;

	if (obj->type == 0)
		hit_n = vec_scalar_mult((obj->rotate), -1.0f);
	if (obj->type == 1)
		hit_n = ray->hit_p - obj->translate;
	if (obj->type == 2)
	{
		m = dot_product(vec_scalar_mult(obj->rotate, ray->t), ray->dir) \
		+ dot_product((ray->ori - obj->translate), obj->rotate);
		hit_n = ray->hit_p - obj->translate - vec_scalar_mult(obj->rotate, m);
		normilize_vec(&(hit_n));
	}
	if (obj->type == 3)
	{
		t_cone	*cone = (t_cone *)obj->fig;
		m = dot_product(vec_scalar_mult(obj->rot, ray->t), ray->dir) \
		+ dot_product((ray->ori - obj->translate), obj->rot);
		hit_n = ray->hit_p - obj->translate - vec_scalar_mult(obj->rotate, m);
		hit_n -= vec_scalar_mult(obj->rot, m * cone->tg2);
	}
	normilize_vec(&(hit_n));
	return (hit_n);
}

t_vector		get_light(t_env *env, t_ray *ray, t_object *obj, t_light *p_light)
{
	t_vector	li;
	t_vector	spec;
	t_vector	l_dir;
	float		r2;
	int			in_sh;

	ray->hit_n = get_normal(ray, obj);
	li = (t_vector){0.0f, 0.0f, 0.0f};
	spec = (t_vector){0.0f, 0.0f, 0.0f};
	while (p_light)
	{
		l_dir = p_light->pos - ray->hit_p;
		r2 = dot_product(l_dir, l_dir);
		normilize_vec(&l_dir);
		if (obj->reflect)
			spec = get_spec(p_light, ray, obj, l_dir);
		in_sh = trace_shad(vec_scalar_mult(l_dir, 1.0), ray, env->obj, r2);
		li += vec_scalar_mult(get_diff(p_light, ray, l_dir), in_sh) + \
		vec_scalar_mult(spec, in_sh);
		p_light = p_light->next;
	}
	li = (t_vector){li[0] + AMBILI, li[1] + AMBILI, li[2] + AMBILI};
	return (li);
}
