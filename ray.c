/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:25:40 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/12/18 14:41:37 by mhedtman         ###   ########.fr       */
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
		return ((-half_b - sqrt(discriminant)) / a);
}

uint32_t	cons_sphere_clr(t_3d unit, t_d reflection)
{
	t_3d	*result;

	unit.x += 1.0;
	unit.y += 1.0;
	unit.z += 1.0;
	result = mul(reflection, (t_3d){0.9 * 255, 0.2 * 255, 0.3 * 255});
	return (rgb(result->x, result->y, result->z));
}

int	color_ray(t_ray r, t_sphere *sphere)
{
	t_3d	*unit;
	t_3d	*thit;
	double	t;
	double	t2;
	uint32_t clr;

	// Hier eher loop für mehrere Gegenstände
	t = hit_sphere(sphere->pos, sphere->diameter, r);
	if (t > 0.0)
	{
		t_3d *thit = at(r, t);
		t_3d *unit_vektor = mk_unit(*sum_3d(*thit, *mul(-1.0, sphere->pos)));
		double	reflection = -dot(r.dir, *unit_vektor);
		clr = cons_sphere_clr(*unit_vektor, reflection);
		return (clr);
	}
	// t2 = hit_sphere((t_3d){0, 100.5, -1}, 100, r);
	// if (t2 > 0.0)
	// {
	// 	unit = mk_unit(*sum_3d(*at(r, t2), *mul(-1.0, (t_3d){0, 0, -1})));
	// 	clr = cons_sphere_clr(*unit);
	// 	return (clr);
	// }
	// unit = mk_unit(r.dir);
	// t = 0.5 * (unit->y + 1.0);
	// t_clr	s = (t_clr){255, 255, 255};
	// t_clr	e = (t_clr){127, 180, 255};
	// clr = color(s, e, t);
	clr = rgb(0, 0, 0);
	return (clr);
}
