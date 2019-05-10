/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libpnt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 10:53:06 by domelche          #+#    #+#             */
/*   Updated: 2018/09/19 10:53:13 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBPNT_H

# define LIBPNT_H

# include <time.h>
# include <stdlib.h>
# include <math.h>
# include <float.h>

# define Z_AXIS			(t_vector){1.f, 0.f, 0.f}
# define Y_AXIS			(t_vector){0.f, 1.f, 0.f}
# define X_AXIS			(t_vector){0.f, 0.f, 1.f}

typedef float			t_vector __attribute__((vector_size(sizeof(float)*4)));

static int				g_is_seeded = 0;

/*
**	point
*/

t_vector				ft_3_nullpointnew(void);
t_vector				ft_3_zeropointnew(void);
int						ft_3_isnullpoint(t_vector point);
int		            	ft_3_iszeropoint(t_vector point);
float					ft_3_point_point_dist(t_vector pnt_0, t_vector pnt_1);
float					ft_3_point_point_dist_square(t_vector pnt_0, t_vector pnt_1);
float					ft_3_line_point_dist
							(t_vector origin, t_vector direct, t_vector point);
float					ft_3_plane_point_dist
							(t_vector origin, t_vector norm, t_vector point);
float					ft_3_line_line_dist
							(t_vector o1, t_vector d1,
							t_vector o2, t_vector d2);
t_vector				ft_3_line_line_inter
							(t_vector o1, t_vector d1,
							t_vector o2, t_vector d2);
t_vector				ft_3_line_plane_inter
							(t_vector pln_o, t_vector pln_norm,
							t_vector ln_o, t_vector ln_d);
t_vector				ft_3_line_point_proj
							(t_vector origin, t_vector direct, t_vector point);
int						ft_3_pointcmp
							(t_vector pnt_0, t_vector pnt_1, float prec);

/*
**	vector
*/

t_vector				ft_3_unitvectornew(t_vector origin, t_vector direct);
t_vector				ft_3_tounitvector(t_vector vec);
t_vector				ft_3_vector_invert(t_vector vector);
t_vector				ft_3_vector_random(void);
t_vector				ft_3_vector_random_cone(t_vector d, float cone_angle);
t_vector				ft_3_vector_scale(t_vector vec, float k);
float					ft_3_vector_dot(t_vector vec_1, t_vector vec_2);
t_vector				ft_3_vector_cross(t_vector vec_1, t_vector vec_2);
float					ft_3_vector_len(t_vector vec);
float					ft_3_vector_cos(t_vector vec_1, t_vector vec_2);
t_vector				ft_3_vector_reflect
							(t_vector origin, t_vector coll, t_vector norm);
t_vector				ft_3_vector_refract
							(t_vector norm, t_vector direct,
							float refr1, float refr2);
t_vector				ft_3_vector_turn
							(t_vector proj, t_vector norm, float angle);
t_vector				ft_3_vector_project(t_vector norm, t_vector vec);
t_vector				ft_3_vector_rotate
							(t_vector vec, float alpha,
							float beta, float gamma);
t_vector				ft_3_vector_turn_near
							(t_vector vec, t_vector axis, float angle);

t_vector				ft_3_fabsf_vector(t_vector vec);

// ------------------------- DELETE ME ---------------------------------------//
void					ft_3_vector_print(const char *str, t_vector point);
// ---------------------------------------------------------------------------//

/*
** matrix
*/

typedef	float		t_matrix[4][4];

void				ft_3_identity(t_matrix *m);
void				ft_3_matrix_scale(t_matrix *m_scale, float scale, int inv);
void				ft_3_matrix_move(t_matrix *m_move, t_vector rot, int inv);
void				ft_3_matrix_rotate(t_matrix *m, t_vector rot, int inv);
void				ft_3_transform_mat(t_matrix *lm, t_vector transl, t_vector rot, float scale);
void				ft_3_inv_trans_mat(t_matrix *lm, t_vector transl, t_vector rot, float scale);
void				ft_3_matrix_x_rot(t_matrix *m, float ang, int inv);
void				ft_3_matrix_y_rot(t_matrix *m, float ang, int inv);
void				ft_3_matrix_z_rot(t_matrix *m, float ang, int inv);
void				ft_3_matrix_mult(t_matrix *right, t_matrix *left, int inv);
void				ft_3_inverse(t_matrix *m_inv, t_matrix *m4);
t_vector			ft_3_vec_transform(const t_matrix *m, t_vector p);
t_vector			ft_3_pnt_transform(const t_matrix *m, t_vector p);
t_vector			ft_3_norm_transform(const t_matrix *m, t_vector p);


#endif
