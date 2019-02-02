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

# include <math.h>
# include <float.h>

typedef struct			s_point3
{
	float				x;
	float				y;
	float				z;
}						t_point3;

/*
**	point
*/

t_point3				ft_3_pointnew(float x, float y, float z);
t_point3				ft_3_nullpointnew(void);
int						ft_3_isnullpoint(t_point3 point);
float					ft_3_point_point_dist(t_point3 pnt_0, t_point3 pnt_1);
float					ft_3_line_point_dist
							(t_point3 origin, t_point3 direct, t_point3 point);
float					ft_3_plane_point_dist
							(t_point3 origin, t_point3 norm, t_point3 point);
float					ft_3_line_line_dist
							(t_point3 o1, t_point3 d1,
							t_point3 o2, t_point3 d2);
t_point3				ft_3_line_line_inter
							(t_point3 o1, t_point3 d1,
							t_point3 o2, t_point3 d2);
t_point3				ft_3_line_plane_inter
							(t_point3 pln_o, t_point3 pln_norm,
							t_point3 ln_o, t_point3 ln_d);
t_point3				ft_3_line_point_proj
							(t_point3 origin, t_point3 direct, t_point3 point);
int						ft_3_pointcmp
							(t_point3 pnt_0, t_point3 pnt_1, float prec);

/*
**	vector
*/

t_point3				ft_3_vectornew(t_point3 origin, t_point3 direct);
t_point3				ft_3_unitvectornew(t_point3 origin, t_point3 direct);
t_point3				ft_3_tounitvector(t_point3 vec);
t_point3				ft_3_vector_add(t_point3 vec_1, t_point3 vec_2);
t_point3				ft_3_vector_scale(t_point3 vec, float k);
float					ft_3_vector_dot(t_point3 vec_1, t_point3 vec_2);
t_point3				ft_3_vector_cross(t_point3 vec_1, t_point3 vec_2);
float					ft_3_vector_len(t_point3 vec);
float					ft_3_vector_cos(t_point3 vec_1, t_point3 vec_2);
t_point3				ft_3_vector_reflect
							(t_point3 origin, t_point3 coll, t_point3 norm);
t_point3				ft_3_vector_refract
							(t_point3 norm, t_point3 direct,
							float refr1, float refr2);
t_point3				ft_3_vector_turn
							(t_point3 proj, t_point3 norm, float angle);
t_point3				ft_3_vector_project(t_point3 norm, t_point3 vec);
t_point3				ft_3_vector_rotate
							(t_point3 vec, float alpha,
							float beta, float gamma);
t_point3				ft_3_vector_turn_near
							(t_point3 vec, t_point3 axis, float angle);

#endif
