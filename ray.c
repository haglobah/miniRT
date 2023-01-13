/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:25:40 by bhagenlo          #+#    #+#             */
/*   Updated: 2023/01/13 13:50:19 by bhagenlo         ###   ########.fr       */
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
	
	res = sum_clr(
		*mul_clr(m->amb->ratio, m->amb->color),
		*mul_clr(m->l->brightness * d_max(coeff, 0.0),
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

	hit_something = did_hit(h);
	coeff = -dot(*mk_unit(*m->l->pos), h->normal);
	if (hit_something)
		clr = shade(m, h->clr, coeff);
	else
		clr = rgb(0, 0, 0);
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
		hit_sphere(&m->sp[i], r, &h);
	}
	// i = -1;
	// while (++i < m->pl_count)
	// {
	// 	hit_plane(&m->pl[i], r, &h);
	// }
	// i = -1;
	// while (++i < m->cyl_count)
	// {
	// 	hit_cylinder(&m->cyl[i], r, &h);
	// }
	clr = compute_clr(m, &h);
	return (clr);
}
