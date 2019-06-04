/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 21:50:08 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/26 15:30:10 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H

# define RT_H

/*
**	includes
*/

# include <stdio.h>
# include <pthread.h>
# include <stdint.h>
# include <time.h>
# include <stdarg.h>

# include "json.h"

/*
**	MACOSX
*/

# if defined(__MACH__) && defined(__APPLE__)

#  include "SDL.h"
#  include "SDL_image.h"
#  include "SDL_syswm.h"

/*
**	LINUX
*/

# else

#  include <SDL2/SDL.h>
#  include <SDL2/SDL_image.h>

# endif

/*
**	window and camera
*/

# define SCR_WID		950
# define SCR_HEI		548
# define GUI_WIDTH		220
# define FOV			1.570796
# define FOV_MIN		60.0f
# define FOV_MAX		120.0f
# define EQN_EPS		1e-16
# define MIN_DPTH		1
# define MAX_DPTH		20

/*
**	macro functions
*/
# define MINV(a, b) ({typeof(a) _a = (a);typeof(b) _b = (b);_a < _b ? _a : _b;})
# define MAXV(a, b) ({typeof(a) _a = (a);typeof(b) _b = (b);_a > _b ? _a : _b;})
# define DEG_TO_RAD(x) ((x) * (float)M_PI / 180.0f)
# define RAD_TO_DEG(x) ((x) * 180.0f / M_PI)
# define IN_RANGE(x, left, right) (((x) >= (left)) && ((x) <= (right)))
# define IS_ZERO(x) (((x) > -EQN_EPS) && ((x) < EQN_EPS))
# define CLAMP(x, min, max) ((x) < (min) ? (min) : (x > (max) ? (max) : (x)))
# define ANGL_R(x, pi) {IN_RANGE(x, 0, pi) ? x : (x < 0 ? x + pi : x - pi)}

/*
**	color modes
*/

# define MD_COLOR		0
# define MD_GRAYSCALE	SDLK_g
# define MD_SEPIA		SDLK_u
# define MD_NEGATIVE	SDLK_h
# define MD_INVERTED	SDLK_i

/*
**	camera
*/

# define FOV_MIN		60.0f
# define FOV_MAX		120.0f

/*
**	tracing
*/

# define BRIGHT_UNIT	20000.0f
# define DEFAULT_REFR	1.0f
# define SHIFT			0.1f

# define RM_SPCLR		0
# define RM_TRANS		1

# define IT_NEG			-1
# define IT_VOID		0
# define IT_POS_RT		1
# define IT_POS_RF		2

# define ROTAT_F		DEG_TO_RAD(5)
# define TRANS_F		10.0f
# define SCALE_F		0.1f
# define SCANG_F		0.05f
# define MIN_R			0.00005f
# define MAX_R			FLT_MAX
# define BOX_FACES		6
# define EXP_COLOR		0
# define EXP_TEXTR		1
# define EXP_CHCKR		2
# define EXP_NOISE		3

/*
**	system
*/

# define THREADS		8

/*
** LATTICE NOISE
*/

# define LTABLE_SIZE		256
# define LTABLE_MASK		LTABLE_SIZE - 1
# define TURBULANCE		 	"turbulance"
# define FRACTAL_SUM		"fractal"
# define TEX_LATTICE		"lattice"
# define TEX_GR_MRBL		"gray_marble"
# define TEX_BL_MRBL		"blue_marble"
# define TEX_WM_MRBL		"warm_marble"
# define TEX_GN_MRBL		"green_marble"
# define TEX_RD_MRBL		"red_marble"
# define TEX_SANDSTN		"sandstone"
# define RAMP_GR_MRBL		"./texture/procedural/GrayMarbleRamp.jpg"
# define RAMP_GN_MRBL		"./texture/procedural/GreenMarbleRamp.png"
# define RAMP_BL_MRBL		"./texture/procedural/BlueMarbleRamp.jpg"
# define RAMP_WM_MRBL		"./texture/procedural/sandstone_ramp2.jpg"
# define RAMP_RD_MRBL		"./texture/procedural/RedMarbleRamp.png"
# define RAMP_SANDSTN		"./texture/procedural/sandstone_ramp1.jpg"

# define SMPL_NMB			6

