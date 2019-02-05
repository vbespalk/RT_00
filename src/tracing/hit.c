
#include "rt.h"

t_hit			*ft_hit_list_new(int length)
{
	t_hit	*head;
	t_hit	*prev;
	t_hit	*node;
	int		i;

	head = NULL;
	prev = NULL;
	i = 0;
	while (i < length)
	{
		node = (t_hit *)ft_smemalloc(sizeof(t_hit), "ft_hit_list_new");
		node->prev = prev;
		if (!i)
			head = node;
		if (prev)
			prev->next = node;
		prev = node;
		node = node->next;
		++i;
	}
	return (head);
}

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

void			ft_handle_hit(t_hit *head, t_object *o, float (*refr)[2])
{
	while (head->o && head->o != o)
		head = head->next;
	if (!(head->o))
		ft_hit_push(head, o, refr);
	else
		ft_hit_remove(head, o, refr);
}
