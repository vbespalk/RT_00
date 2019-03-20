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

#ifndef RT_H

# define RT_H

# define SCR_WID 640
# define SCR_HEI 480
# define FOV 1.570796
# define L_X(a, b) ({typeof(a) _a = (a);typeof(b) _b = (b);_a >= _b ? _b : _a;})
# define L_N(a, b) ({typeof(a) _a = (a);typeof(b) _b = (b);_a <= _b ? _b : _a;})
# define DEG_TO_RAD(x) ((x) * (float)M_PI / 180.0f)
# define RAD_TO_DEG(x) ((x) * 180.0f / M_PI)
# define IN_RANGE(x, left, right) ((x >= left) && (x <= right))

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

/*
**	system
*/

# define DEPTH			5
# define STACK_SIZE		DEPTH
# define THREADS		1

/*
**	includes
*/

# define ROTAT_F		DEG_TO_RAD(10)
# define TRANS_F		15.0f
# define SCALE_F		0.1f
# define SCANG_F		0.05f
// # define SCALE_F_CAM	0.1
# define BOX_FACES		6


# include <stdio.h>
# include <pthread.h>
# include <stdint.h>
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

//typedef	float		t_matrix[4][4];
typedef uint8_t		t_byte;

typedef union		u_color
{
	Uint32			val;
	t_byte			argb[4];
}					t_color;

typedef enum		e_ltype
{
	L_POINT,
	L_DIRECT,
	L_PARALLEL
}					t_ltype;

typedef struct		s_texture
{
	char			*path;
	SDL_Surface		*surface;
	Uint32 			*pixels;
	SDL_PixelFormat	*format;
}					t_texture;

typedef enum		e_smooth
{
	SMOOTH_1X,
	SMOOTH_4X,
	SMOOTH_9X
}					t_smooth;

/*
** -------------------------------------------OBJECTS-----------------------------------------------
*/

typedef struct		s_object
{
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
	int				is_neg;
	float			ambnt;
	float			diff;
	float			spclr;
	float			s_blur;
	float			refr;
	float			trans;
	float			t_blur;
	float			phong;

	t_color			color;
	char 			*texture_id;
	t_texture		*texture;
/*
** functions for intersection / search etc.
*/
	int				(*ft_is_reachable)
	 					(void *fig, t_vector origin, t_vector direct);
	t_vector		(*ft_collide)
	 					(t_list **objs, void *fig, t_vector o, t_vector d);
	int				(*ft_is_inside)(void *fig, t_vector point);
	t_vector		(*ft_get_norm)(void *fig, t_vector coll);
/*
** functions for transform obj.
*/
	void			(*ft_translate)
						(Uint32 key, void *fig, t_vector *translate);
	void			(*ft_rotate)
						(Uint32 key, void *fig, t_vector *rotate);
	void			(*ft_scale)
						(Uint32 key, void *fig, float *scale);
/*
** functions for texturing obj.
*/
	Uint32			(*ft_mapping)
						(void *fig, t_texture *tex, t_vector coll);
}					t_object;

typedef struct		s_plane
{
	t_vector		origin_ini;
	t_vector		norm_ini;
	t_vector		w_ini;
	t_vector		h_ini;
	t_vector		origin;
	t_vector		norm;
	t_vector		dir_wh[2];
	float			len_wh[2];
	t_vector		cntr;
	t_vector		dgnl;
}					t_plane;

typedef struct		s_sphere
{
	t_vector		origin_ini;
	float			radius_ini;
	t_vector		origin;
	float			radius;
	float			min_thcos;
	float			max_thcos;
	float			min_phi;
	float			max_phi;
	float			phi;
	float 			theta;
}					t_sphere;

typedef struct		s_cone
{
	t_vector		o; //vertex of the cone
	t_vector		v;
	t_vector		v_cp;
	float 			r[2]; //caps radius; from vertex to base
	float 			h; //height
	float			tan;
	float			minh; //limits of height; from vertex
	float			maxh; //limits of height; from vertex
	t_vector		norm;
	float 			phi;
}					t_cone;

typedef struct		s_cylinder
{
	t_vector		o;
	t_vector		v;
	float			r;
	float 			h; //height
	float			maxh;
	float			phi;
}					t_cylinder;

typedef struct		s_disc
{
	t_vector		origin_ini;
	t_vector		norm_ini;
	float			in_r_ini;
	float			out_r_ini;
	t_vector		origin;
	t_vector		norm;
	float			in_r;
	float			out_r;
}					t_disk;

typedef struct		s_triangle
{
	t_vector		v0_ini;
	t_vector		v1_ini;
	t_vector		v2_ini;
	t_vector		v0;
	t_vector		v1;
	t_vector		v2;
	t_vector		unorm; //unnormilised normal
	t_vector		norm;
	float			u; // baricentric coordinates
	float			v; // baricentric coordinates
}					t_triangle;

