//
// Created by Viktoriia BESPALKO on 2019-04-24.
//
# include "rt.h"
# define RED_CH 0.212671
# define GRE_CH 0.715160
# define BLU_CH 0.072169

t_color  ft_grayscale_px(t_color in_col)
{
    Uint8   v;
    t_color col;

    v = (Uint8)(RED_CH * in_col.argb[0] + GRE_CH *
    		in_col.argb[1] + BLU_CH * in_col.argb[2]);
    col.argb[0] = v;
    col.argb[1] = v;
    col.argb[2] = v;
    col.argb[3] = in_col.argb[3];
    return (col);
}

t_color  ft_sepia_px(t_color in_col)
{
    t_color col;

    col.argb[0] = (Uint8)L_X(in_col.argb[0] * .393 +
    		in_col.argb[1] * .769 + in_col.argb[2] * .189, 0xFF);
    col.argb[1] = (Uint8)L_X(in_col.argb[0] * .349 +
    		in_col.argb[1] * .686 + in_col.argb[2] * .168, 0xFF);
    col.argb[2] = (Uint8)L_X(in_col.argb[0] * .272 +
    		in_col.argb[1] * .534 + in_col.argb[2] * .131, 0xFF);
    col.argb[3] = in_col.argb[3];
    return (col);
}

t_color  ft_negative_px(t_color in_col)
{
    t_color col;

    col.argb[0] = (Uint8)(0xFF - in_col.argb[0]);
    col.argb[1] = (Uint8)(0xFF - in_col.argb[1]);
    col.argb[2] = (Uint8)(0xFF - in_col.argb[2]);
    col.argb[3] = in_col.argb[3];
    return (col);
}

/*
** SMTH WRONG WITH YELLOW THEN MORE WHEN 1 ITERATION
*/

t_color  ft_invert_px(t_color in_col)
{
    t_vector 	hsv;
    t_color 	col;

    hsv = rgb_to_hsv(in_col.argb[0] / 255.0f, in_col.argb[1] / 255.0f, in_col.argb[2] / 255.0f);
    col.argb[0] = (Uint8)(0xFF - in_col.argb[0]);
    col.argb[1] = (Uint8)(0xFF - in_col.argb[1]);
    col.argb[2] = (Uint8)(0xFF - in_col.argb[2]);
    col.argb[3] = (Uint8)0xFF;
    // hsv[0] -= 30;
    hsv[0] = (int)(hsv[0] + 180.0f + .5) % 360;
    col = hsv_to_rgb(hsv[0], hsv[1], hsv[2]);
    return (col);
}


void	ft_col_mode(t_sdl *sdl, t_mode *head)
{
	t_color col;
	int 	x;
	int 	y;
	t_mode	*mode;

	if (head == NULL)
		return ;
	y = -1;
	while (++y < sdl->scr_hei && (x = -1))
	{
		while (++x < sdl->rt_wid)
		{
			col.val = sdl->pixels[y * sdl->rt_wid + x];
			mode = head;
			while (mode)
			{
				if (mode->id == MD_GRAYSCALE)
					col = ft_grayscale_px(col);
				if (mode->id == MD_SEPIA)
					col = ft_sepia_px(col);
				if (mode->id == MD_NEGATIVE)
					col = ft_negative_px(col);
				if (mode->id == MD_INVERTED)
					col = ft_invert_px(col);
				sdl->pixels[y * sdl->rt_wid + x] = col.val;
				mode = mode->next;
			}
		}
	}
}

//void	ft_col_mode(t_sdl *sdl, bool *mode)
//{
//	t_color col;
//	int 	x;
//	int 	y;
//
//	y = -1;
//	while (++y < sdl->scr_hei && (x = -1))
//	{
//		while (++x < sdl->rt_wid)
//		{
//			col.val = sdl->pixels[y * sdl->rt_wid + x];
//			if (mode[MD_GRAYSCALE])
//				col = ft_grayscale_px(col);
//			if (mode[MD_SEPIA])
//				col = ft_sepia_px(col);
//			if (mode[MD_NEGATIVE])
//				col = ft_negative_px(col);
//			if (mode[MD_INVERTED])
//				col = ft_invert_px(col);
//			sdl->pixels[y * sdl->rt_wid + x] = col.val;
//		}
//	}
//}
//t_color		ft_px_mode(t_color col, int mode)
//{
//			if (mode == MD_GRAYSCALE)
//				return (ft_grayscale_px(col));
//			else if (mode == MD_SEPIA)
//				return (ft_sepia_px(col));
//			else if (mode == MD_NEGATIVE)
//				return (ft_negative_px(col));
//			else if (mode == MD_INVERTED)
//				return (ft_invert_px(col));
//}

t_color		ft_px_mode(t_color col, t_mode *mode)
{
	t_color	out_col;

	out_col = col;
	while (mode)
	{
		if (mode->id == MD_GRAYSCALE)
			out_col = (ft_grayscale_px(out_col));
		if (mode->id == MD_SEPIA)
			out_col = (ft_sepia_px(out_col));
		if (mode->id == MD_NEGATIVE)
			out_col = (ft_negative_px(out_col));
		if (mode->id == MD_INVERTED)
			out_col = (ft_invert_px(out_col));
		mode = mode->next;
	}
	return (out_col);
}

//t_color		ft_px_mode(t_color col, bool *mode)
//{
//	t_color	out_col;
//
//	out_col = col;
//	if (mode[MD_GRAYSCALE])
//		out_col = (ft_grayscale_px(out_col));
//	if (mode[MD_SEPIA])
//		out_col = (ft_sepia_px(out_col));
//	if (mode[MD_NEGATIVE])
//		out_col = (ft_negative_px(out_col));
//	if (mode[MD_INVERTED])
//		out_col = (ft_invert_px(out_col));
//	return (out_col);
//}