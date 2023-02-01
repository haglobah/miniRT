/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 10:31:04 by bhagenlo          #+#    #+#             */
/*   Updated: 2023/02/01 13:27:59 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


bool	did_hit(t_hit *h)
{
	if (h->t == 1e6)
		return (false);
	return (true);
}

void	update_hit(t_hit *h, t_3d pos, double t, t_3d *normal, bool from_plane, t_clr clr)
{
	h->pos = pos;
	h->normal = *normal;
	h->from_plane = from_plane;
	h->t = t;
	h->clr = clr;
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
			update_hit(h, hitpos, root[i], &hit_normal, false, sp->color);
		}
		i++;
	}
	// if (t <= 0.0)
	// 	return ;
	// else
	// {
	// 	if (t < h->t)
	// 	{
	// 		hitpos = at(r, t);
	// 		hit_normal = unit(sub_3d(at(r, t), *sp->pos));
	// 		update_hit(h, hitpos, t, &hit_normal, sp->color);
	// 		// print_hit(*h);
	// 	}
	// }
}

void	print_plane(t_coor_plane pl)
{
	printf("  a: %f\n", pl.a);
	printf("  b: %f\n", pl.b);
	printf("  c: %f\n", pl.c);
	printf("  d: %f\n\n", pl.d);
}

double	hitpoint_plane(t_3d support, t_3d normal, t_ray r)
{
	t_coor_plane	pl;
	double			t;
	double			dividend;
	double			divisor;

	pl = (t_coor_plane){.a = normal.x, .b = normal.y, .c = normal.z,
		  .d = dot(support, normal)};
	t_3d abc = (t_3d){pl.a, pl.b, pl.c};
	dividend = pl.d - dot(abc, r.pos);
	// print_plane(pl);
	// printf("dividend: %f\n", dividend);
	// printf("          ---------------\n");
	divisor = dot(abc, r.dir);
	// printf("divisor:  %f\n", divisor);
	t = dividend / divisor;
	return (t);
}

void	hit_plane(t_plane *pl, t_ray r, t_hit *h)
{
	double	t;
	t_3d	hitpos;

	t = hitpoint_plane(*pl->pos, *pl->normal, r);
	// printf("t: %f\n", t);
	if (t <= 0.0)
		return ;
	else
	{
		if (t < h->t)
		{
			hitpos = at(r, t);
			// print_clr(pl->color);
			update_hit(h, hitpos, t, pl->normal, true, pl->color);
			// print_hit(*h);
		}
	}
}

bool	is_in_plane(t_3d p, t_coor_plane e)
{
	return (dot(p, (t_3d){e.a, e.b, e.c}) == e.d);
}

// bool	is_in_disc(t_3d p, t_3d *c, double r, t_coor_plane *e, int index)
// {
// 	if (is_in_plane(p, e[index]))
// 	{
// 		print_3d("hitpoint:", p);
// 		printf("dist: %f <=? r = %f\n", dist(p, c[index]), r);
// 	}
// 	return (/* dist(p, c[index]) <= r && */ is_in_plane(p, e[index]));
// }

void	hit_tube(t_cyl *cyl, t_ray ray, t_hit *hit)
{
	t_3d	a;
	double	r;
	double	h;
	t_3d	n;
	t_3d	b;
	t_3d	f;
	t_3d	nxa;
	double	d[4];
	double	t[2];

	t_3d	hitpos;
	t_3d	hit_normal;

	a = unit(*cyl->axis);
	n = unit(ray.dir);
	b = *cyl->pos;
	f = sub_3d(b, ray.pos);
	r = cyl->diameter / 2.0;
	h = cyl->height;

	//tube
	nxa = cross(n, a);
	d[0] = (dot(nxa, cross(f, a))
		 + sqrt(dot(nxa, nxa) * sq(r) - dot(a, a) * sq(dot(f, nxa))))
		 / dot(nxa, nxa);
	d[1] = (dot(nxa, cross(f, a))
		 - sqrt(dot(nxa, nxa) * sq(r) - dot(a, a) * sq(dot(f, nxa))))
		 / dot(nxa, nxa);
	t[0] = dot(a, sub_3d(mul(d[0], n), f));
	t[1] = dot(a, sub_3d(mul(d[1], n), f));
	if (t[0] >= 0 && t[0] <= h)
	{
		hitpos = at(ray, d[0]);
		hit_normal = unit(sub_3d(hitpos, sum_3d(mul(t[0], a), b)));
		update_hit(hit, hitpos, d[0], &hit_normal, false, cyl->color);
	}
	if (t[1] >= 0 && t[1] <= h)
	{
		hitpos = at(ray, d[1]);
		hit_normal = unit(sub_3d(hitpos, sum_3d(mul(t[1], a), b)));
		update_hit(hit, hitpos, d[1], &hit_normal, false, cyl->color);
	}
}

void	update_disk_hit(double d, t_3d center, double r, t_hit *hit, t_cyl *cyl, t_ray ray)
{
	t_3d	hitpos;
	t_3d	hit_normal;

	if (d < hit->t && dist(center, at(ray, d)) < r)
	{
		hitpos = at(ray, d);
		hit_normal = unit(mul(-1, *cyl->axis));
		update_hit(hit, hitpos, d, &hit_normal, true, cyl->color);
	}
}

void	hit_disk(t_cyl *cyl, t_ray ray, t_hit *hit)
{
	t_3d	a;
	double	r;
	double	h;
	t_3d	n;
	t_3d	b;
	t_3d	f;
	double	d[4];

	t_3d	hitpos;
	t_3d	hit_normal;

	a = unit(*cyl->axis);
	n = unit(ray.dir);
	b = *cyl->pos;
	f = sub_3d(b, ray.pos);
	r = cyl->diameter / 2.0;
	h = cyl->height;
	
	t_3d	c[2];
	
	c[0] = b;
	c[1] = sum_3d(b, mul(h, a));
	d[2] = hitpoint_plane(c[0], a, ray);
	d[3] = hitpoint_plane(c[1], a, ray);
	update_disk_hit(d[2], c[0], r, hit, cyl, ray);
	update_disk_hit(d[3], c[1], r, hit, cyl, ray);
}

void	hit_cylinder(t_cyl *cyl, t_ray ray, t_hit *hit)
{
	hit_tube(cyl, ray, hit);
	hit_disk(cyl, ray, hit);
}
