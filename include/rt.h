/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 11:57:36 by domelche          #+#    #+#             */
/*   Updated: 2019/01/31 18:18:51 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H

# define RTV1_H

# include <stdio.h>

# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <stdint.h>
# include <time.h>
# include "libft.h"
# include "libpnt.h"

# define WIN_WIDTH		1200.0
# define WIN_HEIGHT		700.0

# define CLOSE_MASK		0L
# define CLOSE_NOTIFY	17

# define FOV_MIN		60.0
# define FOV_MAX		120.0

# define BRIGHT_UNIT	20000.0

# define DEPTH			10

# define THREADS		8

# define KOEF			0
# define DBL			1
# define STR			2
# define PNT			3
# define COLOR			4

# define FTSA_GLOBALLY	0
# define FTSA_IN_SCOPE	1

# define ESC            0X35
# define ARR_UP         0X7E
# define ARR_DOWN       0X7D
# define ARR_RIGHT      0X7C
# define ARR_LEFT       0X7B
# define R              0X0F
# define PLUS           0X45
# define MINUS          0X4E
# define C              0X08

typedef uint8_t			t_byte;

typedef union			u_color
{
	int					val;
	unsigned char		argb[4];
}						t_color;

typedef enum			e_ltype
{
	POINT,
	DIRECT,
	PARALLEL
}						t_ltype;

typedef struct			s_light
{
	t_ltype				type;
	t_color				color;
	double				bright;
	t_point3			origin;
	t_point3			direct;
}						t_light;

typedef struct			s_camera
{
	double				alpha;
	double				beta;
	double				gamma;
	double				fov;
	double				start_refr;
	t_point3			origin;
	t_point3			direct;
	t_point3			vs_start_point;
	t_point3			vs_start_vec;
	t_point3			vs_x_step_vec;
	t_point3			vs_y_step_vec;
}						t_camera;

typedef struct			s_scene
{
	t_color				bg_color;
	char				*name;
	t_list				*lights;
	t_list				*objs;
	t_camera			*cam;
}						t_scene;

typedef struct			s_env
{
	// some drawing stuff here

	t_scene				*scn;
}						t_env;

/*
**	--------------------------------- objects ----------------------------------
*/

typedef struct			s_object
{
	t_color				color;
	double				ambnt;
	double				diff;
	double				spclr;
	double				s_blur;
	double				refr;
	double				trans;
	double				t_blur;
	double				phong;

/*
**	figure, one of the objects, listed bellow
*/
	void				*fig;

	int					(*ft_is_reachable)
							(void *fig, t_point3 origin, t_point3 direct);
	t_point3			(*ft_collide)
							(void *fig, t_point3 origin, t_point3 direct);
	int					(*ft_is_inside)(void *fig, t_point3 point);
	t_point3			(*ft_get_norm)(void *fig, t_point3 coll);
	t_point3			translate;
	t_point3			rotate;
}						t_object;

typedef struct			s_plane
{
	t_point3			origin;
	t_point3			norm;
}						t_plane;

typedef struct			s_sphere
{
	double				radius;
	t_point3			origin;
}						t_sphere;

typedef struct			s_cone
{
	double				base_rad;
	double				vert_rad;
	double				bv_dist;
	double				side_norm_angle;
	t_point3			base;
	t_point3			vert;
	t_point3			bv;
	t_point3			main_vert;
}						t_cone;

/*
**	----------------------------------------------------------------------------
*/

/*
typedef struct			s_collision
{
	t_color				illum_color;
	t_color				phong_color;
	double				phong;
	t_object			*o;
	t_point3			coll_pnt;
	t_point3			norm;
	t_point3			spclr_vec;
	t_point3			trans_vec;
}						t_coll;
*/



#endif
