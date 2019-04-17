//
// Created by Viktoriia BESPALKO on 2019-04-17.
//
#include "rt.h"

Uint32		ft_procedural_prbld(void *fig, t_procedural *tex, t_vector coll)
{
    t_prbld		*prbl;
    float 		hei;
    t_vector	point;
    t_vector	vec;
    float		theta;

    prbl = (t_prbld *)fig;
//	hei = fabsf(ft_3_vector_dot(coll - ((t_cylinder *)fig)->o, ((t_cylinder *)fig)->v));
//	printf("HEI %f %f\n", prbl->maxh, prbl->maxh / prbl->r);
    point = ft_3_vector_scale(coll, ((1 / (prbl->r))));
//	printf("PAR R %f Y %f\n", prbl->r, coll[1]);
    point[1] = coll[1] / 50;
//	point[1] = (coll[1] - prbl->maxh / (prbl->r * prbl->r)) ;
//	point = coll;
//	point = ft_3_vector_scale(coll - cyl->o, 1.0f / cyl->r);
//	float ang[2];
//	ang[0] = DEG_TO_RAD(90) - acosf(ft_3_vector_dot(cyl->v, (t_vector){1,0,0}));
//	ang[1] = DEG_TO_RAD(90) - acosf(ft_3_vector_dot(cyl->v, (t_vector){0,0,1}));
//	float len = ft_3_vector_len(point);
//	point = ft_3_vector_rotate(ft_3_tounitvector(point), -ang[1], 0, ang[0]);
//	point = ft_3_vector_rotate((point), ang[1], 0, ang[0]);

    //	printf("point %f,%f,%f\n", point[0], point[1], point[2]);
//	theta = cyl->theta * 2.0f;
//	point = ft_3_vector_rotate(point, 0, -cyl->phi, theta);
    return (tex->ft_get_color(tex, NULL, ft_3_vector_scale(point, 1)));
}