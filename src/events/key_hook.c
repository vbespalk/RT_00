/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 17:35:53 by vbespalk          #+#    #+#             */
/*   Updated: 2019/04/27 16:29:19 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_ev.h"

static int	ft_on_other_key_down(SDL_Keycode sum, t_env *e)
{
	if (sum == SDLK_DELETE && e->selected)
		if (delete_obj(&(e->scn->objs), e->selected->id))
			return ((e->selected = NULL) == NULL);
	if (sum == SDLK_g || sum == SDLK_u || sum == SDLK_h || sum == SDLK_i)
		return (ft_switch_col_mode(e, sum));
	if (sum == SDLK_b)
		return (ft_switch_skybox(e->sdl, e->scn));
	if (e->selected && (sum >= SDLK_0 && sum <= SDLK_9))
		return (ft_set_exposure(sum, e->selected, e));
	if (sum == SDLK_c)
		e->selected = NULL;
	if (sum == SDLK_RALT || sum == SDLK_LALT)
		return (ft_mod_depth(sum, &(e->scn->depth)));
	return (0);
}

int			on_key_down(SDL_Keycode sum, t_env *e)
{
	if (sum == SDLK_w || sum == SDLK_a || sum == SDLK_s ||
		sum == SDLK_d || sum == SDLK_q || sum == SDLK_e)
	{
		return (e->selected ? e->selected->ft_translate(sum, e->selected,
				&(e->selected->transform), &(e->selected->inverse)) :
				ft_translate_cam(sum, &(e->scn->cam->origin)));
	}
	if (sum == SDLK_UP || sum == SDLK_DOWN || sum == SDLK_LEFT ||
		sum == SDLK_RIGHT || sum == SDLK_PAGEDOWN || sum == SDLK_PAGEUP)
	{
		return (e->selected ? e->selected->ft_rotate(sum, e->selected,
				&(e->selected->transform), &(e->selected->inverse)) :
				ft_rotate_cam(sum, &(e->scn->cam->angles)));
	}
	if (sum == SDLK_z || sum == SDLK_x)
	{
		return (e->selected ? e->selected->ft_scale(sum, e->selected,
				&(e->selected->transform), &(e->selected->inverse)) :
				ft_scale_cam(sum, &(e->scn->cam->fov)));
	}
	if (e->selected && (sum == SDLK_r || sum == SDLK_t))
		return (e->selected->ft_scale_height(sum, e->selected,
				&(e->selected->transform), &(e->selected->inverse)));
		return (ft_on_other_key_down(sum, e));
}
