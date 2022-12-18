/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:59:43 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/12/18 13:59:06 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
# include <time.h>

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

t_3d	*mk_random_3d(void)
{
	t_3d	*new;
	double	x;
	double	y;
	double	z;

	srand(time(NULL));
	x = (double) rand() / RAND_MAX * 2 - 1;
	y = (double) rand() / RAND_MAX * 2 - 1;
	z = (double) rand() / RAND_MAX * 2 - 1;
	new = mk_3d(x, y ,z);
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
	t_3d	*dir;
	t_3d	*ret;

	dir = mul(t, ray.dir);
	ret = sum_3d(*dir, (t_3d){0, 0, 0});
	return (ret);
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

void	printray(char *s, t_ray v)
{
	printf("%s DIR: (%f %f %f)\n", s, v.dir.x, v.dir.y, v.dir.z);
	printf("%s POS: (%f %f %f)\n", s, v.pos.x, v.pos.y, v.pos.z);
}