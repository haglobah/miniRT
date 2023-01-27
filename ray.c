/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:25:40 by bhagenlo          #+#    #+#             */
/*   Updated: 2023/01/27 13:26:21 by bhagenlo         ###   ########.fr       */
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

bool	in_shadow(t_ray light_ray, t_mrt *m, t_3d *hitpoint)
{
	// uint32_t clr;
	// double	t;
	t_hit	light_hit;
	int		i;
	bool	in_shadow;

	light_hit = (t_hit){(t_3d){0, 0, 0},
				(t_3d){0, 0, 0}, false, 1e6, (t_clr){0, 0, 0, 0}};
	i = -1;
	while (++i < m->sp_count)
	{
		hit_sphere(&m->sp[i], light_ray, &light_hit);
	}
	i = -1;
	// while (++i < m->pl_count)
	// {
	// 	hit_plane(&m->pl[i], light_ray, &light_hit);
	// }
	// i = -1;
	while (++i < m->cyl_count)
	{
		hit_cylinder(&m->cyl[i], light_ray, &light_hit);
	}

	double other_hit_dist;
	double light_rayhit_dist;

	other_hit_dist = dist(light_ray.pos, at(light_ray, light_hit.t));
	light_rayhit_dist = dist(light_ray.pos, *hitpoint);
	// print_hit(light_hit);
	// printf("d(other_hit, light): %f\nd(orig_hit, light): %f\n", other_hit_dist, light_rayhit_dist);
	if (other_hit_dist < light_rayhit_dist)
	{
		in_shadow = true;
	}
	else
	{
		in_shadow = false;
	}
	return (in_shadow);
}

bool	is_shaded(t_mrt *m, t_hit *h)
{
	t_ray	light;

	light = mk_ray(*m->l->pos,
			unit(sub_3d(h->pos,
			*m->l->pos)));
	return (in_shadow(light, m, &h->pos));
}

uint32_t	compute_clr(t_mrt *m, t_hit *h)
{
	double		coeff;
	uint32_t	clr;
	bool		hit_something;
	bool		shaded;
	static int	i;

	hit_something = did_hit(h);
	if (hit_something)
	{
		// print_3d("h->normal: ", h->normal);
		t_3d light_hit = sub_3d(
					*m->l->pos,
					h->pos);
		// print_3d("LP", light_hit);
		shaded = is_shaded(m, h);
		if (false)
		{
			clr = scattered_reflection(m, h->clr, h->from_plane, 0.0);
		}
		else
		{
			coeff = dot( // should that be + or - ?
				unit(light_hit),
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
	{
		clr = rgb(0, 0, 0);
		// printf("didn't hit.\n");
	}
	return (clr);
}

int	trace_ray(t_ray r, t_mrt *m)
{
	uint32_t clr;
	t_hit	h;
	int		i;
	
	h = (t_hit){(t_3d){0, 0, 0},
				(t_3d){0, 0, 0}, false, 1e6, (t_clr){0, 0, 0, 0}};
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
