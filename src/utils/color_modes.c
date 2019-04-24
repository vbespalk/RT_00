////
//// Created by Viktoriia BESPALKO on 2019-04-24.
////
//# include "rt.h"
//# define RED_CH 0.212671
//# define GRE_CH 0.715160
//# define BLU_CH 0.072169
//
//t_color  grayscale_px(Uint8 r, Uint8 g, Uint8 b)
//{
//    Uint8   v;
//    t_color col;
//
//    v = (Uint8)(RED_CH * r + GRE_CH * g + BLU_CH * b);
//    col.argb[0] = v;
//    col.argb[1] = v;
//    col.argb[2] = v;
//    col.argb[3] = 0xFF;
//    return (col);
//}
//
//t_color  sepia_px(Uint8 r, Uint8 g, Uint8 b)
//{
//    t_color col;
//
//    col.argb[0] = (Uint8)L_X(r * .393 + g * .769 + b * .189, 0xFF);
//    col.argb[1] = (Uint8)L_X(r * .349 + g * .686 + b * .168, 0xFF);
//    col.argb[2] = (Uint8)L_X(r * .272 + g * .534 + b * .131, 0xFF);
//    col.argb[3] = 0xFF;
//    return (col);
//}
//
//void	mode_grey(t_sdl *sdl, int x, int y)
//{
//    Uint32	pixel;
//    Uint8	rgb[3];
//    t_color col;
//
//    while (++y < sdl->scr_hei && (x = -1))
//    {
//        while (++x < sdl->scr_wid)
//        {
//            pixel = sdl->pixels[y * sdl->scr_wid + x];
//            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
//            {
//                rgb[0] = (Uint8)(pixel >> 24);
//                rgb[1] = (Uint8)(pixel >> 16 & 0xFF);
//                rgb[2] = (Uint8)(pixel >> 8 & 0xFF);
//            }
//            else
//            {
//                rgb[0] = (Uint8)(pixel & 0xFF);
//                rgb[1] = (Uint8)(pixel >> 8 & 0xFF);
//                rgb[2] = (Uint8)(pixel >> 16 & 0xFF);
//            }
//            col = grayscale_px(rgb[0], rgb[1], rgb[2]);
//            sdl->pixels[y * sdl->scr_wid + x] = col.val;
//        }
//    }
//}
//
//void	mode_sepia(t_sdl *sdl, int x, int y)
//{
//    Uint32	pixel;
//    Uint8	in_rgb[3];
//    Uint8	out_rgb[3];
//
//    while (++y < sdl->scr_hei && (x = -1))
//    {
//        while (++x < sdl->scr_wid)
//        {
//            pixel = sdl->pixels[y * sdl->scr_wid + x];
//            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
//            {
//                in_rgb[0] = pixel >> 24;
//                in_rgb[1] = pixel >> 16 & 0xFF;
//                in_rgb[2] = pixel >> 8 & 0xFF;
//            }
//            else
//            {
//                in_rgb[0] = pixel & 0xFF;
//                in_rgb[1] = pixel >> 8 & 0xFF;
//                in_rgb[2] = pixel >> 16 & 0xFF;
//            }
//            sdl->pixels[y * sdl->scr_wid + x] = sepia_px(in_rgb[0], in_rgb[1], in_rgb[2]).val;
//        }
//    }
//}
//
//t_color  negative_px(Uint8 r, Uint8 g, Uint8 b)
//{
//    t_color col;
//
//    col.argb[0] = (Uint8)(0xFF - r);
//    col.argb[1] = (Uint8)(0xFF - g);
//    col.argb[2] = (Uint8)(0xFF - b);
//    col.argb[3] = (Uint8)0xFF;
//    return (col);
//}
//
//void	mode_negative(t_sdl *sdl, int x, int y)
//{
//    Uint32	pixel;
//    Uint8	in_rgb[3];
//    Uint8	out_rgb[3];
//
//    while (++y < sdl->scr_hei && (x = -1))
//    {
//        while (++x < sdl->scr_wid)
//        {
//            pixel = sdl->pixels[y * sdl->scr_wid + x];
//            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
//            {
//                in_rgb[0] = pixel >> 24;
//                in_rgb[1] = pixel >> 16 & 0xFF;
//                in_rgb[2] = pixel >> 8 & 0xFF;
//            }
//            else
//            {
//                in_rgb[0] = pixel & 0xFF;
//                in_rgb[1] = pixel >> 8 & 0xFF;
//                in_rgb[2] = pixel >> 16 & 0xFF;
//            }
//            sdl->pixels[y * sdl->scr_wid + x] = negative_px(in_rgb[0], in_rgb[1], in_rgb[2]).val;
//        }
//    }
//}
//
//t_color  invert_px(Uint8 r, Uint8 g, Uint8 b)
//{
//    t_vector 	hsv;
//    t_color col;
//
//    hsv = rgb_to_hsv(r / 255.0f, g / 255.0f, b / 255.0f);
//    col.argb[0] = (Uint8)(0xFF - r);
//    col.argb[1] = (Uint8)(0xFF - g);
//    col.argb[2] = (Uint8)(0xFF - b);
//    col.argb[3] = (Uint8)0xFF;
//    // hsv[0] -= 30;
//    hsv[0] = (int)(hsv[0] + 180.0f + .5) % 360;
//    col = hsv_to_rgb(hsv[0], hsv[1], hsv[2]);
//    return (col);
//}
//
///*
//** SMTH WRONG WITH YELLOW THEN MORE WHEN 1 ITERATION
//*/
//
//void	mode_inverted(t_sdl *sdl, int x, int y)
//{
//    Uint32		pixel;
//    float		in_rgb[3];
//    t_vector 	hsv;
//
//    while (++y < sdl->scr_hei && (x = -1))
//    {
//        while (++x < sdl->scr_wid)
//        {
//            pixel = sdl->pixels[y * sdl->scr_wid + x];
//            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
//            {
//                in_rgb[0] = pixel >> 24;
//                in_rgb[1] = pixel >> 16 & 0xFF;
//                in_rgb[2] = pixel >> 8 & 0xFF;
//            }
//            else
//            {
//                in_rgb[0] = pixel & 0xFF;
//                in_rgb[1] = pixel >> 8 & 0xFF;
//                in_rgb[2] = pixel >> 16 & 0xFF;
//            }
//            hsv = rgb_to_hsv(in_rgb[0] / 255.0f, in_rgb[1] / 255.0f, in_rgb[2] / 255.0f);
//            // hsv[0] -= 30;
//            hsv[0] = (int)(hsv[0] + 180.0f + .5) % 360;
//            pixel = hsv_to_rgb(sdl, hsv[0], hsv[1], hsv[2]);
//            sdl->pixels[y * sdl->scr_wid + x] = pixel;
//        }
//    }
//    t_vector t1 = {8.25, 34.36, 5.42};
//    void *ptr1;
//    void *ptr2;
//    void *ptr3;
//    printf("%p\n", &t1);
//    ptr1 = &t1;
//    printf("ptr %p\n", ptr1);
//    ptr2 = &(t1) + 4;
//    printf("ptr2 %p\n", ptr2);
//    ptr3 = &t1 + 2 * sizeof(int);
//    printf("ptr3 %p\n", ptr3);
//    t1 = (t_vector){*(float *)(ptr1), *(float *)(ptr2), *(float *)(ptr3)};
//    printf("t1 %f,%f,%f\n", t1[0], t1[1], t1[2]);
//    // for (int i = 0; i < 20; ++i)
//    // {
//    // in_rgb[0] = L_X(rand() % 255, 255);
//    // in_rgb[1] = L_X(rand() % 255, 255);
//    // in_rgb[2] = L_X(rand() % 255, 255);
//    // in_rgb[0] = 0;
//    // in_rgb[1] = 0;
//    // in_rgb[2] = 255;
//    // printf("rgb st  %f,%f,%f\n", in_rgb[0], in_rgb[1], in_rgb[2]);
//    // hsv = rgb_to_hsv(in_rgb[0] / 255.0f, in_rgb[1] / 255.0f, in_rgb[2] / 255.0f);
//    // printf("hsv %f,%f,%f\n", hsv[0], hsv[1], hsv[2]);
//    // hsv[0] = (int)(hsv[0] + 180) % 360;
//    // printf("inv hsv %f,%f,%f\n", hsv[0], hsv[1], hsv[2]);
//    // pixel = hsv_to_rgb(sdl, hsv[0], hsv[1], hsv[2]);
//    // in_rgb[0] = pixel & 0xFF;
//    // in_rgb[1] = pixel >> 8 & 0xFF;
//    // in_rgb[2] = pixel >> 16 & 0xFF;
//    // printf("rgb inv %f,%f,%f\n", in_rgb[0], in_rgb[1], in_rgb[2]);
//    // }
//
//}