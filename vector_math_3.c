/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 16:22:42 by mhedtman          #+#    #+#             */
/*   Updated: 2023/01/25 16:27:36 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	sq(double a)
{
	return (a * a);
}

double	dist(t_3d v, t_3d w)
{
	double	res;

	res = sqrt(sq(v.x - w.x)
			+ sq(v.y - w.y)
			+ sq(v.z - w.z));
	if (res < 0.0)
		return (-res);
	return (res);
}

bool	v_iseq(t_3d *v, t_3d *w)
{
	return (dist(*v, *w) == 0);
}

t_3d	at(t_ray ray, double t)
{
	t_3d	dir;
	t_3d	ret;

	dir = mul(t, ray.dir);
	ret = sum_3d(dir, ray.pos);
	return (ret);
}

t_3d	mk_unit(t_3d v)
{
	double	vlen;
	t_3d	new;

	vlen = sqrt(len_squared(v));
	new = mul(1.0 / vlen, v);
	return (new);
}
