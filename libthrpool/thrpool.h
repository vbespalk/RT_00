
#ifndef THRPOOL_H

# define THRPOOL_H

# include <pthread.h>
# include <stdlib.h>

typedef struct			s_thrnode
{
	pthread_t			*thread;
	struct s_thrnode	*prev;
	struct s_thrnode	*next;
}						t_thrnode;

typedef struct			s_thrpool
{
	int					count;
	t_thrnode			*head;
	t_thrnode			*tail;
}						t_thrpool;

#endif
