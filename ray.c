/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:25:40 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/12/15 11:18:45 by bhagenlo         ###   ########.fr       */
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

double	hit_sphere(t_3d center, double radius, t_ray r)
{
	t_3d	a_c;

    a_c = *sum_3d(r.pos,  *mul(-1, center));
    double a = dot(r.dir, r.dir);
    double b = 2.0 * dot(a_c, r.dir);
    double c = dot(a_c, a_c) - radius*radius;
    double discriminant = b*b - 4*a*c;
	if (discriminant < 0)
		return (-1.0);
    else
		return (-b - sqrt(discriminant) / (2.0 * a));
}

uint32_t	cons_sphere_clr(t_3d unit)
{
	t_3d	*result;

	result = mul(0.5, *sum_3d(unit, (t_3d){1, 1, 1}));
	return (dcolor(result->x, result->y, result->z));
}

int	color_ray(t_ray r)
{
	t_3d	*unit;
	double	t;
	uint32_t clr;

	t = hit_sphere((t_3d){0, 0, -1}, 0.5, r);
	if (t > 0.0)
	{
		unit = mk_unit(*sum_3d(at(r, t), (t_3d){0, 0, 1}));
		clr = cons_sphere_clr(*unit);
		return (clr);
	}
	unit = mk_unit(r.dir);
	t = 0.5 * (unit->y + 1.0);
	t_clr	s = (t_clr){255, 255, 255};
	t_clr	e = (t_clr){127, 180, 255};
	clr = color(s, e, t);
	return (clr);
}
