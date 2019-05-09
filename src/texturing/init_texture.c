//
// Created by ivoriik on 09.03.19.
//

#include "rt.h"

t_texture				*load_texture(t_sdl *sdl, char *path)
{
	SDL_Surface	*src;
	t_texture	*texture;

	texture = ft_smemalloc(sizeof(t_texture), "load_texture");
	ft_bzero(texture, sizeof(t_texture));
	texture->path = ft_strdup(path);
	src = IMG_Load(path);
	if(!src)
	{
		sdl_img_error(ON_WARN "load texture");
		ft_memdel((void **)&texture->path);
		ft_memdel((void **)&texture);
		return (NULL);
	}
	texture->surface = SDL_ConvertSurface(src, sdl->format, 0);
	SDL_FreeSurface(src);
	printf("TEXTURE %s loading SUCCESSFULLY\n", path);
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
			if (ft_strcmp(id, ((t_texture *) lst->content)->path) == 0)
				return (((t_texture *) lst->content)->surface);
			lst = lst->next;
		}
	}
    t = load_texture(sdl, id);
	if (!t)
		return (NULL);
	ft_lstpush(textures, ft_nodenew((void *)t, sizeof(t_texture)));
	return (t->surface);
}