/*
** DEFAULT SKYBOX PATH
*/
# define SKBX_NEGX			"./texture/skybox/thunder/negx.tga"
# define SKBX_NEGY			"./texture/skybox/thunder/negy.tga"
# define SKBX_NEGZ			"./texture/skybox/thunder/negz.tga"
# define SKBX_POSX			"./texture/skybox/thunder/posx.tga"
# define SKBX_POSY			"./texture/skybox/thunder/posy.tga"
# define SKBX_POSZ			"./texture/skybox/thunder/posz.tga"

static const unsigned char	g_permutation_table[LTABLE_SIZE] =
{
	225, 155, 210, 108, 175, 199, 221, 144, 203, 116, 70, 213, 69, 158, 33,
	252, 5, 82, 173, 133, 222, 139, 174, 27, 9, 71, 90, 246, 75, 130, 91, 191,
	169, 138, 2, 151, 194, 235, 81, 7, 25, 113, 228, 159, 205, 253, 134, 142,
	248, 65, 224, 217, 22, 121, 229, 63, 89, 103, 96, 104, 156, 17, 201, 129,
	36, 8, 165, 110, 237, 117, 231, 56, 132, 211, 152, 20, 181, 111, 239, 218,
	170, 163, 51, 172, 157, 47, 80, 212, 176, 250, 87, 49, 99, 242, 136, 189,
	162, 115, 44, 43, 124, 94, 150, 16, 141, 247, 32, 10, 198, 223, 255, 72,
	53, 131, 84, 57, 220, 197, 58, 50, 208, 11, 241, 28, 3, 192, 62, 202,
	18, 215, 153, 24, 76, 41, 15, 179, 39, 46, 55, 6, 128, 167, 23, 188,
	106, 34, 187, 140, 164, 73, 112, 182, 244, 195, 227, 13, 35, 77, 196, 185,
	26, 200, 226, 119, 31, 123, 168, 125, 249, 68, 183, 230, 177, 135, 160, 180,
	12, 1, 243, 148, 102, 166, 38, 238, 251, 37, 240, 126, 64, 74, 161, 40,
	184, 149, 171, 178, 101, 66, 29, 59, 146, 61, 254, 107, 42, 86, 154, 4,
	236, 232, 120, 21, 233, 209, 45, 98, 193, 114, 78, 19, 206, 14, 118, 127,
	48, 79, 147, 85, 30, 207, 219, 54, 88, 234, 190, 122, 95, 67, 143, 109,
	137, 214, 145, 93, 92, 100, 245, 0, 216, 186, 60, 83, 105, 97, 204, 52
};

# define PERM(x)		(g_permutation_table[x & LTABLE_MASK])
# define INDEX(x, y, z)	(PERM(x + PERM(y + PERM(z))))

# if SDL_BYTEORDER == SDL_BIG_ENDIAN

#  define RMASK			0xff000000U
#  define GMASK			0x00ff0000U
#  define BMASK			0x0000ff00U
#  define AMASK			0x000000ffU
#  define SWAP32(X)		(X)

# else

#  define RMASK			0x000000ffU
#  define GMASK			0x0000ff00U
#  define BMASK			0x00ff0000U
#  define AMASK			0xff000000U
#  define SWAP32(X)		SDL_Swap32(X)

# endif

/*
** GUI STUFF - includes, structures, defines etc.
*/

# define MLC_TEST(t, msg) if (!(t)) {ft_putendl(msg);exit(-1);}
# define ON_ERR "Fatal error at "
# define ON_WARN "Warning at "

# define DEFAULT_BUTTTON_WIDTH 93
# define DEFAULT_BUTTTON_HEIGHT 20
# define ARROW_BUTTON_WIDTH 30
# define ARROW_BUTTON_HEIGHT 20
# define OBJ_EDIT_BTN_WIDTH 65
# define OBJ_EDIT_BTN_HEIGHT 20
# define TEXTURE_EDIT_BTN_W 50
# define TEXTURE_EDIT_BTN_H 17
# define GUI_WIDTH 220
# define GUI_HEIGHT 250 * 1290 / 570
# define BUTTONS_AMOUNT 52
# define BTN_ID_SHIFT 100

# define DEFAULT_GUI_TEX_NAME "./texture/gui_texture/gui_tex.png"
# define DEFAULT_SCRSHT_NAME "screenshots/RT ScreenShot "

typedef enum	e_bool
{
	false,
	true
}				t_bool;

/*
** buttons ids enum
*/

extern const SDL_Rect g_btn_containers[];

