/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_gui_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 12:15:26 by mdovhopo          #+#    #+#             */
/*   Updated: 2019/04/24 13:55:19 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

uint32_t	mouse_on_btn(const int32_t x, const int32_t y, t_env *e)
{
	uint32_t		i;
	const uint32_t	w = e->sdl->scr_wid;

	i = -1;
	while (++i < BUTTONS_AMOUNT)
	{
		if (x > w - g_btn_containers[i].x &&
			x < w - g_btn_containers[i].x + g_btn_containers[i].w &&
			y > g_btn_containers[i].y &&
			y < g_btn_containers[i].y + g_btn_containers[i].h)
			return (i + 1);
	}
	return (0);
}

static void	inc_val_in_range(float *val, uint8_t cond, float lo, float hi)
{
	const float inc = 0.1f;

	*val += cond ? -inc : inc;
	*val = clamp(lo, hi, *val);
}

static void	object_mode_events_handle_2(t_env *e, const uint32_t id)
{
	if (id == T_BLUR_DOWN || id == T_BLUR_UP)
		inc_val_in_range(&(e->selected->t_blur), id == T_BLUR_DOWN, 0, 1);
	else if (id == S_BLUR_DOWN || id == S_BLUR_UP)
		inc_val_in_range(&(e->selected->s_blur), id == S_BLUR_DOWN, 0, 1);
	else if (id == TRANSP_DOWN || id == TRANSP_UP)
		inc_val_in_range(&(e->selected->trans), id == TRANSP_DOWN, 0, 1);
	else if (id == DIFFUSE_DOWN || id == DIFFUSE_UP)
		inc_val_in_range(&(e->selected->diff), id == DIFFUSE_DOWN, 0, 1);
	else if (id == AMBIENT_DOWN || id == AMBIENT_UP)
		inc_val_in_range(&(e->selected->ambnt), id == AMBIENT_DOWN, 0, 1);
}

static void	object_mode_events_handle_1(t_env *e, const uint32_t id)
{
	if (id == RADIUS_DOWN || id == RADIUS_UP)
		{} // radius change
	else if (id == HEIGHT_DOWN || id == HEIGHT_UP)
		{} // height change
	else if (id == REFL_DOWN || id == REFL_UP)
		{} // reflection change
	else if (id == REFR_DOWN || id == REFR_UP)
		inc_val_in_range(&(e->selected->refr), id == REFR_DOWN, 1, 2.4);
	else
		object_mode_events_handle_2(e, id);
}

uint32_t	handle_button(t_env *e, const uint32_t id)
{
	printf("clicked btn with id %d\n", id); // remove this test stuff
	if (id == SAVE_IMG || id == CAMERA_MODE ||
		id == SKYBOX || id == DELETE_OBJ)
		other_buttons(e, id);
	else if (id >= SAVE_IMG && id <= COLOR_FILTER_TMP_NAME)
		color_filter(e, id);
	else if (id == FOV_DOWN || id == FOV_UP)
		ft_scale_cam((id == FOV_DOWN ? SDLK_z : SDLK_x), &(e->scn->cam->fov));
	else if (id >= TRANS_OX_DOWN && id <= TRANS_OZ_UP)
		translate(e, id);
	else if (id >= ROT_OX_DOWN && id <= ROT_OZ_UP)
		rotate(e, id);
	else if (id > ROT_OZ_UP && id <= AMBIENT_UP && e->selected)
		object_mode_events_handle_1(e, id);
	return (id);
}
