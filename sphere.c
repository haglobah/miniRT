/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 11:11:48 by mhedtman          #+#    #+#             */
/*   Updated: 2022/12/16 13:43:50 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	set_front_face(t_ray r, t_3d v, t_hrecord *hrecord)
{
	if (dot(r.dir, v) > 0.0) 
	{
		hrecord->normal = mul(-1, v);
		hrecord->front_face = false;
	}
	else
	{
		hrecord->normal = &v;
		hrecord->front_face = true;
	}
}

void	set_front_normal(t_ray r, t_3d v, t_hrecord *hrecord)
{
	hrecord->front_face = dot(r.dir, v) < 0;
	if (hrecord->front_face == true)
		hrecord->normal = &v;
	else
		hrecord->normal = mul(-1, v);
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

bool	hit_sphere(t_3d center, double radius, t_ray r, double t_min, double t_max, t_hrecord *rec)
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
		return (false);
	double sqrtd = sqrt(discriminant);
	double root = (half_b - sqrtd) / a;
	if (root < t_min || t_max < root)
	{
		root = (-half_b + sqrtd) / a;
		if (root < t_min || t_max < root)
			return (false);
	}
    *rec->t = root;
	rec->point = at(r, *rec->t);
	t_3d *outward_normal = mul(1 / radius, *sum_3d(*rec->point, *mul(-1, center)));
	set_front_normal(r, *outward_normal, rec);
	return (true);
		// return (-half_b - (sqrt(discriminant) / a));
}