typedef enum	e_btn_code
{
	SCREENSHOT = 1,
	GRAYSCALE,
	SEPIA,
	NEGATIVE,
	INVERTED,
	CAMERA_MODE,
	FOV_DOWN, FOV_UP,
	TRANS_OX_DOWN, TRANS_OX_UP,
	TRANS_OY_DOWN, TRANS_OY_UP,
	TRANS_OZ_DOWN, TRANS_OZ_UP,
	ROT_OX_DOWN, ROT_OX_UP,
	ROT_OY_DOWN, ROT_OY_UP,
	ROT_OZ_DOWN, ROT_OZ_UP,
	SKYBOX,
	DELETE_OBJ, NEGATIVE_OBJ, REACT_NEGATIVE,
	RADIUS_DOWN, RADIUS_UP,
	HEIGHT_DOWN, HEIGHT_UP,
	REFL_DOWN, REFL_UP,
	S_BLUR_DOWN, S_BLUR_UP,
	TRANSP_DOWN, TRANSP_UP,
	T_BLUR_DOWN, T_BLUR_UP,
	REFR_DOWN, REFR_UP,
	DIFFUSE_DOWN, DIFFUSE_UP,
	AMBIENT_DOWN, AMBIENT_UP,
	COLOR, TEXTURE, CHECKER, NOISE,
	TEX_1, TEX_2, TEX_3,
	TEX_4, TEX_5, TEX_6
}				t_btn_code;

typedef struct s_environment	t_env;
typedef struct s_sdl			t_sdl;
typedef struct s_procedural		t_procedural;
typedef struct s_object			t_object;
typedef struct s_collision		t_coll;

typedef Uint32	(*t_fun_tab[4])(t_object *o, void *t, t_vector pnt);

typedef struct	s_gui
{
	SDL_Texture	*gui_texture;
	SDL_Surface	*gui_surface;
	int			h;
	int			w;
}				t_gui;

int				gui_init(t_sdl *sdl);
void			ft_gui(t_env *e, uint32_t btn_id);

/*
** buttons event handlers
*/

uint32_t		mouse_on_btn(const int32_t x, const int32_t y, t_env *e);
uint32_t		handle_button(t_env *e, uint32_t btn_id);

/*
** gui utils
*/

int				make_screenshot(t_env *e);
uint32_t		other_buttons(t_env *e, const uint32_t id);
uint32_t		color_filter(t_env *e, const uint32_t id);
uint32_t		translate(t_env *e, const uint32_t id);
uint32_t		rotate(t_env *e, const uint32_t id);
uint32_t		texture_editing(t_env *e, uint32_t id);

/*
** Gui stuff end
*/

/*
** some interface defines
*/

typedef uint8_t	t_byte;

typedef union	u_color
{
	Uint32			val;
	t_byte			argb[4];
}				t_color;

typedef enum	e_ltype
{
	L_POINT,
	L_DIRECT,
	L_PARALLEL
}				t_ltype;

typedef struct	s_texture
{
	char			*path;
	SDL_Surface		*surface;
}				t_texture;

typedef enum	e_smooth
{
	SMOOTH_1X,
	SMOOTH_4X,
	SMOOTH_9X
}				t_smooth;

typedef struct	s_lattice_noise
{
	float			*value_table;
	float			(*ft_generate_noise)
					(t_vector pnt, const float *val_table);
}				t_lattice;

struct			s_procedural
{
	t_lattice		*noise_ptr;

	float			octaves;
	float			gain;
	float			lacunarity;
	float			bounds[2];

	t_color			color;
	float			scale;
	float			min_max[2];
	float			pertubation;
	char			*ramp_id;
	SDL_Surface		*ramp;
	float			(*ft_noise_value)
					(t_procedural *tex, t_vector hit);
	Uint32			(*ft_get_color)
					(t_procedural *tex, t_vector hit);
};

typedef struct	s_checkbrd
{
	unsigned int	size;
	Uint32			color[2];
	t_procedural	*noise[2];
}				t_checkbrd;

/*
** OBJECTS
*/

struct			s_object
{
	Uint32			id;
	float			dist;
	t_bool			composed;

	t_vector		translate;
	t_vector		rotate;
	t_matrix		transform;
	t_matrix		inverse;

	void			*fig;

	int				is_neg;
	t_bool			react_neg;
	float			ambnt;
	float			diff;
	float			spclr;
	float			s_blur;
	float			refr;
	float			trans;
	float			t_blur;
	float			phong;
	t_color			color;

