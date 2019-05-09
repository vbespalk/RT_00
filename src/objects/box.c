#include "rt.h"

t_box		*ft_boxnew(t_object *o)
{
	t_box	*bx;

    o->ft_collide = ft_collide_box;
    o->ft_is_reachable = ft_is_reachable_box;
    o->ft_is_inside = ft_is_inside_box;
    o->ft_get_norm = ft_get_norm_box;
    o->ft_translate = ft_translate_box;
    o->ft_rotate = ft_rotate_box;
    o->ft_scale = ft_scale_box;
    o->ft_scale_height = ft_scale_box;
    o->ft_mapping = ft_map_box;
    o->ft_checker = ft_checker_box;
    o->composed = true;
	bx = ft_smemalloc(sizeof(t_box), "ft_boxnew");
	bx->whl[0] = 10;
	bx->whl[1] = 10;
	bx->whl[2] = 10;
    bx->scale = 1;
    return (bx);
}

void		ft_init_box_pln(t_box *bx, t_plane *pln, int i)
{
	if (i % 3 == 0)
	{
           bx->face[i]->translate = i == 0 ? (t_vector) {-bx->whl[0], 0, 0} :
                   (t_vector) {bx->whl[0], 0, 0};
           pln->len_wh[0] = bx->whl[2];
           pln->len_wh[1] = bx->whl[1];
           bx->face[i]->rotate = (t_vector){FLT_MIN, FLT_MIN, DEG_TO_RAD(90)};
       }
       else if (i % 3 == 1)
       {
           bx->face[i]->translate = i == 1 ? (t_vector){0, -bx->whl[1], 0} :
                   (t_vector){0, bx->whl[1], 0};
           pln->len_wh[0] = bx->whl[2];
           pln->len_wh[1] = bx->whl[0];
           bx->face[i]->rotate = (t_vector){FLT_MIN, FLT_MIN, FLT_MIN};
       }
       else
       {
           bx->face[i]->translate = i == 2 ? (t_vector){0, 0, -bx->whl[2]} :
                   (t_vector){0, 0, bx->whl[2]};
           pln->len_wh[0] = bx->whl[1];
           pln->len_wh[1] = bx->whl[0];
           bx->face[i]->rotate = (t_vector){DEG_TO_RAD(90), FLT_MIN, FLT_MIN};
       }
}

char		*ft_parse_box(char **content, t_object *o)
{
	t_box		*bx;
    t_plane		*pln;
    int			i;

    bx = ft_boxnew(o);
	ft_get_attr(content, "length", (void *)(&(bx->whl[2])), DT_FLOAT);
	ft_get_attr(content, "width", (void *)(&(bx->whl[0])), DT_FLOAT);
	ft_get_attr(content, "height", (void *)(&(bx->whl[1])), DT_FLOAT);
	i = -1;
    while (++i < BOX_FACES)
    {
        bx->face[i] = ft_smemalloc(sizeof(t_object), "ft_init_box");
        bx->face[i]->fig = ft_planenew(bx->face[i]);
        pln = (t_plane *)bx->face[i]->fig;
	    ft_init_box_pln(bx, pln, i);
        pln->ratio = pln->len_wh[1] / pln->len_wh[0];
        ft_3_transform_mat(&(bx->face[i]->transform), bx->face[i]->translate,
                           bx->face[i]->rotate, pln->len_wh[0]);
        ft_3_inv_trans_mat(&(bx->face[i]->inverse), -bx->face[i]->translate,
                           -bx->face[i]->rotate, 1.0f / pln->len_wh[0]);
    }
	ft_3_transform_mat(&(o->transform), o->translate, o->rotate, FLT_MIN);
	ft_3_inv_trans_mat(&(o->inverse), -o->translate, -o->rotate, FLT_MIN);
	return ((void *)bx);
}

int 		ft_translate_box(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m)
{
	t_box	*bx;

	if (!o)
		return (0);
	bx = (t_box *)o->fig;
	if (key == SDLK_d)
		o->translate[2] += TRANS_F;
	if (key == SDLK_a)
		o->translate[2] -= TRANS_F;
	if (key == SDLK_w)
		o->translate[1] += TRANS_F;
	if (key == SDLK_s)
		o->translate[1] -= TRANS_F;
	if (key == SDLK_e)
		o->translate[0] += TRANS_F;
	if (key == SDLK_q)
		o->translate[0] -= TRANS_F;
	ft_3_transform_mat(tr_m, o->translate, o->rotate, bx->scale);
	ft_3_inv_trans_mat(inv_m, -o->translate, -o->rotate, 1.f / bx->scale);
    return (1);
}

int 		ft_rotate_box(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m)
{
	t_box	*bx;

	if (!o)
		return (0);
	bx = (t_box *)o->fig;
	if (key == SDLK_DOWN)
		o->rotate[2] += ROTAT_F;
	else if (key == SDLK_UP)
		o->rotate[2] -= ROTAT_F;
	else if (key == SDLK_LEFT)
		o->rotate[1] -= ROTAT_F;
	else if (key == SDLK_RIGHT)
		o->rotate[1] += ROTAT_F;
	else if (key == SDLK_PAGEDOWN)
		o->rotate[0] += ROTAT_F;
	else if (key == SDLK_PAGEUP)
		o->rotate[0] -= ROTAT_F;
	ft_3_transform_mat(tr_m, o->translate, o->rotate, bx->scale);
	ft_3_inv_trans_mat(inv_m, -o->translate, -o->rotate, 1.f / bx->scale);
    return (1);
}

int 		ft_scale_box(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m)
{
	t_box		*bx;

	if (!o)
		return (0);
	bx = (t_box *)o->fig;
	if (key == SDLK_z)
		bx->scale *= (1.f + SCALE_F);
	else if (key == SDLK_x )
		bx->scale *= (1.f - SCALE_F);
	ft_3_transform_mat(tr_m, o->translate, o->rotate, bx->scale);
	ft_3_inv_trans_mat(inv_m, -o->translate, -o->rotate, 1.f / bx->scale);
    return (1);
}

int 		ft_scale_hei_null(Uint32 key, t_object *o, t_matrix *tr_m, t_matrix *inv_m)
{
	(void)key;
	(void)o;
	(void)tr_m;
	(void)inv_m;
    return (0);
}