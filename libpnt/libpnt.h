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

typedef float			t_vector __attribute__((vector_size(sizeof(float)*4)));

static int				g_is_seeded = 0;

/*
**	point
*/

t_vector				ft_3_nullpointnew(void);
int						ft_3_isnullpoint(t_vector point);
float					ft_3_point_point_dist(t_vector pnt_0, t_vector pnt_1);
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
t_vector				ft_3_vector_random(void);
t_vector				ft_3_vector_random_cone(t_vector d, float cone_angle);
t_vector				ft_3_tounitvector(t_vector vec);
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

#endif