typedef struct		s_bounding_box
{
	t_vector		bounds[2];
	t_vector		origin;
	t_vector		cntr;
	t_vector		dgnl;
//	t_vector		norm;
/*
** functions for intersection / search etc.
*/
	int				(*ft_is_reachable)
			(void *fig, t_vector origin, t_vector direct);
	t_vector		(*ft_collide)
			(void *fig, t_vector origin, t_vector direct);
	int				(*ft_is_inside)(void *fig, t_vector point);
	t_vector		(*ft_get_norm)(void *fig, t_vector coll);
/*
** functions for transform obj.
*/
	void			(*ft_translate)
			(Uint32 key, void *fig, t_vector *translate);
	void			(*ft_rotate)
			(Uint32 key, void *fig, t_vector *rotate);
	void			(*ft_scale)
			(Uint32 key, void *fig, float *scale);
}					t_aabb;

typedef struct		s_skybox
{
	t_aabb			*bbx;
	char 			*textur_id[BOX_FACES];
	t_texture		*textur[BOX_FACES];
}					t_skybox;

typedef struct		s_box
{
	t_vector		o;
	t_vector		lwh[3];
	t_vector		dgnl;
	t_vector		cntr;
//	t_vector		dir_lwh[3];
//	float 			len_lwh[3];

	t_plane			*face[BOX_FACES];
	t_plane			*fcoll;
}					t_box;

typedef struct		s_paraboloid
{
	t_vector		o;
	t_vector		v;
	t_vector		n;
	float			r; //radius
	float			maxh; //max height

}					t_prbld;

typedef struct		s_torus
{
	t_vector		o;
	t_vector		v;
	t_vector		n;
	float			r_inner; //  small radius of the torus = r
	float			r_outer; // big radius of the torus = R

}					t_torus;
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
	t_smooth		smooth;
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
	t_object		*inner_o;
}					t_camera;

