/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 21:50:08 by vbespalk          #+#    #+#             */
/*   Updated: 2018/08/17 21:50:10 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef rt_h
# define rt_h
# define INFINITY 18446744073709551615
# define SCR_WID 1000
# define SCR_HEI 800
# define SQ_MATR 4
# define POSI "pos("
# define COLO "col("
# define RADI "rad("
# define SIZE "size("
# define DIFU "diffuse("
# define REFL "reflect("
# define DIRE "dir("
# define ROTI "rot("
# define FOV 1.570796
# define ALBEDO 0.18
# define T_COEF 0.0f
# define AMBILI 0.1f
# define NB_THREADS 8
# define L_X(a, b) ({typeof(a) _a = (a);typeof(b) _b = (b);_a >= _b ? _b : _a;})
# define L_N(a, b) ({typeof(a) _a = (a);typeof(b) _b = (b);_a <= _b ? _b : _a;})
# define DEG_TO_RAD(x) ((x) * M_PI / 180.0f)
# define RAD_TO_DEG(x) ((x) * 180.0f / M_PI)

# define CLOSE_MASK		0L
# define CLOSE_NOTIFY	17

# define FOV_MIN		60.0
# define FOV_MAX		120.0

# define BRIGHT_UNIT	20000.0

# define DEFAULT_REFR	1.0f

# define DEPTH			10

# define THREADS		8

# define KOEF			0
# define FLT			1
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

# include <stdio.h>
# include <pthread.h>
# include <math.h>
# include "libft.h"
# include "SDL.h"
# include "SDL_image.h"
# include "SDL_syswm.h"

# include <stdint.h>
# include <time.h>
# include "libpnt.h"

typedef	float		t_matrix[4][4];
typedef uint8_t		t_byte;

typedef union		u_color
{
	int				val;
	t_byte			argb[4];
}					t_color;

typedef enum		e_ltype
{
	POINT,
	DIRECT,
	PARALLEL
}					t_ltype;

/*
** -------------------------------------------OBJECTS-----------------------------------------------
*/

typedef struct		s_object
{
	int				type;
	Uint32			id;
	t_vector		pos; //
	t_vector		rot; //
	unsigned int	size; //
/*
**	transformations
*/	
	t_vector		translate;
	t_vector		rotate;
	float			scale;
/*
**	figure, one of the objects, listed bellow
*/
	void			*fig;
/*
** object propetries
*/
	float			ambnt;
	float			diff;
	float			spclr;
	float			s_blur;
	float			refr;
	float			trans;
	float			t_blur;
	float			phong;

	unsigned int	reflect; // my shiny val

	t_vector		col;
	t_color			color;
/*
** functions for intersection / search etc.
*/
//	int				(*intersect)();
	int				(*ft_is_reachable)
	 					(void *fig, t_vector origin, t_vector direct);
	t_vector		(*ft_collide)
	 					(void *fig, t_vector origin, t_vector direct);
	int				(*ft_is_inside)(void *fig, t_vector point);
	t_vector		(*ft_get_norm)(void *fig, t_vector coll);
}					t_object;

typedef struct		s_plane
{
	t_vector		origin;
	// t_vector		origin_ini;
	t_vector		norm;
	// t_vector		norm_ini;

	t_vector		direction;
	// t_vector		direction_ini;
}					t_plane;

typedef struct		s_sphere
{
	t_vector		origin;
	// t_vector		origin_ini;
	float			radius;
	// float			radius_ini;
}					t_sphere;

typedef struct		s_cone
{
	float			base_rad;
	float			vert_rad;
	float			bv_dist;
	float			side_norm_angle;
	t_vector		base;
	t_vector		vert;
	t_vector		bv;
	t_vector		main_vert;

	t_vector		direction;
	t_vector		origin;
	t_vector		norm;
	float			radius;
	float			tg2;
}					t_cone;

/*
** ------------------------------------------ENVIRONMENT-----------------------------------------------------------
*/

typedef struct		s_light
{
	t_ltype			type;
	t_color			color;
	float			bright;
	t_vector		origin;
	t_vector		direct;
}					t_light;

