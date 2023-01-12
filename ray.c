/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:25:40 by bhagenlo          #+#    #+#             */
/*   Updated: 2023/01/12 16:35:18 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	*mk_ray(t_3d pos, t_3d dir)
{
	t_ray	*new;

	new = ft_calloc(1, sizeof(t_ray));
	if (new == NULL)
		return (NULL);
	new->pos = pos;
	new->dir = dir;
	// add_to_free_list(new);
	return (new);
}

void	del_ray(t_ray *r)
{
	(void)r;
	// ft_free(r->pos);
	// ft_free(r->dir);
}

uint32_t	shade(t_clr color, double coeff)
{
	t_3d	*result;
	t_3d	clr;
	double	ambient = 0.2;
	double	diffuse = 0.7;

	clr.x = color.r;
	clr.y = color.g;
	clr.z = color.b;

	t_3d	*background =  sum_3d(*mul(ambient, clr), *mul(diffuse, clr));
	if (coeff <= 0.0)
	{
		result = sum_3d(*mul(coeff, clr), *background);
	}
	else
	{
		result = background;
		// coeff *= -1;
	}
	return (rgb(result->x, result->y, result->z));
}

uint32_t	compute_clr(t_mrt *m, t_hit *h)
{
	double		coeff;
	uint32_t	clr;

	coeff = -dot(*mk_unit(*m->l->pos), h->normal);
	clr = shade(h->clr, coeff);
	return (clr);
}

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
			update_hit(h, sp, t, r, sp->color);
	}
}

void	hit_plane(t_plane *pl, t_ray *r, t_hit *h)
{
	double	lo;
	double	hi;
	double	t;

	(void)pl;
	(void)r;
	(void)h;
}

void	hit_cylinder(t_cyl *cyl, t_ray *r, t_hit *h)
{
	double	lo;
	double	hi;
	double	t;

	(void)cyl;
	(void)r;
	(void)h;
}

int	trace_ray(t_ray *r, t_mrt *m)
{
	uint32_t clr;
	double	t;
	t_hit	h;
	int		i;
	// double	t2;
	
	// Hier eher loop für mehrere Gegenstände
	i = -1;
	while (++i < m->sp_count)
	{
		hit_sphere(&m->sp[i], r, &h);
	}
	i = -1;
	while (++i < m->pl_count)
	{
		hit_plane(&m->pl[i], r, &h);
	}
	i = -1;
	while (++i < m->cyl_count)
	{
		hit_cylinder(&m->cyl[i], r, &h);
	}
	clr = compute_clr(m, &h);
	return (clr);
}
