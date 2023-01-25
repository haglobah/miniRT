/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 10:31:04 by bhagenlo          #+#    #+#             */
/*   Updated: 2023/01/25 16:43:58 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


bool	did_hit(t_hit *h)
{
	if (h->t == 1e6)
		return (false);
	return (true);
}

void	update_hit(t_hit *h, t_3d pos, double t, t_3d *normal, t_clr clr)
{
	h->pos = pos;
	h->normal = *normal;
	h->t = t;
	h->clr = clr;
}

double	hitpoint_sphere(t_3d center, double radius, t_ray r)
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
	discriminant = pow(half_b, 2) - (a * c);
	if (discriminant < 0)
		return (-1.0);
	else 
		return ((-half_b - sqrt(discriminant)) / a);
}

void	hit_sphere(t_sphere *sp, t_ray r, t_hit *h)
{
	// Wofuer waren die nochmal?
	// double	lo;
	// double	hi;
	double	t;
	t_3d	hitpos;
	t_3d	hit_normal;

	t = hitpoint_sphere(*sp->pos, sp->diameter, r);
	if (t <= 0.0)
		return ;
	else
	{
		if (t < h->t)
		{
			hitpos = at(r, t);
			hit_normal = mk_unit(sub_3d(at(r, t), *sp->pos));
			update_hit(h, hitpos, t, &hit_normal, sp->color);
			// print_hit(*h);
		}
	}
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
			update_hit(h, hitpos, t, pl->normal, pl->color);
			// print_hit(*h);
		}
	}
}

// void	hit_cylinder(t_cyl *cyl, t_ray r, t_hit *h)
// {
// 	double	lo;
// 	double	hi;
// 	double	t;

// 	(void)cyl;
// 	(void)r;
// 	(void)h;
// }

void	print_hit(t_hit h)
{
	// print3d("  pos", h.pos);
	// print3d("  normal", h.normal);
	printf("  t: %f\n", h.t);
	printf("  ");
	print_clr(h.clr);
}