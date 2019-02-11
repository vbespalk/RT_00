
#include "json.h"

void	ft_destroy(t_checker checker)
{
    checker->valid = 0;
    free((void*)checker->stack);
    free((void*)checker);
}

int		ft_reject(t_checker checker)
{
	ft_destroy(checker);
    return (FALSE);
}

int		ft_push(t_checker checker, int mode)
{
    checker->top += 1;
    if (checker->top >= checker->depth)
        return (FALSE);
    checker->stack[checker->top] = mode;
    return (TRUE);
}

int		ft_pop(t_checker jc, int mode)
{
    if (jc->top < 0 || jc->stack[jc->top] != mode)
        return (FALSE);
    jc->top -= 1;
    return (TRUE);
}

int		ft_handle_next_state
			(t_checker checker, int is_push, t_modes mode, t_states state)
{
	if (is_push)
	{
		if (!ft_push(checker, mode))
        	return (FALSE);
	}
	else
	{
		if (!ft_pop(checker, mode))
        	return (FALSE);
	}
    checker->state = state;
	return (TRUE);
}
