/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 13:17:57 by domelche          #+#    #+#             */
/*   Updated: 2018/08/23 13:25:38 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_camera			*ft_cameranew(void)
{
	t_camera	*cam;

	cam = ft_smemalloc(sizeof(t_camera), "ft_cameranew");
	cam->origin = (t_vector){ -500.0f, 0.0f, 0.0f };
	cam->fov = ft_torad(100.0f);
	return (cam);
}

char				*ft_parse_camera(char *attr, t_scene *scn)
{
	float angles[3];

	ft_bzero(&angles[0], sizeof(angles));
	attr = ft_get_curve(attr, '{');
	ft_get_attr_in_scope(attr, "origin:", (void *)&(scn->cam->origin), PNT);
	ft_get_attr_in_scope(attr, "alpha:", (void *)&(angles[0]), FLT);
	ft_get_attr_in_scope(attr, "beta:", (void *)&(angles[1]), FLT);
	ft_get_attr_in_scope(attr, "gamma:", (void *)&(angles[2]), FLT);
	scn->cam->angles = (t_vector){angles[0], angles[1], angles[2]};
	ft_get_attr_in_scope(attr, "fov:", (void *)&(scn->cam->fov), FLT);
	scn->cam->fov = (float)ft_limitf(FOV_MIN, FOV_MAX, scn->cam->fov);
	scn->cam->fov = ft_torad(scn->cam->fov);
	scn->cam->angles[0] = ft_torad(scn->cam->angles[0]);
	scn->cam->angles[1] = ft_torad(scn->cam->angles[1]);
	scn->cam->angles[2] = ft_torad(scn->cam->angles[2]);
	return (ft_get_curve(attr, '}'));
}

static void			ft_add_start_object(t_scene *scn, t_object *o)
{
	int		i;

	i = -1;
	while (++i < THREADS)
		scn->hits[i]->o = o;
}

static t_object		*ft_get_inner_object(t_list *objs, t_vector point)
{
	t_vector	direct;
	float		dist;
	float		min_dist;
	t_object	*o;
	t_object	*res;

	direct = (t_vector){ 1.0f, 0.0f, 0.0f };
	min_dist = FLT_MAX;
	res = NULL;
	while (objs)
	{
		o = (t_object *)(objs->content);
		dist = ft_3_point_point_dist(
			point, o->ft_collide(o->fig, point, direct));
		if (dist < min_dist)
		{
			min_dist = dist;
			res = o;
		}
		objs = objs->next;
	}
	return (res);
}

void				ft_get_start_refr(t_scene *scn)
{
	t_list		*objs;
	t_list		*node;
	t_object	*o;
	int 		len;

	objs = NULL;
	node = scn->objs;
	len = 0;
	while (node)
	{
		o = (t_object *)(node->content);
		if (o->ft_is_inside(o->fig, scn->cam->origin))
		{
			ft_lstpush(&objs, ft_nodenew((void *)o, sizeof(o)));
			++len;
		}
		node = node->next;
	}
	if (len == 0)
		return ;
	else if (len == 1)
		ft_add_start_object(scn, (t_object *)(objs->content));
	else
		ft_add_start_object(scn, ft_get_inner_object(objs, scn->cam->origin));
}
