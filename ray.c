/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:25:40 by bhagenlo          #+#    #+#             */
/*   Updated: 2023/01/12 09:49:03 by mhedtman         ###   ########.fr       */
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

double	hit_sphere(t_3d center, double radius, t_ray r)
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

uint32_t	cons_sphere_clr(t_clr color, double coeff)
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

int	color_ray(t_ray r, t_mrt *m)
{
	t_3d	*unit;
	t_3d	*thit;
	uint32_t clr;
	double	t;
	double	t2;
	
	// Hier eher loop für mehrere Gegenstände
	t = hit_sphere(*m->sp->pos, m->sp->diameter, r);
	if (t > 0.0)
	{
		t_3d *thit = at(r, t);
		t_3d *surface_normal = mk_unit(*sum_3d(*thit, *mul(-1.0, *m->sp->pos)));
		double	coeff = -dot(*mk_unit(*m->l->pos), *surface_normal);
		clr = cons_sphere_clr(m->sp->color, coeff);
		return (clr);
	}

	// t_sphere *second_sphere;

	// second_sphere = ft_calloc(1, sizeof(t_sphere));
	// second_sphere->pos = mk_3d(0, -1, 0);
	// second_sphere->diameter = 0.3;
	// second_sphere->color = (t_clr){0.9 * 255, 0.2 * 255, 0.3 * 255};
	// t2 = hit_sphere(*second_sphere->pos, second_sphere->diameter, r);
	// if (t2 > 0.0)
	// {
	// 	t_3d *thit2 = at(r, t2);
	// 	t_3d *surface_normal2 = mk_unit(*sum_3d(*thit2, *mul(-1.0, *second_sphere->pos)));
	// 	double	coeff = -dot(*light->pos, *surface_normal2);
	// 	// printf("COEFF: %f\n", coeff);
	// 	clr = cons_sphere_clr(second_sphere->color, coeff);
	// 	return (clr);
	// }
	// unit = mk_unit(r.dir);
	// t = 0.5 * (unit->y + 1.0);
	// t_clr	s = (t_clr){255, 255, 255};
	// t_clr	e = (t_clr){127, 180, 255};
	// clr = color(s, e, t);
	clr = rgb(0, 0, 0); // -> background
	return (clr);
}
