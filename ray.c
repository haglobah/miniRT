/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:25:40 by bhagenlo          #+#    #+#             */
/*   Updated: 2023/01/18 17:57:06 by bhagenlo         ###   ########.fr       */
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

uint32_t	shade(t_mrt *m, t_clr clr, double coeff)
{
	t_clr	*res;
	
	res = sum_clr(m->save_lst,
		*mul_clr(m->save_lst, m->amb->ratio, m->amb->color),
		*mul_clr(m->save_lst, m->l->brightness * d_max(coeff, 0.0),
				 clr));
	// res = mul_clr(m->l->brightness * d_max(coeff, 0.0),
	// 			 clr);
	return (rgb(res->r, res->g, res->b));
}

uint32_t	compute_clr(t_mrt *m, t_hit *h)
{
	double		coeff;
	uint32_t	clr;
	bool		hit_something;
	static int	i;

	hit_something = did_hit(h);
	if (hit_something)
	{
		// print3d("h->normal: ", h->normal);
		t_3d light_hit = *mk_unit(m->save_lst, *sub_3d(m->save_lst,
					*m->l->pos,
					h->pos));
		// print3d("LP", light_hit);
		coeff = -dot(light_hit, // should that be + or - ?
			*mk_unit(m->save_lst, h->normal));
		// printf("coeff: %f\n", coeff);
		// print_clr(h->clr);
		clr = shade(m, h->clr, coeff);
		// printf("hit: i = %i\n", i);
		// print_hit(*h);
		i++;
	}
	else
	{
		clr = rgb(0, 0, 0);
		// printf("didn't hit.\n");
	}
	return (clr);
}

int	trace_ray(t_ray *r, t_mrt *m)
{
	uint32_t clr;
	double	t;
	t_hit	h;
	int		i;
	
	h = (t_hit){(t_3d){0, 0, 0},
				(t_3d){0, 0, 0}, 1e6, (t_clr){0, 0, 0}};
	i = -1;
	while (++i < m->sp_count)
	{
		hit_sphere(m, &m->sp[i], r, &h);
	}
	i = -1;
	while (++i < m->pl_count)
	{
		hit_plane(m, &m->pl[i], r, &h);
	}
	// i = -1;
	// while (++i < m->cyl_count)
	// {
	// 	hit_cylinder(&m->cyl[i], r, &h);
	// }
	clr = compute_clr(m, &h);
	return (clr);
}
