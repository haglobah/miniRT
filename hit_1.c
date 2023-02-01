/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 10:31:04 by bhagenlo          #+#    #+#             */
/*   Updated: 2023/02/01 15:09:39 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	update_hit(t_hit *h, t_uhit uh)
{
	h->pos = uh.pos;
	h->normal = uh.normal;
	h->from_plane = uh.from_plane;
	h->t = uh.t;
	h->clr = uh.clr;
}

void	update_tube_hit(t_tube_hit th)
{
	t_3d	hitpos;
	t_3d	hit_normal;

	if (th.t >= 0 && th.t <= th.h)
	{
		hitpos = at(th.ray, th.d);
		hit_normal = unit(sub_3d(hitpos, sum_3d(mul(th.t, th.a), th.b)));
		update_hit(th.hit,
			(t_uhit){hitpos, th.d, hit_normal, false, th.cyl->color});
	}
}

void	hit_tube(t_cyl *cyl, t_ray ray, t_hit *hit)
{
	t_tube	t;

	t.a = unit(*cyl->axis);
	t.n = unit(ray.dir);
	t.b = *cyl->pos;
	t.f = sub_3d(t.b, ray.pos);
	t.r = cyl->diameter / 2.0;
	t.h = cyl->height;
	t.nxa = cross(t.n, t.a);
	t.d[0] = (dot(t.nxa, cross(t.f, t.a))
			+ sqrt(dot(t.nxa, t.nxa) * sq(t.r)
				- dot(t.a, t.a) * sq(dot(t.f, t.nxa))))
		/ dot(t.nxa, t.nxa);
	t.d[1] = (dot(t.nxa, cross(t.f, t.a))
			- sqrt(dot(t.nxa, t.nxa) * sq(t.r)
				- dot(t.a, t.a) * sq(dot(t.f, t.nxa))))
		/ dot(t.nxa, t.nxa);
	t.t[0] = dot(t.a, sub_3d(mul(t.d[0], t.n), t.f));
	t.t[1] = dot(t.a, sub_3d(mul(t.d[1], t.n), t.f));
	update_tube_hit((t_tube_hit){t.t[0], t.h, t.d[0], t.a, t.b, cyl, ray, hit});
	update_tube_hit((t_tube_hit){t.t[1], t.h, t.d[1], t.a, t.b, cyl, ray, hit});
}

void	update_disk_hit(double d, t_3d center, double r, t_crh crh)
{
	t_3d	hitpos;
	t_3d	hit_normal;

	if (d < crh.hit->t && dist(center, at(crh.ray, d)) < r)
	{
		hitpos = at(crh.ray, d);
		hit_normal = unit(mul(-1, *crh.cyl->axis));
		update_hit(crh.hit,
			(t_uhit){hitpos, d, hit_normal, true, crh.cyl->color});
	}
}

void	hit_disk(t_cyl *cyl, t_ray ray, t_hit *hit)
{
	t_3d	a;
	double	r;
	t_3d	b;
	double	d[2];
	t_3d	c[2];

	a = unit(*cyl->axis);
	b = *cyl->pos;
	r = cyl->diameter / 2.0;
	c[0] = b;
	c[1] = sum_3d(b, mul(cyl->height, a));
	d[0] = hitpoint_plane(c[0], a, ray);
	d[1] = hitpoint_plane(c[1], a, ray);
	update_disk_hit(d[0], c[0], r, (t_crh){hit, cyl, ray});
	update_disk_hit(d[1], c[1], r, (t_crh){hit, cyl, ray});
}
