/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 13:25:05 by domelche          #+#    #+#             */
/*   Updated: 2018/08/23 13:27:16 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ft_get_vs_params(t_camera *cam)
{
	cam->direct = ft_3_vector_rotate(
		(t_vector){ 1.0f, 0.0f, 0.0f },
		cam->angles[0], cam->angles[1], cam->angles[2]);
	cam->vs_start_vec = ft_3_vector_rotate(
		(t_vector){ 0.0f, SCR_HEI / 2.0f, -SCR_WID / 2.0f },
		cam->angles[0], cam->angles[1], cam->angles[2]);
	cam->vs_x_step_vec = ft_3_vector_rotate(
		(t_vector){ 0.0f, 0.0f, 1.0f },
		cam->angles[0], cam->angles[1], cam->angles[2]);
	cam->vs_y_step_vec = ft_3_vector_rotate(
		(t_vector){ 0.0f, -1.0f, 0.0f },
		cam->angles[0], cam->angles[1], cam->angles[2]);
	cam->vs_start_point = cam->vs_start_vec + cam->origin +
		ft_3_vector_rotate(
			(t_vector){
				(SCR_WID / 2.0f) / (float)tan(cam->fov / 2.0f),
				0.0f,
				0.0f
			},
			cam->angles[0], cam->angles[1], cam->angles[2]);
}

void		ft_parse(char *content, t_scene *scn)
{
	char	*attr;
	char	*tmp;
	char	*to_free;

	if (!content)
		ft_error("scn file is empty");
	to_free = content;
	if ((attr = ft_search_attr(content, "scn", FTSA_GLOBALLY)))
		ft_parse_scene(attr, scn);
	if ((attr = ft_search_attr(content, "camera", FTSA_GLOBALLY)))
		ft_parse_camera(attr, scn);
	ft_get_vs_params(scn->cam);
	tmp = content;
	while ((attr = ft_search_attr(tmp, "light", FTSA_GLOBALLY)))
		tmp = ft_parse_light(attr, scn);
	tmp = content;
	while ((attr = ft_search_attr(tmp, "plane", FTSA_GLOBALLY)))
		tmp = ft_parse_plane(attr, scn);
	tmp = content;
	while ((attr = ft_search_attr(tmp, "sphere", FTSA_GLOBALLY)))
		tmp = ft_parse_sphere(attr, scn);
	tmp = content;
	while ((attr = ft_search_attr(tmp, "cone", FTSA_GLOBALLY)))
		tmp = ft_parse_cone(attr, scn);
	free(to_free);
}

char		*ft_get_curve(char *attr, char curve)
{
	while (*attr && *attr != curve)
		++attr;
	if (!*attr)
		ft_error("invalid scn file");
	return (attr + 1);
}
