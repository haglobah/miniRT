/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:25:40 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/12/16 14:07:47 by mhedtman         ###   ########.fr       */
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
	t_3d	oc;
	double	a;
	double	half_b;
	double	c;
    double	discriminant;

	oc = *sum_3d(r.pos, *mul(-1, center));
	a = len_squared(r.dir);
	half_b = dot(oc, r.dir);
	c = len_squared(oc) - pow(radius, 2);
	discriminant = pow(half_b, 2) - (a * c);
	if (discriminant < 0)
		return (-1.0);
	else
		return (-half_b - (sqrt(discriminant) / a));
}

uint32_t	cons_sphere_clr(t_3d unit)
{
	t_3d	*result;

	unit.x += 1.0;
	unit.y += 1.0;
	unit.z += 1.0;
	result = mul((1.0/2.0), unit);
	return (dcolor(result->x, result->z, result->y));
}

int	color_ray(t_ray r)
{
	t_3d	*unit;
	double	t;
	double	t2;
	uint32_t clr;


	// Hier eher loop für mehrere Gegenstände
	t = hit_sphere((t_3d){0, 0, -1}, 0.5, r);
	if (t > 0.0)
	{
		unit = at(r, t);
		unit->z -= -1;
		unit = mk_unit(*unit);
		clr = cons_sphere_clr(*unit);
		return (clr);
	}
	t2 = hit_sphere((t_3d){0, -100.5, -1}, 100, r);
	if (t2 > 0.0)
	{
		unit = at(r, t2);
		unit->z -= -1;
		unit = mk_unit(*unit);
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