typedef struct		s_scene
{
	unsigned int	nb_obj;
	unsigned int	nb_light;
	t_color			bg_color;
	char			*name;
	t_list			*lights;
	t_list			*objs;
	t_list			*textures;
	t_skybox		*skybox;
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
//	Uint32			*highlight;
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
//	t_object		*pointed;
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

typedef struct			s_ray
{
	int					stack_i;
	Uint32				pix;
	t_coll				*coll;
	/*
	**	origin
	*/
	t_vector			o;
	/*
	**	direct
	*/
	t_vector			d;
	t_object			*(stack[STACK_SIZE]);
}						t_ray;

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

//typedef	struct		s_thread
//{
//	int				s_pix;
//	int				e_pix;
//	t_env			*env;
//}					t_thread;
//
//typedef	struct		s_ray
//{
//	t_vector		ori;
//	t_vector		dir;
//	float			t;
//	t_vector		hit_p;
//	t_vector		hit_n;
//	t_vector		hit_c;
//}					t_ray;

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

void				cam_rotate(Uint32 key, t_vector *angles);
t_matrix			*x_rotate(t_matrix *m_xrot, float angle);
t_matrix			*y_rotate(t_matrix *m_yrot, float angle);
t_matrix			*z_rotate(t_matrix *m_zrot, float angle);
t_vector			cross_prod(t_vector u, t_vector v);
void				reset(t_env *e);
void				delete_obj(t_list **obj_lst, Uint32 id);

// void				rotate(Uint32 key, t_vector *angles);
// void				scale(Uint32 key, float *siz, int cam);
// void				translate(Uint32 key, t_vector *pos, int cam);

void				scale_cam(Uint32 key, t_object *obj, float *sc_factor, int cam);

/*
** init_sdl.c
*/
int					sdl_init(t_sdl *sdl);
void				sdl_close(t_sdl *sdl);
int					event_handler(t_env *env);
int 				sdl_error(char *message);
int					get_format_data(t_sdl *sdl);
int 				sdl_img_error(char *message);



////////////////////////////////////////////////////////////////////////////////

/*
**	hit.c
*/

void					ft_get_refrs(t_ray *ray, float (*refr)[2]);
void					ft_handle_hit(t_ray *ray, t_object *o);

/*
**	scene.c
*/

t_scene					*ft_scenenew(void);
void					ft_parse_scene(char **content, t_scene *scn);

/*
**	camera.c
*/

t_camera				*ft_cameranew(void);
void					ft_parse_camera(char **content, t_camera *cam);
void					ft_get_start_stack(t_scene *scn);

/*
** cam_transform
*/

void					ft_translate_cam(Uint32 key, t_vector *rot);
void					ft_rotate_cam(Uint32 key, t_vector *angles);
void					ft_scale_cam(Uint32 key, float *sc_factor);

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

//char					*ft_search_attr
//	(char *content, char *attr, int ftsa_mode);
//void					ft_read_attr(void *dst, char *attr, int type);
//void					ft_get_attr_in_scope
//	(char *start, char *name, void *dst, int type);

/*
**	light.c
*/

void					ft_parse_light(char **content, t_list **lst, Uint32 id);

/*
**	object.c
*/

t_object				*ft_objectnew(Uint32 id);
void					ft_parse_object
							(char **content, t_list **lst, Uint32 id);
t_object				*ft_objectnew(Uint32 id);

/*
**--------------------------------------------------PLANE------------------------------------------------------------------
*/

/*
**	plane.c
*/

void					*ft_parse_plane(char **content, t_object *o);
void					ft_translate_plane(Uint32 key, void *fig, t_vector *transl);
void					ft_rotate_plane(Uint32 key, void *fig, t_vector *rot);
void					ft_scale_plane(Uint32 key, void *fig, float *scale);

/*
**	plane_utils.c
*/

int						ft_is_reachable_plane
							(void *fig, t_vector origin, t_vector direct);
t_vector				ft_collide_plane
							(t_list **objs, void *fig, t_vector o, t_vector d);
int						ft_is_inside_plane(void *fig, t_vector point);
t_vector				ft_get_norm_plane(void *fig, t_vector coll);

/*
**--------------------------------------------------DISK------------------------------------------------------------------
*/
/*
**	disk.c
*/

char					*ft_parse_disk(char **content, t_object *o);
void					ft_translate_disk(Uint32 key, void *fig, t_vector *transl);
void					ft_rotate_disk(Uint32 key, void *fig, t_vector *rot);
void					ft_scale_disk(Uint32 key, void *fig, float *scale);

/*
**	disk_utils.c
*/

int						ft_is_reachable_disk
							(void *fig, t_vector origin, t_vector direct);
t_vector				ft_collide_disk
							(t_list **objs, void *fig, t_vector o, t_vector d);
int						ft_is_inside_disk(void *fig, t_vector point);
t_vector				ft_get_norm_disk(void *fig, t_vector coll);

/*
**--------------------------------------------------TRIANGLE------------------------------------------------------------------
*/
/*
**	triangle.c
*/

char					*ft_parse_triangle(char *attr, t_scene *scn, unsigned int id);
void					ft_translate_triangle(Uint32 key, void *fig, t_vector *transl);
void					ft_rotate_triangle(Uint32 key, void *fig, t_vector *rot);
void					ft_scale_triangle(Uint32 key, void *fig, float *scale);

/*
**	triangle_utils.c
*/

int						ft_is_reachable_triangle
							(void *fig, t_vector origin, t_vector direct);
t_vector				ft_collide_triangle
							(t_list **objs, void *fig, t_vector o, t_vector d);
int						ft_is_inside_triangle(void *fig, t_vector point);
t_vector				ft_get_norm_triangle(void *fig, t_vector coll);

/*
**--------------------------------------------------BOX------------------------------------------------------------------
*/
/*
**	box.c
*/

char					*ft_parse_box(char **content, t_object *o);
void					ft_translate_box(Uint32 key, void *fig, t_vector *transl);
void					ft_rotate_box(Uint32 key, void *fig, t_vector *rot);
void					ft_scale_box(Uint32 key, void *fig, float *scale);

/*
**	box_utils.c
*/

int						ft_is_reachable_box
							(void *fig, t_vector origin, t_vector direct);
t_vector				ft_collide_box
							(t_list **objs, void *fig, t_vector o, t_vector d);
int						ft_is_inside_box(void *fig, t_vector point);
t_vector				ft_get_norm_box(void *fig, t_vector coll);

/*
** aabb.c
*/

t_aabb					*ft_init_aabb(t_vector min, t_vector max);
int						ft_is_reachable_aabb(void *fig, t_vector origin, t_vector direct);
t_vector				ft_collide_aabb(void *fig, t_vector origin, t_vector direct);
void					ft_translate_aabb(Uint32 key, void *fig, t_vector *transl);
void					ft_scale_aabb(Uint32 key, void *fig, float *scale);

/*
**--------------------------------------------------SPHERE------------------------------------------------------------------
*/
/*
**	sphere.c
*/

void					*ft_parse_sphere(char **content, t_object *o);
void					ft_translate_sphere(Uint32 key, void *fig, t_vector *transl);
void					ft_rotate_sphere(Uint32 key, void *fig, t_vector *rot);
void					ft_scale_sphere(Uint32 key, void *fig, float *scale);

/*
**	sphere_utils.c
*/

int						ft_is_reachable_sphere
							(void *fig, t_vector origin, t_vector direct);
t_vector				ft_collide_sphere
							(t_list **objs, void *fig, t_vector o, t_vector d);
int						ft_is_inside_sphere(void *fig, t_vector point);
t_vector				ft_get_norm_sphere(void *fig, t_vector coll);

/*
**--------------------------------------------------CONE------------------------------------------------------------------
*/
/*
**	cone.c
*/

void					*ft_parse_cone(char **content, t_object *o);
void					ft_translate_cone(Uint32 key, void *fig, t_vector *transl);
void					ft_rotate_cone(Uint32 key, void *fig, t_vector *rot);
void					ft_scale_cone(Uint32 key, void *fig, float *scale);

/*
**	cone_utils.c
*/

t_vector				ft_collide_cone
							(t_list **objs, void *fig, t_vector o, t_vector d);
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
**	cylinder_utils.c
*/

void					*ft_parse_cylinder(char **content, t_object *o);
void					ft_translate_cylinder(Uint32 key, void *fig, t_vector *transl);
void					ft_rotate_cylinder(Uint32 key, void *fig, t_vector *rot);
void					ft_scale_cylinder(Uint32 key, void *fig, float *scale);

/*
**	cone_utils.c
*/

int						ft_is_reachable_cylinder(void *fig, t_vector origin, t_vector direct);
t_vector				ft_collide_cylinder(void *fig, t_vector origin, t_vector direct);
int						ft_is_inside_cylinder(void *fig, t_vector point);
t_vector				ft_get_norm_cylinder(void *fig, t_vector coll);

/*
**------------------------------------------------PARABOLOID----------------------------------------------------------------
*/
/*
**	paraboloid.c
*/

char					*ft_parse_prbld(char **content, t_object *o);
void					ft_translate_prbld(Uint32 key, void *fig, t_vector *transl);
void					ft_rotate_prbld(Uint32 key, void *fig, t_vector *rot);
void					ft_scale_prbld(Uint32 key, void *fig, float *scale);

/*
**	paraboloid_utils.c
*/

int						ft_is_reachable_prbld(void *fig, t_vector origin, t_vector direct);
t_vector				ft_collide_prbld
							(t_list **objs, void *fig, t_vector o, t_vector d);
int						ft_is_inside_prbld(void *fig, t_vector point);
t_vector				ft_get_norm_prbld(void *fig, t_vector coll);

/*
**------------------------------------------------TORUS----------------------------------------------------------------
*/
/*
**	torus.c
*/

char					*ft_parse_torus(char **content, t_object *o);
void					ft_translate_torus(Uint32 key, void *fig, t_vector *transl);
void					ft_rotate_torus(Uint32 key, void *fig, t_vector *rot);
void					ft_scale_torus(Uint32 key, void *fig, float *scale);

/*
**	torus_utils.c
*/

int						ft_is_reachable_torus(void *fig, t_vector origin, t_vector direct);
t_vector				ft_collide_torus(void *fig, t_vector origin, t_vector direct);
int						ft_is_inside_torus(void *fig, t_vector point);
t_vector				ft_get_norm_torus(void *fig, t_vector coll);

/*
**	ray.c
*/

t_color					ft_trace_ray(t_thrarg *parg, int x, int y);
t_color					ft_throw_ray(t_thrarg *parg, t_ray *ray, int depth);
t_color					ft_throw_rays
							(t_thrarg *parg, t_ray *ray,
							t_vector *vec, float num[2]);

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

int						ft_inside_what(t_list **objs, t_vector point);
t_coll					ft_get_collision(t_thrarg *arg, t_ray *ray);

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
**  textures.c
*/

t_texture				*init_texture(t_list **textures, t_sdl *sdl, char *id);
t_texture				*load_texture(t_sdl *sdl, char *path);

/*
** sphere_mapping.c
*/

Uint32					ft_map_sphere(void *fig, t_texture *tex, t_vector coll);

/*
** cylinder_mapping.c
*/

Uint32					ft_map_clndr(void *fig, t_texture *tex, t_vector coll);

/*
** cone_mapping.c
*/

Uint32					ft_map_cone(void *fig, t_texture *tex, t_vector coll);

/*
** plane_mapping.c
*/

Uint32					ft_map_plane(void *fig, t_texture *tex, t_vector coll);
Uint32					ft_map_box(void *fig, t_texture *tex, t_vector hit);

/*
** skybox.c
*/

void					ft_parse_skybox(char **content, t_skybox **sky);
Uint32					ft_map_skybox(t_aabb *bbx, t_texture *tex[6], t_vector hit);
t_color					ft_apply_sky(t_skybox *skybox, t_vector origin, t_vector direct);
/*
** FROM MY LIBFT
*/
//void	ft_perr_exit(char *message);
int		ft_perr_retu(char *message);
void	ft_usage(char *message);


#endif