typedef struct		s_camera
{
	t_vector		origin;
	t_vector		direct;
	t_vector		angles;
	t_vector		cam_transl;
	float			fov;
	t_matrix		wto_cam;

	t_vector		vs_start_point;
	t_vector		vs_start_vec;
	t_vector		vs_x_step_vec;
	t_vector		vs_y_step_vec;
}					t_camera;

/*
**	Hit Transparent Objects List
*/

typedef struct		s_hit
{
	struct s_object	*o;
	struct s_hit	*prev;
	struct s_hit	*next;
}					t_hit;

typedef struct		s_scene
{
	unsigned int	nb_obj;
	unsigned int	nb_light;
	t_color			bg_color;
	char			*name;
	t_vector		r_ori; //
	// t_vector		cam_pos; //
	// t_vector		cam_dir; //
	// t_vector		cam_transl; //
	// t_vector		cam_angles; //
	// t_matrix		wto_cam; //
	t_hit			*(hits[THREADS]);
	t_list			*lights;
	t_list			*objs;
	t_camera		*cam;
}					t_scene;

typedef struct 		s_sdl //FREE IN CASE OF ERROR / ON EXIT
{
	int				scr_wid;
	int				scr_hei;
	SDL_Window		*window;
	SDL_Texture		*screen;
	SDL_Renderer	*renderer;
	Uint32			*pixels;
	SDL_PixelFormat	*format; //from SDL_Surface
	int				pitch; //from SDL_Surface
	int				event_loop;
	// SDL_Event 		event;
}					t_sdl;

typedef struct 		s_environment
{
	t_scene			*scn;
//	t_light			*light;//
//	t_object		*obj;//
	float			asp_rat;
	t_object		**pix_obj;
	t_object		*selected;
	t_sdl			*sdl;

	unsigned int	nb_obj;
	unsigned int	nb_light;
}					t_env;

typedef struct			s_collision
{
	t_color				illum_color;
	t_color				phong_color;
	float				phong;
	float				fresnel;
	t_object			*o;
	t_vector			coll_pnt;
	t_vector			norm;
	t_vector			spclr_vec;
	t_vector			trans_vec;
}						t_coll;
/*
** -----------------------------------------DIFFERENT-----------------------------------------------------
*/

typedef struct		s_thrarg
{
	int				i;
//	int				pix_x;
//	int				pix_y;
	t_env			*e;
}					t_thrarg;

typedef	struct		s_thread
{
	int				s_pix;
	int				e_pix;
	t_env			*env;
}					t_thread;

typedef	struct		s_ray
{
	t_vector		ori;
	t_vector		dir;
	float			t;
	t_vector		hit_p;
	t_vector		hit_n;
	t_vector		hit_c;
}					t_ray;

/*
** -------------------------------------FUNCTIONS---------------------------------------------------------------
*/

int					is_tag(char *s);
int					get_vec(char *str, t_vector *vec);
int					get_col(char *str, t_vector *vec);
int					get_val(char *str, unsigned int *val);
int					parser(int fd, t_scene *scene);
char				*ft_ptrtostr(const char *s1, const char *s2);
/*
** THREADS
*/
int					mult_threads(t_env *env);
/*
** SET SCENE
*/
int					set_lights(t_scene *scene, char **prop);
int					set_cam(t_scene *scene, char **prop);
int					set_object1(t_scene *scene, char **prop, int type);
int					set_object2(t_scene *scene, char **prop, int type);
int					to_struct(t_scene *scene, char *s, int i);
t_object				*init_sobj(t_object **obj, unsigned int *nb_ob);
t_light				*init_slight(t_light **light, unsigned int *nb_li);
/*
** FREESHING
*/
int					clear_mem(char ***mem, int nb);
void				struct_del(t_scene *scene);
void				slight_del(t_light **lst);
void				sobj_del(t_object **lst);
/*
** RT RENDER
*/
void				render(t_env *env, t_scene *scene);
int					cast_ray(t_ray *ray, t_env *env, unsigned int pix);
t_vector			ray_generate(const t_env *env, int i, int j);
int					solve_qvadratic(float a, float b, float c, float *t);
int					s_intersect(t_vector dir, t_vector	orig, \
	t_object obj, float *t);
