/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_transf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 21:29:24 by vbespalk          #+#    #+#             */
/*   Updated: 2019/02/07 21:29:26 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_translate_cam(Uint32 key, t_vector *transl)
{

	if (key == SDLK_w)
		(*transl)[1] += TRANS_F;
	if (key == SDLK_d)
		(*transl)[2] += TRANS_F;
	if (key == SDLK_a)
		(*transl)[2] -= TRANS_F;
	if (key == SDLK_s)
		(*transl)[1] -= TRANS_F;
	if (key == SDLK_q)
		(*transl)[0] += TRANS_F;
	if (key == SDLK_e)
		(*transl)[0] -= TRANS_F;
}

void	ft_rotate_cam(Uint32 key, t_vector *angles)
{
	if (key == SDLK_UP)
		(*angles)[0] += ROTAT_F;
	if (key == SDLK_DOWN)
		(*angles)[0] -= ROTAT_F;
	if (key == SDLK_LEFT)
		(*angles)[1] -= ROTAT_F;
	if (key == SDLK_RIGHT)
		(*angles)[1] += ROTAT_F;
	if (key == SDLK_PAGEUP)
		(*angles)[2] -= ROTAT_F;
	if (key == SDLK_PAGEDOWN)
		(*angles)[2] += ROTAT_F;
}

void	ft_scale_cam(Uint32 key, float *sc_factor)
{
	if (key == SDLK_z)
		*sc_factor = ((*sc_factor - SCALE_F) < DEG_TO_RAD(10.f)) ? \
	DEG_TO_RAD(10.f) : *sc_factor - SCALE_F;
	else if (key == SDLK_x)
		*sc_factor = ((*sc_factor + SCALE_F) < DEG_TO_RAD(160)) ? *sc_factor + \
	SCALE_F : DEG_TO_RAD(160);
}

