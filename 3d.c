/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:59:43 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/12/14 17:24:00 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_3d	*mk_3d(double x, double y, double z)
{
	t_3d	*new;

	new = ft_calloc(1, sizeof(t_3d));
	if (new == NULL)
		return (NULL);
	new->x = x;
	new->y = y;
	new->z = z;
	// add_to_free_list(new);
	return (new);
}

void	del_3d(t_3d *v)
{
	ft_free(v);
}

t_3d	*sum_3d(t_3d v, t_3d w)
{
	t_3d	*new;

	new = mk_3d(v.x + w.x, v.y + w.y, v.z + w.z);
	return (new);
}

t_3d	*sum4_3d(t_3d v, t_3d w, t_3d u, t_3d z)
{
	t_3d	*new;

	new = mk_3d(v.x + w.x + u.x + z.x, 
				v.y + w.y + u.y + z.y,
				v.z + w.z + u.z + z.z);
	return (new);
}

t_3d	*mul(double k, t_3d v)
{
	t_3d	*new;

	new = mk_3d(k * v.x, k * v.y, k * v.z);
	return (new);
}

double	dot(t_3d v, t_3d w)
{
	return (v.x * w.x + v.y * w.y + v.z * w.z);
}

t_3d	*cross(t_3d v, t_3d w)
{
	t_3d	*new;

	new = mk_3d(v.y * w.z - w.y * v.z,
				v.z * w.x - w.z * v.x,
				v.x * w.y - w.x * v.y);
	return (new);
}

double	len_squared(t_3d v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

t_3d	*at(t_ray ray, double t)
{
	return (sum_3d(ray.pos, *mul(t, ray.dir)));
}

t_3d	*mk_unit(t_3d v)
{
	double vlen;

	vlen = sqrt(len_squared(v));
	return (mul(1.0 / vlen, v));
}

void	print3d(char *s, t_3d v)
{
	printf("%s: (%f %f %f)\n", s, v.x, v.y, v.z);
}