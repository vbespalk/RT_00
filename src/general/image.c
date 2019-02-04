/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 13:25:05 by domelche          #+#    #+#             */
/*   Updated: 2018/08/23 13:26:43 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_img	*ft_imgnew(t_env *e)
{
	t_img	*img;

	img = (t_img *)ft_smemalloc(sizeof(t_img), "ft_imgnew");
	img->ptr = mlx_new_image(e->mlx, WIN_WIDTH, WIN_HEIGHT);
	img->data = mlx_get_data_addr(img->ptr, &(img->bpp),
		&(img->size_line), &(img->endian));
	img->bpp /= 8;
	return (img);
}

void	ft_pixel_put_image(t_env *e, int x, int y, int color)
{
	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	*(int *)(e->img->data + (y * (int)WIN_WIDTH + x) * e->img->bpp) = color;
}
