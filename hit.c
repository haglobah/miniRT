/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 10:31:04 by bhagenlo          #+#    #+#             */
/*   Updated: 2023/01/13 11:26:54 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	hitpoint_sphere(t_3d center, double radius, t_ray r)
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

bool	did_hit(t_hit *h)
{
	if (h->t == 1e6)
		return (false);
	return (true);
}

void	update_hit(t_hit *h, t_sphere *sp, double t, t_ray *r, t_clr clr)
{
	h->pos = *at(*r, t);
	h->normal = *mk_unit(*sub_3d(*at(*r, t), *sp->pos));
	h->t = t;
	h->clr = clr;
}

void	hit_sphere(t_sphere *sp, t_ray *r, t_hit *h)
{
	double	lo;
	double	hi;
	double	t;

	t = hitpoint_sphere(*sp->pos, sp->diameter, *r);
	if (t <= 0.0)
		return ;
	else
	{
		if (t < h->t)
		{
			update_hit(h, sp, t, r, sp->color);
			// print_hit(*h);
		}
	}
}

// void	hit_plane(t_plane *pl, t_ray *r, t_hit *h)
// {
// 	double	lo;
// 	double	hi;
// 	double	t;

// 	(void)pl;
// 	(void)r;
// 	(void)h;
// }

// void	hit_cylinder(t_cyl *cyl, t_ray *r, t_hit *h)
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
	print3d("pos: ", h.pos);
	print3d("normal: ", h.normal);
	printf("t: %f\n", h.t);
	print_clr(h.clr);
}