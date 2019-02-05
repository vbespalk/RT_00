
#include "thrpool.h"

void		ft_free_list(t_thrnode *tail)
{
	t_thrnode	*node;

	while (tail)
	{
		node = tail;
		if (tail->thread)
			pthread_cancel(*(tail->thread));
		tail = tail->prev;
		free(node);
	}
}

void		ft_thread_list_init(t_thrnode **head, t_thrnode **tail, int count)
{
	t_thrnode	*prev;
	t_thrnode	*node;
	int			i;

	if (!head || !tail)
		return ;
	*head = NULL;
	*tail = NULL;
	prev = NULL;
	i = -1;
	while (++i < count)
	{
		if (!(node = (t_thrnode *)malloc(sizeof(t_thrnode))))
			return (ft_free_list(prev));
		node->prev = prev;
		if (!i)
			head = node;
		if (prev)
			prev->next = node;
		prev = node;
		node = node->next;
	}
	return (head);
}

t_thrpool	*ft_thrpoolnew(int threads)
{
	t_thrpool	*pool;

	pool = (t_thrpool *)malloc(sizeof(t_thrpool));
}