	char			*texture_id;
	void			*tex_pnt;
	SDL_Surface		*texture;
	t_procedural	*noise;
	t_checkbrd		*checker;
	int				exposure;

	float			(*ft_collide)
			(t_list **objs, t_object *obj,
			t_coll *coll, t_vector od[2]);

	int				(*ft_is_inside)(t_object *o, t_vector pnt);
	t_vector		(*ft_get_norm)(void *fig, t_matrix *inv_m, t_vector coll);

	int				(*ft_translate)
			(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m);
	int				(*ft_rotate)
			(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m);
	int				(*ft_scale)
			(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m);
	int				(*ft_scale_height)
			(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m);

	Uint32			(*ft_mapping)
			(t_object *o, void *tex, t_vector coll);
	Uint32			(*ft_checker)
			(t_object *o, void *tex, t_vector coll);
	Uint32			(*ft_procedural)
			(t_object *o, void *tex, t_vector coll);
};

typedef struct	s_plane
{
	int				is_in_box;
	float			len_wh[2];
	float			ratio;
}				t_plane;

typedef struct	s_sphere
{
	t_vector		origin;
	float			radius;
}				t_sphere;

typedef struct	s_cone
{
	float			tan;
	float			tan2;
	float			minh;
	float			maxh;
	float			r[2];
	float			texh;

}				t_cone;

typedef struct	s_cylinder
{
	float			r;
	float			maxh;
	float			ratio;
}				t_cylinder;

typedef struct	s_disc
{
	float			in_r;
	float			out_r;
	float			sq_in_r;
	float			sq_out_r;
}				t_disk;

typedef struct	s_box
{
	float			whl[3];
	t_object		*face[BOX_FACES];
	float			scale;
}				t_box;

typedef struct	s_paraboloid
{
	float			r;
	float			maxh;
	float			ratio;
}				t_prbld;

typedef struct	s_torus
{
	float			r_inner;
	float			r_outer;
	float			r_inner2;
	float			r_outer2;

}				t_torus;

typedef struct	s_bounding_box
{
	t_vector		bounds[2];
	t_vector		origin;
	t_vector		cntr;
	t_vector		dgnl;

	t_vector		(*ft_collide)
			(void *fig, t_vector origin, t_vector direct);
	int				(*ft_is_inside)(struct s_object *o, t_vector pnt);
	t_vector		(*ft_get_norm)(void *fig, t_matrix *inv_m, t_vector coll);

	void			(*ft_translate)
			(Uint32 key, void *fig, t_vector *translate);
	void			(*ft_rotate)
			(Uint32 key, void *fig, t_vector *rotate);
	void			(*ft_scale)
			(Uint32 key, void *fig, float *scale);
}				t_aabb;

typedef struct	s_skybox
{
	t_aabb			*bbx;
	char			*textur_id[BOX_FACES];
	SDL_Surface		*textur[BOX_FACES];
}				t_skybox;

/*
** ENVIRONMENT
*/

typedef struct	s_light
{
	t_ltype			type;
	t_color			color;
	float			bright;
	t_vector		origin;
	t_vector		direct;
}				t_light;

typedef struct	s_camera
{
	t_smooth		smooth;
	t_vector		origin;
	t_vector		direct;
	t_vector		angles;
	float			fov;

	t_vector		vs_start_point;
	t_vector		vs_start_vec;
	t_vector		vs_x_step_vec;
	t_vector		vs_y_step_vec;
	t_object		*inner_o;
}				t_camera;

typedef struct	s_scene
{
	int				depth;
	t_color			bg_color;
	char			*name;
	t_list			*lights;
	t_list			*objs;
	t_list			*textures;
	t_bool			skybox_on;
	t_skybox		*skybox;
	t_camera		*cam;
}				t_scene;

struct			s_sdl
{
	int				scr_wid;
	int				rt_wid;
	int				scr_hei;
	SDL_Window		*window;
	SDL_Texture		*screen;
	SDL_Renderer	*renderer;
	Uint32			*pixels;
	SDL_PixelFormat	*format;
	int				pitch;
	int				event_loop;
	SDL_Rect		rt_cont;
	t_gui			*gui;
};

typedef struct	s_mode
{
	int				id;
	struct s_mode	*next;
}				t_mode;

struct			s_environment
{
	t_scene			*scn;
	float			asp_rat;
	t_object		**pix_obj;
	t_object		*selected;
	t_sdl			*sdl;
	t_mode			*color_mode;
	t_procedural	*smpl[6];
};

