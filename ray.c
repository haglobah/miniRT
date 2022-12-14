/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:25:40 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/12/14 17:15:33 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	*mk_ray(t_3d pos, t_3d dir)
{
	t_ray	*new;

	new = ft_calloc(1, sizeof(t_ray));
	if (new == NULL)
		return (NULL);
	new->pos = pos;
	new->dir = dir;
	// add_to_free_list(new);
	return (new);
}

void	del_ray(t_ray *r)
{
	(void)r;
	// ft_free(r->pos);
	// ft_free(r->dir);
}

int	color_ray(t_ray r)
{
	t_3d	*unit;
	double	t;
	uint32_t clr;

	// print3d("orig", r.pos);
	// print3d("dir ", r.dir);
	unit = mk_unit(r.dir);
	// print3d("unit", *unit);
	t = 0.5 * (unit->y + 1.0);
	// printf("t: %f\n", t);
	t_clr	s = (t_clr){255, 255, 255};
	t_clr	e = (t_clr){127, 180, 255};
	clr = color(s, e, t);
	return (clr);
}
