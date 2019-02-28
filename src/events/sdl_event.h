/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_ev.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 21:53:36 by vbespalk          #+#    #+#             */
/*   Updated: 2019/01/28 21:53:41 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SDL_EV_H
# define SDL_EV_H

# include "rt.h"



int		on_key_down(SDL_Keycode sum, Uint16 mod, t_env  *e);
int		on_key_up(SDL_Keycode sum, Uint16 mod, t_env  *e);
int		on_mouse_move(int x, int y, int rel_x, int rel_y, t_env *e, int left, int right, int middle);
int		on_lbutton_down(int x, int y, t_env *e );
int		on_rbutton_down(int x, int y, t_env *e );
int		on_lbutton_up(int x, int y, t_env *e );
int		on_resize(Sint32 w, Sint32 h, t_env *e);
int		ft_on_exit(t_env *e);
int		on_mouse_wheel(Sint32 y, Uint32 dir, t_env *e);

#endif