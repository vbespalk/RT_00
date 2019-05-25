/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_gui_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 12:15:26 by mdovhopo          #+#    #+#             */
/*   Updated: 2019/05/22 15:39:54 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

uint32_t		mouse_on_btn(const int32_t x, const int32_t y, t_env *e)
{
	uint32_t		i;
	const uint32_t	w = e->sdl->scr_wid;

	i = -1;
	while (++i < BUTTONS_AMOUNT)
	{
		if ((uint32_t)x > w - g_btn_containers[i].x &&
			(uint32_t)x < w - g_btn_containers[i].x + g_btn_containers[i].w &&
			y > g_btn_containers[i].y &&
			y < g_btn_containers[i].y + g_btn_containers[i].h)
			return (i + 1);
	}
	return (0);
}

static void		inc_val_in_range(float *val, uint8_t cond, float lo, float hi)
{
	const float inc = 0.1f;

	*val += cond ? -inc : inc;
	*val = fmax(lo, fmin(hi, *val));
}

static uint32_t	object_mode_events_handle_2(t_env *e, const uint32_t id)
{
	if (id == T_BLUR_DOWN || id == T_BLUR_UP)
		inc_val_in_range(&(e->selected->t_blur), id == T_BLUR_DOWN, 0, 1);
	else if (id == S_BLUR_DOWN || id == S_BLUR_UP)
		inc_val_in_range(&(e->selected->s_blur), id == S_BLUR_DOWN, 0, 1);
	else if (id == TRANSP_DOWN || id == TRANSP_UP)
	{
		inc_val_in_range(&(e->selected->trans), id == TRANSP_DOWN, 0, 1);
		ft_balance_koefs(e->selected);
	}
	else if (id == DIFFUSE_DOWN || id == DIFFUSE_UP)
	{
		inc_val_in_range(&(e->selected->diff), id == DIFFUSE_DOWN, 0, 1);
		ft_balance_koefs(e->selected);
	}
	else if (id == AMBIENT_DOWN || id == AMBIENT_UP)
		inc_val_in_range(&(e->selected->ambnt), id == AMBIENT_DOWN, 0, 1);
	else if (id >= COLOR && id <= TEX_6)
		return (texture_editing(e, id));
	return (1);
}

static uint32_t	object_mode_events_handle_1(t_env *e, const uint32_t id)
{
	if ((id == RADIUS_DOWN || id == RADIUS_UP) && e->selected)
		return (e->selected->ft_scale(id == RADIUS_DOWN ? SDLK_x : SDLK_z,
		e->selected, &(e->selected->transform), &(e->selected->inverse)));
	else if ((id == HEIGHT_DOWN || id == HEIGHT_UP) && e->selected)
		return (e->selected->ft_scale_height(id == HEIGHT_DOWN ? SDLK_t :
	SDLK_r, e->selected, &(e->selected->transform), &(e->selected->inverse)));
	else if (id == REFL_DOWN || id == REFL_UP)
	{
		inc_val_in_range(&(e->selected->spclr), id == REFL_DOWN, 0, 1);
		ft_balance_koefs(e->selected);
		return (1);
	}
	else if (id == REFR_DOWN || id == REFR_UP)
	{
		inc_val_in_range(&(e->selected->refr), id == REFR_DOWN, 1, 2.4);
		return (1);
	}
	else
		return (object_mode_events_handle_2(e, id));
}

uint32_t		handle_button(t_env *e, const uint32_t id)
{
	if (id == SCREENSHOT || id == CAMERA_MODE ||
		id == SKYBOX || (id >= DELETE_OBJ && id <= REACT_NEGATIVE))
		return (other_buttons(e, id));
	else if (id >= GRAYSCALE && id <= INVERTED)
		return (color_filter(e, id));
	else if (id == FOV_DOWN || id == FOV_UP)
		return (ft_scale_cam((id == FOV_DOWN ? SDLK_z : SDLK_x),
								&(e->scn->cam->fov)));
	else if (id >= TRANS_OX_DOWN && id <= TRANS_OZ_UP)
		return (translate(e, id));
	else if (id >= ROT_OX_DOWN && id <= ROT_OZ_UP)
		return (rotate(e, id));
	else if (id >= RADIUS_DOWN && id <= TEX_6 && e->selected)
		return (object_mode_events_handle_1(e, id));
	return (0);
}
