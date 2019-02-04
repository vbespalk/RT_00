
#include "rt.h"

t_rhhn			*ft_rhhn_list_new(int length)
{
	write(1, "in ft_rhhn_list_new\n", 21);

	t_rhhn	*head;
	t_rhhn	*prev;
	t_rhhn	*node;
	int		i;

	head = NULL;
	prev = NULL;
	i = 0;
	while (i < length)
	{
		node = (t_rhhn *)ft_smemalloc(sizeof(t_rhhn), "ft_rhhnnew");
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

static void		ft_rhhn_push(t_rhhn *node, t_object *o, float (*refr)[2])
{
	node->o = o;
	(*refr)[0] = (node->prev) ? node->prev->o->refr : DEFAULT_REFR;
	(*refr)[1] = o->refr;
}

static void		ft_rhhn_remove(t_rhhn *node, t_object *o, float (*refr)[2])
{
	t_rhhn	*tmp;

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

void			ft_rhhn_hit(t_rhhn *head, t_object *o, float (*refr)[2])
{
	while (head->o && head->o != o)
		head = head->next;
	if (!(head->o))
		ft_rhhn_push(head, o, refr);
	else
		ft_rhhn_remove(head, o, refr);
}