/*
** RAY TRACING STAFF
*/

struct			s_collision
{
	int				inside_type;
	t_color			px_color;
	t_color			illum_color;
	t_color			phong_color;
	float			phong;
	float			fresnel;
	t_object		*o;
	t_object		*tex_o;
	t_vector		coll_pnt;
	t_vector		ucoll_pnt;
	t_vector		norm;
	t_vector		spclr_vec;
	t_vector		trans_vec;
};

typedef struct	s_ray
{
	int				stack_i;
	Uint32			pix;
	size_t			stack_size;
	t_coll			*coll;
	t_vector		o;
	t_vector		d;
	t_object		**stack;
}				t_ray;

typedef struct	s_thrarg
{
	int				i;
	t_env			*e;
}				t_thrarg;

/*
** GRAPH_TRANSFORMATION LIBRARY
*/

void			img_pixel_put(t_sdl *sdl, int x, int y, unsigned int color);
Uint32			get_rgb(t_sdl *sdl, Uint8 red, Uint8 green, Uint8 blue);
int				delete_obj(t_list **obj_lst, Uint32 id);

/*
** init_sdl.c
*/

int				sdl_init(t_sdl *sdl, char *name);
int				event_handler(t_env *env, uint32_t *btn_id);
int				sdl_error(char *message);
int				get_format_data(t_sdl *sdl);
int				sdl_img_error(char *message);

/*
** sdl_cleanup.c
*/

void			cleanup_sdl_window(SDL_Window **win);
void			cleanup_sdl_texture(SDL_Texture **tex);
void			cleanup_sdl_surface(SDL_Surface **surf);
void			cleanup_sdl_render(SDL_Renderer **rend);
void			on_sdl_close(char *fmt, ...);

/*
** init_env.c
*/

int				init_env
			(t_env *e, t_scene *scene, t_object **obj_pix, t_sdl *sdl);

/*
**	hit.c
*/

void			ft_get_refrs(t_ray *ray, float (*refr)[2]);
void			ft_handle_hit(t_ray *ray, t_object *o);

/*
**	scene.c
*/

t_scene			*ft_scenenew(void);
void			ft_parse_scene(char **content, t_scene *scn);

/*
**	camera.c
*/

t_camera		*ft_cameranew(void);
void			ft_parse_camera(char **content, t_camera *cam);
void			ft_get_start_stack(t_scene *scn);

/*
** cam_transform
*/

int				ft_translate_cam(Uint32 key, t_vector *rot);
int				ft_rotate_cam(Uint32 key, t_vector *angles);
int				ft_scale_cam(Uint32 key, float *sc_factor);

/*
**	render.c
*/

void			ft_render(t_env *e);
void			*ft_section_handle(void *arg);

/*
**	light.c
*/

void			ft_parse_light(char **content, t_list **lst, Uint32 id);

/*
**	object.c
*/

void			ft_balance_koefs(t_object *o);
t_object		*ft_objectnew(Uint32 id);
void			ft_parse_object
			(char **content, t_list **lst, Uint32 id);
/*
** PLANE
*/

/*
**	plane.c
*/
t_plane			*ft_planenew(t_object *o);
void			*ft_parse_plane(char **content, t_object *o);
int				ft_translate_plane
			(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m);
int				ft_rotate_plane
			(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m);
int				ft_scale_plane
			(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m);

/*
**	plane_utils.c
*/

float			ft_collide_plane
			(t_list **objs, t_object *o, t_coll *coll, t_vector od[2]);
int				ft_is_inside_plane(t_object *o, t_vector pnt);
t_vector		ft_get_norm_plane(void *fig,
			t_matrix *inv_m, t_vector coll);

/*
** DISK
*/
/*
**	disk.c
*/

char			*ft_parse_disk(char **content, t_object *o);
int				ft_translate_disk
			(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m);
int				ft_rotate_disk
			(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m);
int				ft_scale_disk
			(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m);

/*
**	disk_utils.c
*/

float			ft_collide_disk
			(t_list **objs, t_object *o, t_coll *coll, t_vector od[2]);
int				ft_is_inside_disk(t_object *o, t_vector pnt);
t_vector		ft_get_norm_disk(void *fig,
			t_matrix *inv_m, t_vector coll);

/*
** BOX
*/
/*
**	box.c
*/

char			*ft_parse_box(char **content, t_object *o);
int				ft_translate_box
			(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m);
int				ft_rotate_box
			(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m);
int				ft_scale_box
			(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m);
