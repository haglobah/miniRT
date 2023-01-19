/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:59:43 by bhagenlo          #+#    #+#             */
/*   Updated: 2023/01/19 14:04:30 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
# include <time.h>

t_3d	*mk_3d(t_lst *lst, double x, double y, double z)
{
	t_3d	*new;
	static int	counter;

	new = ft_calloc(1, sizeof(t_3d));
	if (new == NULL)
		return (NULL);
	new->x = x;
	new->y = y;
	new->z = z;
	add_to_list(&lst, new, NULL, NULL);
	return (new);
}

void	del_3d(t_3d *v)
{
	ft_free(v);
}

t_3d	*sum_3d(t_lst *save_lst, t_3d v, t_3d w)
{
	t_3d	*new;

	new = mk_3d(save_lst, v.x + w.x, v.y + w.y, v.z + w.z);
	return (new);
}

t_3d	*sum4_3d(t_lst *save_lst, t_3d v, t_3d w, t_3d u, t_3d z)
{
	t_3d	*new;

	new = mk_3d(save_lst, v.x + w.x + u.x + z.x, 
				v.y + w.y + u.y + z.y,
				v.z + w.z + u.z + z.z);
	return (new);
}

t_3d	mul(t_lst *save_lst, double k, t_3d v)
{
	t_3d	new;

	(void)save_lst;
	new = (t_3d){k * v.x, k * v.y, k * v.z};
	return (new);
}

t_3d	*sub_3d(t_lst *save_lst, t_3d v, t_3d w)
{
	t_3d	*new;

	new = sum_3d(save_lst, v, mul(save_lst, -1, w));
	return (new);
}

t_3d	*sub4_3d(t_lst *save_lst, t_3d v, t_3d w, t_3d u, t_3d z)
{
	t_3d	*new;

	new = mk_3d(save_lst, v.x - w.x - u.x - z.x, 
				v.y - w.y - u.y - z.y,
				v.z - w.z - u.z - z.z);
	return (new);
}

double	dot(t_3d v, t_3d w)
{
	return (v.x * w.x + v.y * w.y + v.z * w.z);
}

t_3d	cross(t_lst *save_lst, t_3d v, t_3d w)
{
	t_3d	new;

	new = (t_3d){v.y * w.z - w.y * v.z,
				v.z * w.x - w.z * v.x,
				v.x * w.y - w.x * v.y};
	return (new);
}

double	len_squared(t_3d v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

double	sq(double a)
{
	return (a * a);
}

double	dist(t_3d v, t_3d w)
{
	double	res;

	res = sqrt( sq(v.x - w.x)
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

t_3d	*at(t_lst *save_lst, t_ray ray, double t)
{
	t_3d	dir;
	t_3d	*ret;

	dir = mul(save_lst, t, ray.dir);
	ret = sum_3d(save_lst, dir, ray.pos); // cam position
	return (ret);
}

t_3d	mk_unit(t_lst *save_lst, t_3d v)
{
	double vlen;
	
	vlen = sqrt(len_squared(v));
	t_3d test = mul(save_lst, 1.0 / vlen, v);
	return (test);
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
