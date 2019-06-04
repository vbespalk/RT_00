/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 18:55:52 by domelche          #+#    #+#             */
/*   Updated: 2019/05/25 18:55:53 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_get_refrs(t_ray *ray, float (*refr)[2])
{
	int		i;

	i = ray->stack_i;
	while (i >= 0 && ray->stack[i] != ray->coll->o)
		--i;
	if (i < 0)
	{
		(*refr)[0] = (ray->stack_i < 0) ?
			DEFAULT_REFR : (ray->stack[ray->stack_i])->refr;
		(*refr)[1] = ray->coll->o->refr;
	}
	else
	{
		(*refr)[0] = ray->coll->o->refr;
		if (i < ray->stack_i)
			(*refr)[1] = (ray->stack[i + 1])->refr;
		else if (i == 0)
			(*refr)[1] = DEFAULT_REFR;
		else
			(*refr)[1] = (ray->stack[i - 1])->refr;
	}
}

void	ft_handle_hit(t_ray *ray, t_object *o)
{
	int		i;

	i = ray->stack_i;
	while (i >= 0 && ray->stack[i] != o)
		--i;
	if (i < 0)
		ray->stack[++(ray->stack_i)] = o;
	else
	{
		ray->stack[i] = NULL;
		while (++i <= ray->stack_i)
		{
			ray->stack[i - 1] = ray->stack[i];
			ray->stack[i] = NULL;
		}
		--(ray->stack_i);
	}
}