int				ft_scale_hei_null
			(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m);
/*
**	box_utils.c
*/

float			ft_collide_box
			(t_list **objs, t_object *o, t_coll *coll, t_vector od[2]);
int				ft_is_inside_box(t_object *o, t_vector pnt);
t_vector		ft_get_norm_box(void *fig,
			t_matrix *inv_m, t_vector coll);

/*
** aabb.c
*/

t_aabb			*ft_init_aabb
			(t_vector min, t_vector max);
t_vector		ft_collide_aabb
			(void *fig, t_vector origin, t_vector direct);
void			ft_translate_aabb
			(Uint32 key, void *fig, t_vector *transl);
void			ft_scale_aabb
			(Uint32 key, void *fig, float *scale);

/*
** SPHERE
*/

/*
**	sphere.c
*/

void			*ft_parse_sphere
			(char **content, t_object *o);
int				ft_translate_sphere
			(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m);
int				ft_rotate_sphere
			(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m);
int				ft_scale_sphere
			(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m);

/*
**	sphere_utils.c
*/

float			ft_collide_sphere
			(t_list **objs, t_object *o, t_coll *coll, t_vector uod[2]);
int				ft_is_inside_sphere(t_object *o, t_vector pnt);
t_vector		ft_get_norm_sphere(void *fig,
			t_matrix *inv_m, t_vector coll);

/*
** CONE
*/

/*
**	cone.c
*/

void			*ft_parse_cone
			(char **content, t_object *o);
int				ft_translate_cone
			(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m);
int				ft_rotate_cone
			(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m);
int				ft_scale_cone
			(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m);
int				ft_scale_hei_cone
			(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m);

/*
**	cone_utils.c
*/

float			ft_collide_cone
			(t_list **objs, t_object *o, t_coll *coll, t_vector uod[2]);
int				ft_is_inside_cone(t_object *o, t_vector upnt);
t_vector		ft_get_norm_cone(void *fig,
			t_matrix *inv_m, t_vector coll);

/*
**	cone_coll_utils.c
*/

float			ft_get_cone_cides_coll(
					t_list **objs, t_vector v[4][2], float t[2], t_object *obj);
float			ft_get_cone_caps_coll(
					t_list **objs, t_vector v[4][2], t_object *obj);

/*
** CYLINDER
*/

/*
**	cylinder.c
*/

void			*ft_parse_cylinder(char **content, t_object *o);
int				ft_translate_cylinder
			(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m);
int				ft_rotate_cylinder
			(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m);
int				ft_scale_cylinder
			(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m);
int				ft_scale_hei_cylinder
			(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m);

/*
**	cylinder_utils.c
*/

float			ft_collide_cylinder
			(t_list **objs, t_object *o, t_coll *coll, t_vector od[2]);
int				ft_is_inside_cylinder(t_object *o, t_vector pnt);
t_vector		ft_get_norm_cylinder(void *fig,
			t_matrix *inv_m, t_vector coll);

/*
**	cylinder_coll_utils.c
*/

float			ft_get_clnd_closer_pnt(
					const float *t, const t_vector *hit,
					t_coll *coll, t_vector *norms);
float			ft_get_clnd_caps_coll(
					t_list **objs, t_vector v[4][2], t_object *obj);
float			ft_get_clnd_cides_coll(
					t_list **objs, t_vector v[4][2], float *t, t_object *obj);

/*
** PARABOLOID
*/
/*
**	paraboloid.c
*/

char			*ft_parse_prbld(char **content, t_object *o);
int				ft_translate_prbld
			(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m);
int				ft_rotate_prbld
			(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m);
int				ft_scale_prbld
			(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m);
int				ft_scale_hei_prbld
			(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m);

/*
**	paraboloid_utils.c
*/

float			ft_collide_prbld(t_list **objs, t_object *o,
			t_coll *coll, t_vector od[2]);
int				ft_is_inside_prbld(t_object *o, t_vector pnt);
t_vector		ft_get_norm_prbld(void *fig,
			t_matrix *inv_m, t_vector coll);

/*
**	paraboloid_utils.c
*/

float			ft_get_prbld_caps_coll(
					t_list **objs, t_vector v[4][2], t_object *obj);
double			ft_get_prbld_cides_coll(
					t_list **objs, t_vector v[4][2],
					double *t, t_object *obj);

/*
** TORUS
*/

/*
**	torus.c
*/

