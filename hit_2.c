/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:03:11 by mhedtman          #+#    #+#             */
/*   Updated: 2023/02/01 15:08:16 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	did_hit(t_hit *h)
{
	if (h->t == 1e6)
		return (false);
	return (true);
}

double	hitpoint_sphere(t_3d center, double radius, t_ray r, double *root)
{
	t_3d	oc;
	double	a;
	double	half_b;
	double	c;
	double	discriminant;

	oc = sum_3d(r.pos, mul(-1, center));
	a = len_squared(r.dir);
	half_b = dot(oc, r.dir);
	c = len_squared(oc) - pow(radius, 2);
	discriminant = sqrt(pow(half_b, 2) - (a * c));
	root[0] = (-half_b + discriminant) / a;
	root[1] = (-half_b - discriminant) / a;
	return (0);
}

void	hit_sphere(t_sphere *sp, t_ray r, t_hit *h)
{
	double	root[2];
	int		i;
	double	t;
	t_3d	hitpos;
	t_3d	hit_normal;

	t = hitpoint_sphere(*sp->pos, sp->diameter / 2, r, root);
	i = 0;
	while (i < 2)
	{
		if (root[i] < h->t && root[i] > 0)
		{
			hitpos = at(r, root[i]);
			hit_normal = unit(sub_3d(at(r, root[i]), *sp->pos));
			update_hit(h,
				(t_uhit){hitpos, root[i], hit_normal, false, sp->color});
		}
		i++;
	}
}

double	hitpoint_plane(t_3d support, t_3d normal, t_ray r)
{
	t_coor_plane	pl;
	double			t;
	double			dividend;
	double			divisor;
	t_3d			abc;

	pl = (t_coor_plane){.a = normal.x, .b = normal.y, .c = normal.z,
		.d = dot(support, normal)};
	abc = (t_3d){pl.a, pl.b, pl.c};
	dividend = pl.d - dot(abc, r.pos);
	divisor = dot(abc, r.dir);
	t = dividend / divisor;
	return (t);
}

void	hit_plane(t_plane *pl, t_ray r, t_hit *h)
{
	double	t;
	t_3d	hitpos;

	t = hitpoint_plane(*pl->pos, *pl->normal, r);
	if (t <= 0.0)
		return ;
	else
	{
		if (t < h->t)
		{
			hitpos = at(r, t);
			update_hit(h, (t_uhit){hitpos, t, *pl->normal, true, pl->color});
		}
	}
}
