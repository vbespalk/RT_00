//
// Created by ivoriik on 15.03.19.
//

#include "rt.h"
void		ft_parse_skybox(char **content, t_skybox **sky)
{
	int			i;
	t_vector	bounds[2];

	if (!content || !(*content))
		return ;
	*sky = (t_skybox *)ft_smemalloc(sizeof(t_skybox), "ft_parse_skybox");
	ft_get_attr(content, "negz", (void *)(&((*sky)->textur_id[0])), DT_STRING);
	ft_get_attr(content, "negy", (void *)(&((*sky)->textur_id[1])), DT_STRING);
	ft_get_attr(content, "negx", (void *)(&((*sky)->textur_id[2])), DT_STRING);
	ft_get_attr(content, "posz", (void *)(&((*sky)->textur_id[3])), DT_STRING);
	ft_get_attr(content, "posy", (void *)(&((*sky)->textur_id[4])), DT_STRING);
	ft_get_attr(content, "posx", (void *)(&((*sky)->textur_id[5])), DT_STRING);
	i = -1;
	while (++i < BOX_FACES)
		if ((*sky)->textur_id[i] == NULL)
		{
			i = -1;
			ft_putendl("PARSE WARNING: incorrect or incomplete SKY BOX description, "
					   "value set to default");
			while (++i < BOX_FACES)
				ft_memdel((void **) &(*sky)->textur_id[i]);
			ft_memdel((void **) (sky));
			return;
		}
	bounds[0] = ft_3_nullpointnew();
	bounds[1] = ft_3_nullpointnew();
	ft_get_attr(content, "min", (void *)(&(bounds[0])), DT_POINT);
	ft_get_attr(content, "max", (void *)(&(bounds[1])), DT_POINT);
	(*sky)->bbx = ft_init_aabb(bounds[0], bounds[1]);
}

static t_vector	ft_get_rst(t_vector vec, t_vector norm)
{
	t_vector rst;

	rst = ft_3_nullpointnew();
	if (fabsf(norm[0]) >= 0.7)
	{
		rst[0] = norm[0] > 0 ? 3 : 0;
		rst[1] = norm[0] > 0 ? ((vec[2]) + 1) * 0.5f : 1 - ((vec[2]) + 1) * 0.5f;
		rst[2] = 1 - ((vec[1]) + 1) * 0.5f;
	}
	else if (fabsf(norm[1]) >= 0.7)
	{
		rst[0] = norm[1] > 0 ? 4 : 1;
		rst[1] = ((vec[2]) + 1) * 0.5f;
		rst[2] = norm[1] > 0 ? ((vec[0]) + 1) * 0.5f : 1 - ((vec[0]) + 1) * 0.5f;
	}
	else if (fabsf(norm[2]) >= 0.7)
	{
		rst[0] = norm[2] > 0 ? 5 : 2;
		rst[1] = norm[2] > 0 ? 1 - ((vec[0]) + 1) * 0.5f : ((vec[0]) + 1) * 0.5f;
		rst[2] = 1 - ((vec[1]) + 1) * 0.5f;
	}
//	else
//		printf("WOOOOP norm %f,%f,%f, vec %f,%f,%f\n", norm[0], norm[1], norm[2], vec[0], vec[1], vec[2]);
	return (rst);
}

Uint32		ft_map_skybox(t_aabb *bbx, t_texture *tex[6], t_vector hit)
{
	t_vector 	rst;
	Uint32		col;
	int			xy[2];

	t_vector	vec;
	t_vector	norm;
	float 		bias;

	bias = 1.000001f;
	vec = (hit - bbx->cntr) / ft_3_fabsf_vector(ft_3_vector_scale(bbx->dgnl, 0.5f));
	norm = ft_3_tounitvector((t_vector){(int)(vec[0] * bias),
									 (int)(vec[1] * bias), (int)(vec[2] * bias)});
	rst = ft_get_rst(vec, norm);
	xy[0] = (int) ((tex[(int) rst[0]]->surface->w - 1) * fabsf(rst[1]));
	xy[1] = (int) ((tex[(int) rst[0]]->surface->h - 1) * fabsf(rst[2]));
	if (!(IN_RANGE(xy[0], 0, tex[(int) rst[0]]->surface->w) &&
		IN_RANGE(xy[1], 0, tex[(int) rst[0]]->surface->h)))
		return (0xff0000);
	ft_memcpy(&col, (Uint32 *) tex[(int) rst[0]]->surface->pixels + xy[1] *
		tex[(int) rst[0]]->surface->w + xy[0],  sizeof(Uint32));
//		printf("vec %f, %f, %f, norm %f,%f,%f\n", vec[0], vec[1], vec[2], norm[0], norm[1], norm[2]);
	return (col);
}

t_color		ft_apply_sky(t_skybox *sky, t_vector o, t_vector d)
{
	t_vector	hit;
	t_color		col;

	hit = sky->bbx->ft_collide(sky->bbx, o, d);
	col.val = ft_map_skybox(sky->bbx, sky->textur, hit);
	return (col);
}