char			*ft_parse_torus(char **content, t_object *o);
int				ft_translate_torus(Uint32 key, t_object *o,
			t_matrix *tr_m, t_matrix *inv_m);
int				ft_rotate_torus(Uint32 key, t_object *o,
			t_matrix *tr_m, t_matrix *inv_m);
int				ft_scale_torus(Uint32 key, t_object *o,
			t_matrix *tr_m, t_matrix *inv_m);

/*
**	torus_utils.c
*/

float			ft_collide_torus(t_list **objs, t_object *obj,
			t_coll *coll, t_vector od[2]);
int				ft_is_inside_torus(t_object *o, t_vector pnt);
t_vector		ft_get_norm_torus(void *fig,
			t_matrix *inv_m, t_vector coll);

/*
**	ray.c
*/

t_color			ft_trace_ray(t_thrarg *parg, int x, int y);
t_color			ft_throw_ray(t_thrarg *parg, t_ray *ray, int depth);
t_color			ft_throw_rays(t_thrarg *parg, t_ray *ray, float num[2]);

/*
**	ray_utils.c
*/

void			ft_init_ray(
					t_ray *ray_prev, t_ray *ray,
					t_vector *o, t_vector *d);
t_vector		ft_change_blur_vec(
					t_vector norm, t_vector vec, float angle);
t_color			ft_sum_colors(
					t_coll *coll, t_color color_s, t_color color_t);
t_color			ft_blind(t_env *e, t_color color, t_ray *ray);

/*
**	illumination.c
*/

void			ft_illuminate(t_thrarg *parg, t_coll *coll);

/*
**	illumination_utils.c
*/

float			ft_get_illumination(
					t_scene *scn, t_vector o, t_vector d, t_light *l);
void			ft_affect_illumination(
					t_coll *coll, t_light *l,
					t_vector ldir, float bright_coef);

/*
**	collision.c
*/

t_coll			ft_get_collision(t_thrarg *arg, t_ray *ray);

/*
**	collision_utils.c
*/

int				ft_inside_type(t_list **objs, t_vector point);
t_object		*ft_get_inner_object(t_list **objs, t_vector point);
t_object		*ft_inside_obj(t_list **objs, t_vector point,
							t_object *(*ft_choose)(t_list **, t_vector));
void			ft_choose_object(t_list **objs, t_object *obj, t_coll *coll);
int				ft_is_invisible(t_object *obj, int inside_type);

/*
**	utils.c
*/

t_color			ft_apply_phong(t_color color, float bright,
			t_color light_color);
t_color			ft_scale_color(t_color color, float k);
t_color			ft_add_colors(t_color c1, t_color c2);

/*
** key.c
*/

int				ft_switch_col_mode(t_env *e, Sint32 sum);
int				ft_set_exposure(Sint32 sum, t_object *o, t_env *e);
int				ft_mod_depth(Sint32 sum, int *depth);

/*
** textures.c
*/

SDL_Surface		*init_texture(t_list **textures, t_sdl *sdl, char *id);
t_texture		*load_texture(t_sdl *sdl, char *path);

/*
** sphere_mapping.c
*/

Uint32			ft_map_sphere(t_object *o, void *tex, t_vector coll);
Uint32			ft_checker_sph(t_object *o, void *tex, t_vector coll);
Uint32			ft_procedural_sph(t_object *o, void *tex, t_vector coll);
/*
** cylinder_mapping.cf
*/

Uint32			ft_map_clndr(t_object *o, void *tex, t_vector coll);
Uint32			ft_checker_cyl(t_object *o, void *tex, t_vector coll);
Uint32			ft_procedural_cyl(t_object *o, void *tex, t_vector coll);

/*
** prbld_mapping.c
*/

Uint32			ft_procedural_prbld(t_object *o, void *tex, t_vector coll);
Uint32			ft_checker_prbld(t_object *o, void *tex, t_vector coll);
Uint32			ft_map_prbld(t_object *o, void *tex, t_vector hit);

/*
** cone_mapping.c
*/

Uint32			ft_map_cone(t_object *o, void *tex, t_vector coll);
Uint32			ft_checker_cone(t_object *o, void *tex, t_vector coll);
Uint32			ft_procedural_cone(t_object *o, void *tex, t_vector coll);
/*
** plane_mapping.c
*/

