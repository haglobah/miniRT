/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:25:40 by bhagenlo          #+#    #+#             */
/*   Updated: 2023/01/25 17:05:55 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	mk_ray(t_3d pos, t_3d dir)
{
	t_ray	new;

	new = (t_ray){pos, dir};
	return (new);
}

uint32_t	scattered_reflection(t_mrt *m, t_clr clr, double coeff)
{
	t_clr	res;
	
	res = sum_clr(
		mul_clr(m->amb->ratio, m->amb->color),
		mul_clr(m->l->brightness * d_max(coeff, 0.0),
		clr));
	return (rgb(res.r, res.g, res.b));
}

bool	in_shadow(t_ray r, t_mrt *m, t_3d *hitpoint)
{
	// uint32_t clr;
	// double	t;
	t_hit	h;
	int		i;
	bool	in_shadow;

	h = (t_hit){(t_3d){0, 0, 0},
				(t_3d){0, 0, 0}, 1e6, (t_clr){0, 0, 0, 0}};
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
	// i = -1;
	// while (++i < m->cyl_count)
	// {
	// 	hit_cylinder(&m->cyl[i], r, &h);
	// }
	if (dist(r.pos, at(r, h.t)) < dist(r.pos, *hitpoint))
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
		// print3d("h->normal: ", h->normal);
		t_3d light_hit = sub_3d(
					*m->l->pos,
					h->pos);
		// print3d("LP", light_hit);
		shaded = is_shaded(m, h);
		if (false)
		{
			clr = scattered_reflection(m, h->clr, 0.0);
		}
		else
		{
			coeff = -dot( // should that be + or - ?
				unit(light_hit),
				unit(h->normal));
			clr = scattered_reflection(m, h->clr, coeff);
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
				(t_3d){0, 0, 0}, 1e6, (t_clr){0, 0, 0, 0}};
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
