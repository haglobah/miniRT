/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:25:40 by bhagenlo          #+#    #+#             */
/*   Updated: 2023/01/27 14:42:30 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	mk_ray(t_3d pos, t_3d dir)
{
	t_ray	new;

	new = (t_ray){pos, dir};
	return (new);
}

uint32_t	scattered_reflection(t_mrt *m, t_clr clr, bool from_plane, double coeff)
{
	t_clr	res;

	if (coeff < 0)
	{
		if (from_plane)
		{
			res = sum_clr(
			mul_clr(m->amb->ratio, m->amb->color),
			mul_clr(m->l->brightness * -coeff,
			clr));
		}
		else
		{
			res = mul_clr(m->amb->ratio, m->amb->color);
		}
	}
	else
	{
		res = sum_clr(
		mul_clr(m->amb->ratio, m->amb->color),
		mul_clr(m->l->brightness * coeff,
		clr));
	}
	return (rgb(res.r, res.g, res.b));
}

bool	trace_light(t_mrt *m, t_3d *light_dir, t_hit *ray_hit)
{
	t_ray	light;
	t_hit	light_hit;
	double	d_light_blocking;
	double	d_light_ray;
	bool	shaded;

	light = mk_ray(*m->l->pos,
			unit(*light_dir));
	trace_ray(m, light, &light_hit);


	d_light_blocking = dist(light.pos, at(light, light_hit.t));
	d_light_ray = dist(light.pos, ray_hit->pos);
	// print_hit(light_hit);
	// printf("d(other_hit, light): %f\nd(orig_hit, light): %f\n", other_hit_dist, light_rayhit_dist);
	if (d_light_blocking + EPSILON < d_light_ray)
	{
		shaded = true;
	}
	else
	{
		shaded = false;
	}
	return (shaded);
}

uint32_t	compute_hitpoint_clr(t_mrt *m, t_hit *h)
{
	double		coeff;
	uint32_t	clr;
	bool		hit_something;
	bool		shaded;
	t_3d 		light_dir;
	static int	i;

	hit_something = did_hit(h);
	if (hit_something)
	{
		light_dir = sub_3d(
					h->pos,
					*m->l->pos);
		shaded = trace_light(m, &light_dir, h);
		// printf("shaded? %s\n", shaded ? "yes!" : "no");
		if (shaded)
		{
			clr = scattered_reflection(m, h->clr, h->from_plane, 0.0);
		}
		else
		{
			coeff = -dot(
				unit(light_dir),
				unit(h->normal));
			clr = scattered_reflection(m, h->clr, h->from_plane, coeff);
			// printf("coeff: %f\n", coeff);
			// print_clr(h->clr);
			// printf("hit: i = %i\n", i);
			// print_hit(*h);
		}
		i++;
	}
	else
		clr = rgb(0, 0, 0);
	return (clr);
}

void	trace_ray(t_mrt *m, t_ray r, t_hit *h)
{
	uint32_t clr;
	int		i;
	
	*h = (t_hit){(t_3d){0, 0, 0},
				(t_3d){0, 0, 0}, false, 1e6, (t_clr){0, 0, 0, 0}};
	i = -1;
	while (++i < m->sp_count)
	{
		hit_sphere(&m->sp[i], r, h);
	}
	i = -1;
	while (++i < m->pl_count)
	{
		hit_plane(&m->pl[i], r, h);
	}
	i = -1;
	while (++i < m->cyl_count)
	{
		hit_cylinder(&m->cyl[i], r, h);
	}
}
