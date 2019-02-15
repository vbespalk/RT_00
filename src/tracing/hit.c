
#include <zconf.h>
#include "rt.h"

static void		ft_hit_push(t_hit *node, t_object *o, float (*refr)[2])
{
	node->o = o;
	(*refr)[0] = (node->prev) ? node->prev->o->refr : DEFAULT_REFR;
	(*refr)[1] = o->refr;
}

static void		ft_hit_remove(t_hit *node, t_object *o, float (*refr)[2])
{
	t_hit	*tmp;

	tmp = node;
	(*refr)[0] = o->refr;
	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
	if (!(node->next) || !(node->next->o))
		(*refr)[1] = (node->prev) ? node->prev->o->refr : DEFAULT_REFR;
	else
	{
		while (node->next && node->next->o)
			node = node->next;
		(*refr)[1] = node->o->refr;
		while (node->next)
			node = node->next;
		node->next = tmp;
		tmp->prev = node;
		tmp->next = NULL;
	}
	tmp->o = NULL;
}

void			ft_get_refrs(t_ray *ray, float (*refr)[2])
{
	int		i;

	i = -1;
	while (++i <= ray->stack_i && ray->stack[i] != ray->coll->o)
		;
	refr[0](--i < 0) ? DEFAULT_REFR : ray->stack[i]->refr;
}

void			ft_handle_hit(t_ray *ray)
{
	int		i;

	i = -1;
	while (++i <= ray->stack_i && ray->stack[i] != ray->coll->o)
		;
	if (i > ray->stack_i)
		ft_hit_push();
	else
		ft_hit_remove();
}
