/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   init_sdl.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: vbespalk <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2018/11/07 17:47:37 by vbespalk		  #+#	#+#			 */
/*   Updated: 2018/11/07 17:47:39 by vbespalk		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "rt.h"

int	get_format_data(t_sdl *sdl)
{
	Uint32		rmask;
	Uint32		gmask;
	Uint32		bmask;
	Uint32		amask;
	SDL_Surface	*surface;

	if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
	{
		rmask = 0x00ff0000;
		gmask = 0x0000ff00;
		bmask = 0x000000ff;
		amask = 0xff000000;
	}
	else
	{
		rmask = 0x00ff0000;
		gmask = 0x0000ff00;
		bmask = 0x000000ff;
		amask = 0xff000000; // test commit
	}
	surface = SDL_CreateRGBSurface(0, sdl->rt_wid, sdl->scr_hei, 32, rmask, gmask, bmask, amask);
	if (!(surface))
		return(sdl_error("SDL could not createRGBSurface! "));
	sdl->pitch = surface->pitch / sizeof(unsigned int);
	sdl->format = (SDL_PixelFormat *)malloc(sizeof(SDL_PixelFormat));
	ft_memcpy(sdl->format, surface->format, sizeof(SDL_PixelFormat));
	SDL_FreeSurface(surface);
	return (0);
}

int		sdl_init(t_sdl *sdl)
{
	SDL_RendererInfo	info;
	Uint32				flags;
	int					img_flags;
	int 				img_init;

	//The window we'll be rendering to
	flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
	img_flags = IMG_INIT_JPG | IMG_INIT_PNG ;
	sdl->window = NULL;
	sdl->scr_wid = SCR_WID;
	sdl->scr_hei = SCR_HEI;
	//The surface contained by the window
	get_format_data(sdl);
	//Initialize SDL
	if (SDL_Init( SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
		return (sdl_error("SDL could not initialize! "));
	if (!IMG_Init(img_flags))
		return (sdl_img_error("SDL_IMG_Init: Failed to init required jpg and png support!\n"));
	//Create window
	sdl->window = SDL_CreateWindow( "RayTracer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCR_WID, SCR_HEI, flags);
	if(sdl->window == NULL)
	{
		SDL_Quit();
		return (sdl_error("Window could not be created! "));
	}
	sdl->renderer = SDL_CreateRenderer(sdl->window, -1, SDL_RENDERER_ACCELERATED);
	if(sdl->renderer == NULL)
	{
		sdl_close(sdl);
		return (sdl_error("Renderer could not be created! "));
	}
	//HOW IT WORKS??
	SDL_GetRendererInfo(sdl->renderer, &info);
	SDL_Log("RENDERER: %s", info.name);
	printf("CURRENT VIDEO DRIVER %s\n", SDL_GetCurrentVideoDriver());
	//Init texture
	sdl->screen = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, sdl->rt_wid, sdl->scr_hei);
	if(sdl->screen == NULL)
	{
		sdl_close(sdl);
		return (sdl_error("Surface could not be created! "));
	}
	if (!(sdl->pixels = (Uint32 *)malloc(sizeof(Uint32) * sdl->scr_hei * sdl->rt_wid)))
	{
		sdl_close(sdl);
		return (ft_perr_retu(NULL));
	}
	ft_memset(sdl->pixels, 100, sdl->scr_hei * sdl->rt_wid * sizeof(Uint32));

	return (0);
}

//MAKE VARIADIC clenup FUNCTION, LIKE HERE:
//https://www.willusher.io/sdl2%20tutorials/2014/08/01/postscript-1-easy-cleanup

void	sdl_close(t_sdl *sdl)
{
	SDL_DestroyTexture(sdl->screen);
	//Destroy renderer
	SDL_DestroyRenderer(sdl->renderer);
	//Destroy window
	SDL_DestroyWindow(sdl->window);
	sdl->window = NULL;
	SDL_DestroyTexture(sdl->gui->gui_texture);
	//Quit SDL subsystems
	SDL_Quit();
}

int 	sdl_error(char *message)
{
	if (message)
		ft_putstr_fd(message, 2);
	ft_putstr_fd("SDL Error: ", 2);
	ft_putstr_fd(SDL_GetError(), 2);
	ft_putstr_fd("\n", 2);
	return (-1);
}

int 	sdl_img_error(char *message)
{
	if (message)
		ft_putstr_fd(message, 2);
	ft_putstr_fd("SDL_Image Error: ", 2);
	ft_putstr_fd(IMG_GetError(), 2);
	ft_putstr_fd("\n", 2);
	return (-1);
}
