//
// Created by ivoriik on 09.03.19.
//

#include "rt.h"

t_texture				*load_texture(t_sdl *sdl, char *path)
{
	SDL_Surface	*src;
	t_texture	*texture;

	texture = ft_smemalloc(sizeof(t_texture), "load_texture");
	texture->path = ft_strdup(path);
	src = IMG_Load(path);
	if(!src)
	{
		sdl_img_error("Error at load_texture(). Texture value set to color.\n");
		return (NULL);
	}
	texture->surface = SDL_ConvertSurface(src, sdl->format, 0);
//	texture->pixels = (Uint32 *)ft_memcpy(&texture->pixels, &texture->texture->pixels, sizeof());
	// tex = SDL_CreateTextureFromSurface(sdl->renderer, surf);
	// if (!tex)
	// {
	// 	fprintf(stderr, "CreateTextureFromSurface failed: %s\n", SDL_GetError());
	// 	return (-1);
	// }
	SDL_FreeSurface(src);
	printf("TEXTURE %s loading SUCCESSFULLY\n", path);
	return (texture);
}
t_texture			*init_texture(t_list **textures, t_sdl *sdl, char *id)
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
				return (((t_texture *) lst->content));
			lst = lst->next;
		}
	}
	t = load_texture(sdl, id);
	if (!t)
		return (NULL);
	ft_lstpush(textures, ft_nodenew((void *)t, sizeof(t_texture)));
	return (t);
}