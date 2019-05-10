/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 17:13:17 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/10 17:16:27 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_texture		*load_texture(t_sdl *sdl, char *path)
{
	SDL_Surface	*src;
	t_texture	*texture;

	texture = ft_smemalloc(sizeof(t_texture), "load_texture");
	ft_bzero(texture, sizeof(t_texture));
	texture->path = ft_strdup(path);
	src = IMG_Load(path);
	if (!src)
	{
		sdl_img_error(ON_WARN "load texture");
		ft_memdel((void **)&texture->path);
		ft_memdel((void **)&texture);
		return (NULL);
	}
	texture->surface = SDL_ConvertSurface(src, sdl->format, 0);
	texture->surface->w = texture->surface->pitch / sizeof(Uint32);
	SDL_FreeSurface(src);
	return (texture);
}

SDL_Surface		*init_texture(t_list **textures, t_sdl *sdl, char *id)
{
	t_list		*lst;
	t_texture	*t;

	if (!id || !textures)
		return (NULL);
	if (*textures)
	{
		lst = *textures;
		while (lst)
		{
			if (ft_strcmp(id, ((t_texture *)lst->content)->path) == 0)
				return (((t_texture *)lst->content)->surface);
			lst = lst->next;
		}
	}
	if (!(t = load_texture(sdl, id)))
		return (NULL);
	ft_lstpush(textures, ft_nodenew((void *)t, sizeof(t_texture)));
	return (t->surface);
}
