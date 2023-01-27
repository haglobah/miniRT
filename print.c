/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 12:34:26 by bhagenlo          #+#    #+#             */
/*   Updated: 2023/01/27 13:07:36 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print3d(char *s, t_3d v)
{
	printf("%s: (%.1f %.1f %.1f)\n", s, v.x, v.y, v.z);
}

void	printray(char *s, t_ray v)
{
	printf("%s DIR: (%.1f %.1f %.1f)\n", s, v.dir.x, v.dir.y, v.dir.z);
	printf("%s POS: (%.1f %.1f %.1f)\n", s, v.pos.x, v.pos.y, v.pos.z);
}

void	print_amb(t_ambient *amb)
{
	printf("[A]:\n  Range: %.1f\n", amb->ratio);
	printf("  ");
	print_clr(amb->color);
}

void	print_cam(t_cam *cam)
{
	printf("[C]:\n");
	print3d("  POS: ", *cam->pos);
	print3d("  DIR: ", *cam->dir);
	printf("  FOV: %.1f\n", cam->fov);
}

void	print_l(t_light *l)
{
	printf("[L]:\n");
	print3d("  POS: ", *l->pos);
	printf("  Range: %.1f\n", l->brightness);
	printf("  ");
	print_clr(l->color);
}

void	print_sp(t_sphere *s)
{
	if (s->pos == NULL)
		return ;
	printf("[S]:\n");
	print3d("  POS: ", *s->pos);
	printf("  Diameter: %.1f\n", s->diameter);
	printf("  ");
	print_clr(s->color);
}

void	print_pl(t_plane *p)
{
	if (p->pos == NULL)
		return ;
	printf("[P]:\n");
	print3d("  POS: ", *p->pos);
	print3d("  NORMAL: ", *p->normal);
	printf("  ");
	print_clr(p->color);
}

void	print_cyl(t_cyl *c)
{
	if (c->pos == NULL)
		return ;
	printf("[CYL]:\n");
	print3d("  POS: ", *c->pos);
	print3d("  NORMAL: ", *c->axis);
	printf("  DIAMETER: %.1f\n  HEIGHT: %.1f\n", c->diameter, c->height);
	printf("  ");
	print_clr(c->color);
}

void	print_mrt(t_mrt *m)
{
	int	i;

	i = -1;
	if (m->amb)
		print_amb(m->amb);
	if (m->cam)
		print_cam(m->cam);
	if (m->l)
		print_l(m->l);
	if (m->sp)
		while (++i < m->sp_count)
			print_sp(m->sp + i);
	i = -1;
	if (m->pl)
		while (++i < m->pl_count)
			print_pl(m->pl + i);
	i = -1;
	if (m->cyl)
		while (++i < m->cyl_count)
			print_cyl(m->cyl + i);
}