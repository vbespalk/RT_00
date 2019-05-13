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
	cam->origin = (t_vector) { -500.0f, 0.0f, 0.0f };
	cam->fov = ft_torad(100.0f);
	cam->smooth = SMOOTH_1X;
	return (cam);
}

static t_smooth		ft_get_smooth_type(char *smooth_str)
{
	t_smooth	res;
	char		*tmp;

	if (!smooth_str)
		return (SMOOTH_1X);
	res = SMOOTH_1X;
	tmp = ft_strmap(smooth_str, ft_tolower);
	free(smooth_str);
	smooth_str = tmp;
	if (!ft_strcmp(smooth_str, "4x"))
		res = SMOOTH_4X;
	else if (!ft_strcmp(smooth_str, "9x"))
		res = SMOOTH_9X;
	free(smooth_str);
	return (res);
}

void				ft_parse_camera(char **content, t_camera *cam)
{
	float	angles[3];
	char	*smooth_str;

	ft_bzero(&angles[0], sizeof(angles));
	ft_get_attr(content, "origin", (void *)&(cam->origin), DT_POINT);
	ft_get_attr(content, "alpha", (void *)&(angles[0]), DT_FLOAT);
	ft_get_attr(content, "beta", (void *)&(angles[1]), DT_FLOAT);
	ft_get_attr(content, "gamma", (void *)&(angles[2]), DT_FLOAT);
	ft_get_attr(content, "smooth", (void *)&(smooth_str), DT_STRING);
	cam->smooth = ft_get_smooth_type(smooth_str);
	cam->angles = (t_vector) { angles[0], angles[1], angles[2] };
	ft_get_attr(content, "fov", (void *)&(cam->fov), DT_FLOAT);
	cam->fov = (float)ft_limitf(FOV_MIN, FOV_MAX, cam->fov);
	cam->fov = ft_torad(cam->fov);
	cam->angles[0] = ft_torad(cam->angles[0]);
	cam->angles[1] = ft_torad(cam->angles[1]);
	cam->angles[2] = ft_torad(cam->angles[2]);
}

//static t_dlist		*ft_sort_stack(t_scene *scn, t_list *objs)
//{
//	t_dlist		*node;
//	t_list		*o_node;
//	t_object	*o;
//
//	node = NULL;
//	o_node = objs;
//	if (!o_node)
//		return (NULL);
//
//	while (o_node)
//	{
//		o = (t_object *)(o_node->content);
//		if (o->ft_is_inside(o->fig, scn->cam->origin))
//		{
//			if (!node)
//				ft_dlstpush(&node, objs->content);
//			else
//			{
//
//			}
//		}
//		o_node = o_node->next;
//	}
//	return (node);
//}

//        LEAKS
//          |
//          |
//          |
//       \      /
//        \    /
//         \  /
//          \/

void				ft_get_start_stack(t_scene *scn)
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
		if (o->ft_is_inside(o, scn->cam->origin))
		{
			ft_lstpush(&objs, ft_nodenew((void *)o, sizeof(o)));
			++len;
		}
		node = node->next;
	}
    if (len == 0)
		scn->cam->inner_o = NULL;
	else if (len == 1)
		scn->cam->inner_o = (t_object *)(objs->content);
	else
		scn->cam->inner_o = ft_get_inner_object(&objs, scn->cam->origin);
	node = objs;
	while (node)
	{
		objs = node;
		node = node->next;
		free(objs);
	}
}
