/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 13:25:05 by domelche          #+#    #+#             */
/*   Updated: 2018/08/23 13:27:08 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_object	*ft_objectnew(Uint32 id)
{
	t_object	*o;

	o = ft_smemalloc(sizeof(t_object), "ft_objectnew");
	o->id = id;
	o->color.val = 0xffff00;
	o->ambnt = 0.1f;
	o->diff = 1.0f;
	o->phong = FLT_MIN;
	o->refr = 1.0f;
	o->translate = ZERO_PNT;
	o->rotate = ZERO_PNT;
	o->exposure = 0;
	return (o);
}

void		ft_balance_koefs(t_object *o)
{
	float	sum;

	sum = o->diff + o->trans + o->spclr;
	if (sum > 1.0f)
	{
		o->diff /= sum;
		o->trans /= sum;
		o->spclr /= sum;
	}
}

void		*ft_get_figure_parser(char *name)
{
	if (!name)
	{
		ft_printf("PARSE WARNING: object with unspecified name ignored\n");
		return (NULL);
	}
	else if (!ft_strcmp(name, "plane"))
		return (ft_parse_plane);
	else if (!ft_strcmp(name, "sphere"))
		return (ft_parse_sphere);
	else if (!ft_strcmp(name, "cone"))
		return (ft_parse_cone);
	else if (!ft_strcmp(name, "cylinder"))
		return (ft_parse_cylinder);
	else if (!ft_strcmp(name, "paraboloid"))
		return (ft_parse_prbld);
	else if (!ft_strcmp(name, "box"))
		return (ft_parse_box);
	else if (!ft_strcmp(name, "disk"))
		return (ft_parse_disk);
	else if (!ft_strcmp(name, "torus"))
		return (ft_parse_torus);
	ft_printf("PARSE WARNING: unknown object name '%s'\n", name);
	return (NULL);
}

static void	ft_get_object_attrs(char **content, t_object *o)
{
	ft_get_attr(content, "negative", (void *)(&(o->is_neg)), DT_BOOL);
	ft_get_attr(content, "react_negative", (void *)(&(o->react_neg)), DT_BOOL);
	ft_get_attr(content, "color", (void *)(&(o->color)), DT_COLOR);
	ft_get_attr(content, "ambnt", (void *)(&(o->ambnt)), DT_COEF);
	ft_get_attr(content, "diff", (void *)(&(o->diff)), DT_COEF);
	ft_get_attr(content, "spclr", (void *)(&(o->spclr)), DT_COEF);
	ft_get_attr(content, "s_blur", (void *)(&(o->s_blur)), DT_COEF);
	ft_get_attr(content, "refr", (void *)(&(o->refr)), DT_FLOAT);
	ft_get_attr(content, "transparent", (void *)(&(o->trans)), DT_COEF);
	ft_get_attr(content, "t_blur", (void *)(&(o->t_blur)), DT_COEF);
	ft_get_attr(content, "phong", (void *)(&(o->phong)), DT_COEF);
	ft_get_attr(content, "translate", (void *)(&(o->translate)), DT_POINT);
	ft_get_attr(content, "rotate", (void *)(&(o->rotate)), DT_POINT);
	ft_get_attr(content, "texture", (void *)(&(o->texture_id)), DT_STRING);
	ft_get_attr(content, "procedural", (void *)(&(o->noise)), DT_PROCEDURAL);
	ft_get_attr(content, "checker", (void *)(&(o->checker)), DT_CHECKER);
}

void		ft_parse_object(char **content, t_list **lst, Uint32 id)
{
	t_object	*o;
	char		*name;
	void		*(*ft_parse_figure)(char **, t_object *o);

	name = NULL;
	ft_get_attr(content, "name", (void *)(&(name)), DT_STRING);
	ft_parse_figure = ft_get_figure_parser(name);
	free(name);
	if (!ft_parse_figure)
		return ;
	o = ft_objectnew(id);
	o->react_neg = false;
	o->color.val = UINT32_MAX;
	o->noise = NULL;
	o->checker = NULL;
	o->texture = NULL;
	o->texture_id = NULL;
	o->composed = false;
	ft_get_object_attrs(content, o);
	o->react_neg = o->is_neg ? false : o->react_neg;
	ft_balance_koefs(o);
	o->rotate = (t_vector){ft_torad(o->rotate[0]), ft_torad(o->rotate[1]),
				ft_torad(o->rotate[2])};
	o->fig = ft_parse_figure(content, o);
	ft_lstpush(lst, ft_nodenew((void *)o, sizeof(t_object)));
}
