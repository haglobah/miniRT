/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:25:40 by bhagenlo          #+#    #+#             */
/*   Updated: 2023/02/01 12:17:57 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	mk_ray(t_3d pos, t_3d dir)
{
	t_ray	new;

	new = (t_ray){pos, dir};
	return (new);
}

uint32_t	scattered_reflection(t_mrt *m, t_clr clr, bool plane, double coeff)
{
	t_clr	res;

	if (coeff < 0)
	{
		if (plane)
		{
			res = sum_clr(
					mul_clr(m->amb->ratio, m->amb->color),
					mul_clr(m->l->brightness * -coeff,
						clr));
		}
		else
			res = mul_clr(m->amb->ratio, m->amb->color);
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
	bool		hit_and_shaded[2];
	t_3d		light_dir;
	static int	i;

	hit_and_shaded[0] = did_hit(h);
	if (hit_and_shaded[0])
	{
		light_dir = sub_3d(h->pos, *m->l->pos);
		hit_and_shaded[1] = trace_light(m, &light_dir, h);
		if (hit_and_shaded[1])
			clr = scattered_reflection(m, h->clr, h->from_plane, 0.0);
		else
		{
			coeff = -dot(unit(light_dir), unit(h->normal));
			clr = scattered_reflection(m, h->clr, h->from_plane, coeff);
		}
		i++;
	}
	else
		clr = rgb(0, 0, 0);
	return (clr);
}

void	trace_ray(t_mrt *m, t_ray r, t_hit *h)
{
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