int					p_intersect(t_vector dir, t_vector orig, \
	t_object obj, float *t);
int					cy_intersect(t_vector dir, t_vector	orig, \
	t_object obj, float *t);
int					co_intersect(t_vector dir, t_vector	orig, \
	t_object obj, float *t);
/*
** LIGHTNING
*/
t_vector			get_light(t_env *env, t_ray *ray, t_object *obj, \
	t_light *light);
t_vector			get_diff(t_light *light, t_ray *ray, t_vector l_dir);
int					trace_shad(t_vector l_dir, t_ray *ray, t_object *objs, \
	float dis);
/*
** GRAPH_TRANSFORMATION LIBRARY
*/
t_matrix			*matrix_scale(t_matrix *m_scale, float scale);
t_matrix			*matrix_move(t_matrix *m_move, int x_m, int y_m, int z_m);
t_matrix			*matrix_rotate(t_matrix *m, float x, float y, float z);
t_matrix			*matrix_mult(t_matrix *right, t_matrix *left);
t_vector			*vec_multipl(const t_matrix *m, t_vector *p);
t_vector			*dir_multipl(const t_matrix *m, t_vector *p);
float				vec_mod(t_vector *v);
t_vector			*normilize_vec(t_vector *v);
float				dot_product(t_vector v1, t_vector v2);
t_vector			vec_scalar_mult(t_vector v, float s);
t_matrix			*inverse(t_matrix *m_inv, t_matrix *m4);
void				img_pixel_put(t_env *env, int x, int y, unsigned int color);
// unsigned int		get_rgb(unsigned int red, unsigned int green, \
// 	unsigned int blue);
unsigned int	get_rgb(t_sdl *sdl, unsigned int red, \
	unsigned int green, unsigned int blue);
// int					hook_keydown(int key, void *env);
// int					mouse_hook(int button, int x, int y, void *env);
// int					exit_x(void *env);
// void				put_to_window(t_env *ptr);
// void				translate(int key, t_vector *translation, int cam);
// void				scale(int key, float *scale, int cam);
t_matrix			*transform_mat(t_matrix *lm, t_vector translation, \
	t_vector rot, float scale);
t_matrix			*transform_mat_inv(t_matrix *lm, t_vector translation, \
	t_vector rot, float scale);
// void				reset(t_env *env);
void				rotate(Uint32 key, t_vector *angles);
void				scale(Uint32 key, float *siz, int cam);
void				cam_rotate(Uint32 key, t_vector *angles);
t_matrix			*x_rotate(t_matrix *m_xrot, float angle);
t_matrix			*y_rotate(t_matrix *m_yrot, float angle);
t_matrix			*z_rotate(t_matrix *m_zrot, float angle);
t_vector			cross_prod(t_vector u, t_vector v);
void				translate(Uint32 key, t_vector *pos, int cam);
void				reset(t_env *e);
void				delete_obj(t_list **obj_lst, Uint32 id);
/*
** SDL
*/
int					sdl_init(t_sdl *sdl);
void				sdl_close(t_sdl *sdl);
int					event_handler(t_env *env);
int 				sdl_error(char *message);
int					get_format_data(t_sdl *sdl);



////////////////////////////////////////////////////////////////////////////////

/*
**	hit.c
*/

t_hit					*ft_hit_list_new(int length);
void					ft_handle_hit
							(t_hit *head, t_object *o, float (*refr)[2]);

/*
**	scn.c
*/

t_scene					*ft_scenenew(void);
t_scene					*ft_get_scene(char *file_name);
void					ft_parse_scene(char *attr, t_scene *scn);

/*
**	camera.c
*/

t_camera				*ft_cameranew(void);
char					*ft_parse_camera(char *attr, t_scene *scn);
void					ft_get_start_refr(t_scene *scn);

/*
**	image.c


t_img					*ft_imgnew(t_env *e);
void					ft_pixel_put_image(t_env *e, int x, int y, int colour);

*/

/*
**	environment.c
*/

t_env					*ft_envnew(char *file_name);