Uint32			ft_map_plane(t_object *o, void *tex, t_vector coll);
Uint32			ft_checker_pln(t_object *o, void *tex, t_vector coll);
Uint32			ft_procedural_pln(t_object *o, void *tex, t_vector coll);
Uint32			ft_map_box(t_object *o, void *tex, t_vector hit);
Uint32			ft_checker_box(t_object *o, void *tex, t_vector coll);
Uint32			ft_procedural_box(t_object *o, void *tex, t_vector hit);

/*
** disk_mapping.c
*/

Uint32			ft_map_disk(t_object *o, void *tex, t_vector hit);
Uint32			ft_checker_dsk(t_object *o, void *tex, t_vector coll);
Uint32			ft_procedural_dsk(t_object *o, void *tex, t_vector coll);

/*
** torus_mapping.c
*/

Uint32			ft_procedural_tor(t_object *o, void *tex, t_vector coll);
Uint32			ft_checker_tor(t_object *o, void *tex, t_vector coll);
Uint32			ft_map_torus(t_object *o, void *tex, t_vector hit);

/*
** skybox.c
*/

void			ft_parse_skybox(char **content, t_skybox **sky);
t_color			ft_apply_sky(t_skybox *skybox,
			t_vector origin, t_vector direct);
void			ft_skybox_del(t_skybox **sk);
int				ft_load_sky_tex(t_skybox **skybox,
			t_list **tex, t_sdl *sdl);
int				ft_switch_skybox(t_sdl *sdl, t_scene *scn);

/*
** map_skybox.c
*/

Uint32			ft_map_skybox(t_aabb *bbx,
			SDL_Surface *tex[6], t_vector hit);

/*
** equations.c
*/

int				ft_solve_quartic(double coef[5], double res[4]);
int				ft_solve_cubic(const double coef[4], double res[3]);

/*
** quadratic.c
*/

int				ft_solve_sq(double a, double b, double c, double res[2]);
int				ft_solve_qdr(float a, float b, float c, float res[2]);

/*
** lattice_noise.c
*/
void			ft_init_value_table(float **vtable, unsigned int seed);
float			ft_linear_noise(t_vector point, const float *value_table);
float			ft_cubic_noise(t_vector point, const float *value_table);
void			ft_lattice_bounds(int octaves, float gain, float bounds[2]);

/*
** noise_val.c
*/

float			ft_fractal_noise(t_procedural *tex, t_vector hit);
float			ft_turbulance_noise(t_procedural *tex, t_vector hit);
Uint32			ft_wrapped_noise_col(t_procedural *tex, t_vector hit);
Uint32			ft_ramp_noise_col(t_procedural *tex, t_vector hit);

/*
** init_procedural.c
*/

void			ft_parse_procedural(char **content, t_procedural **tex);
void			ft_init_lattice(t_procedural **tex,
			char *function, unsigned int seed);
void			ft_set_procedural(t_procedural **tex,
			const char *smpl, Uint32 col);
void			ft_load_noise_ramp(t_procedural *n,
			t_list **textures, t_sdl *sdl);
void			ft_noise_del(t_procedural **noise);

/*
** procedural_type.c
*/

void			ft_init_type(t_procedural *tex, const char *name);
void			ft_null_lattice(t_procedural *tex);

/*
** init_checker.c
*/

void			ft_parse_checker(char **content, t_checkbrd **tex);
void			ft_set_checker(t_checkbrd **chkr, Uint32 col);
void			ft_checker_del(t_checkbrd **checker);

/*
** color_modes.c
*/
t_color			ft_grayscale_px(t_color in_col);
t_color			ft_sepia_px(t_color in_col);
t_color			ft_negative_px(t_color in_col);
void			ft_col_mode(t_sdl *sdl, Sint32 mode);
t_color			ft_px_mode(t_color col, t_mode *mode);

/*
** inv_mode.c
*/

t_vector		hsv_to_rgb(float h, float s, float v);
t_vector		rgb_to_hsv(float r, float g, float b);
t_color			ft_invert_px(t_color in_col);

/*
** FROM MY LIBFT
*/
void			ft_usage(char *message);

/*
**	Structures for norminette
*/

typedef struct	s_clnd_coll
{
	t_list		**objs;
	t_object	*obj;
	t_vector	pnts[3][2];
	t_vector	(*v)[2];
	float		t[2];
	int			i[2];
}				t_clnd_coll;

typedef struct	s_cone_coll
{
	t_list		**objs;
	t_object	*obj;
	t_vector	pnts[3][2];
	t_vector	(*v)[2];
	float		*t;
	int			i[2];
}				t_cone_coll;

#endif
