/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 13:20:12 by domelche          #+#    #+#             */
/*   Updated: 2018/08/23 13:27:00 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			ft_usage(void)
{
	ft_putendl("Usage: ./RTv1 scene_file");
	return (1);
}

int			main(int ac, char **av)
{
	t_env		*e;

	if (ac != 2)
		return (ft_usage());
	srand((unsigned int)time(NULL));
	e = ft_envnew(av[1]);
	ft_render(e);
	mlx_key_hook(e->win, ft_key_hook, (void *)e);
	mlx_hook(e->win, CLOSE_NOTIFY, CLOSE_MASK,
			 ft_close_hook, (void *)e);
	mlx_loop(e->mlx);
	return (0);
}