/*
**	parse.c
*/

void					ft_parse(char *content, t_scene *scn);
char					*ft_get_curve(char *attr, char curve);

/*
**	render.c
*/

void					ft_render(t_env *e);

/*
**	attribute.c
*/

char					*ft_search_attr
	(char *content, char *attr, int ftsa_mode);
void					ft_read_attr(void *dst, char *attr, int type);
void					ft_get_attr_in_scope
	(char *start, char *name, void *dst, int type);

/*
**	light.c
*/

t_light					*ft_lightnew();
char					*ft_parse_light(char *attr, t_scene *scn);

/*
**	object.c
*/

t_object				*ft_objectnew();
t_object				*ft_parse_object(char *attr);

/*
**	plane.c
*/

char					*ft_parse_plane(char *attr, t_scene *scn, Uint32 id);

/*
**	plane_utils.c
*/

int						ft_is_reachable_plane
	(void *fig, t_vector origin, t_vector direct);
t_vector				ft_collide_plane
	(void *fig, t_vector origin, t_vector direct);
int						ft_is_inside_plane(void *fig, t_vector point);
t_vector				ft_get_norm_plane(void *fig, t_vector coll);

/*
**	sphere.c
*/

char					*ft_parse_sphere(char *attr, t_scene *scn, Uint32 id);

/*
**	sphere_utils.c
*/

int						ft_is_reachable_sphere
	(void *fig, t_vector origin, t_vector direct);
t_vector				ft_collide_sphere
	(void *fig, t_vector origin, t_vector direct);
int						ft_is_inside_sphere(void *fig, t_vector point);
t_vector				ft_get_norm_sphere(void *fig, t_vector coll);

/*
**	cone.c
*/

char					*ft_parse_cone(char *attr, t_scene *scn, Uint32 id);

/*
**	cone_utils.c
*/

t_vector				ft_collide_cone
	(void *fig, t_vector origin, t_vector direct);
int						ft_is_inside_cone(void *fig, t_vector point);
t_vector				ft_get_norm_cone(void *fig, t_vector coll);
void					ft_get_coll_pnts
	(t_cone *cone, t_vector (*pnt)[4], int is_cyl);

/*
**	cone_utils_2.c
*/

void					ft_set_coll_pnts_null(t_vector *pnt1, t_vector *pnt2);
void					ft_get_coll_pnts_cyl(t_cone *cone, t_vector (*pnt)[4]);
void					ft_is_between_planes
	(t_vector (*pnt)[4], t_vector base, t_vector vert);
void					ft_collide_cone_planes
	(t_cone *cone, t_vector origin,
	 t_vector direct, t_vector (*pnt)[4]);
t_vector				ft_get_closest(t_vector cam, t_vector pnt[4]);

/*
**	ray.c
*/

t_color					ft_throw_rays
							(t_thrarg *parg, t_coll *coll,
							t_vector *vec, float num[2]);
t_color					ft_trace_ray(t_thrarg *parg, int x, int y);

/*
**	ray_utils.c
*/

t_vector				ft_change_blur_vec
							(t_vector norm, t_vector vec, float angle);
t_vector				ft_get_blur_proj(t_vector origin, t_vector norm);
t_color					ft_sum_colors
							(t_coll *coll, t_color color_s,
							t_color color_t, int depth);

/*
**	illumination.c
*/

void					ft_illuminate(t_thrarg *parg, t_coll *coll);

/*
**	collision.c
*/

t_coll					ft_get_collision
							(t_thrarg *arg, t_vector origin, t_vector direct);

/*
**	utils.c
*/

t_color					ft_apply_phong
							(t_color color, float bright, t_color light_color);
t_color					ft_scale_color(t_color color, float k);
t_color					ft_add_colors(t_color c1, t_color c2);

/*
**	key_hooks.c
*/

int						ft_key_hook(int key, void *p);

/*
**	hook.c
*/

int						ft_close_hook(int x, int y, void *a);

/*
** FROM MY LIBFT
*/
void	ft_perr_exit(char *message);
int		ft_perr_retu(char *message);
void	ft_usage(char *message);

#endif
