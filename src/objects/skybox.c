/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 15:23:02 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/10 15:23:04 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_parse_skybox(char **content, t_skybox **sky)
{
	int			i;

	if (!content || !(*content))
		return ;
	*sky = (t_skybox *)ft_smemalloc(sizeof(t_skybox), "ft_parse_skybox");
	ft_get_attr(content, "negz", (void *)(&((*sky)->textur_id[0])), DT_STRING);
	ft_get_attr(content, "negy", (void *)(&((*sky)->textur_id[1])), DT_STRING);
	ft_get_attr(content, "negx", (void *)(&((*sky)->textur_id[2])), DT_STRING);
	ft_get_attr(content, "posz", (void *)(&((*sky)->textur_id[3])), DT_STRING);
	ft_get_attr(content, "posy", (void *)(&((*sky)->textur_id[4])), DT_STRING);
	ft_get_attr(content, "posx", (void *)(&((*sky)->textur_id[5])), DT_STRING);
	(*sky)->bbx = ft_init_aabb(ZERO_PNT, ZERO_PNT);
	i = -1;
	while (++i < BOX_FACES)
		if ((*sky)->textur_id[i] == NULL)
		{
			ft_putendl(ON_WARN "ft_parse_skybox: value set to default");
			ft_skybox_del(sky);
			return ;
		}
}

t_color		ft_apply_sky(t_skybox *sky, t_vector o, t_vector d)
{
	t_vector	hit;
	t_color		col;

	hit = sky->bbx->ft_collide(sky->bbx, o, d);
	col.val = ft_map_skybox(sky->bbx, sky->textur, hit);
	return (col);
}

int			ft_load_sky_tex(t_skybox **skybox, t_list **tex, t_sdl *sdl)
{
	int i;

	i = -1;
	while (++i < BOX_FACES)
		if (!((*skybox)->textur[i] = init_texture(tex, sdl,
			(*skybox)->textur_id[i])))
		{
			ft_skybox_del(skybox);
			return (0);
		}
	return (1);
}

void		ft_skybox_del(t_skybox **sk)
{
	int i;

	if (!sk || !*sk)
		return ;
	ft_memdel((void **)&(*sk)->bbx);
	i = -1;
	while (++i < BOX_FACES)
		ft_memdel((void **)&(*sk)->textur_id[i]);
	ft_memdel((void **)sk);
}
