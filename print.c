/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 12:34:26 by bhagenlo          #+#    #+#             */
/*   Updated: 2023/02/01 15:23:25 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// void	print_3d(char *s, t_3d v)
// {
// 	printf("%s: (%.1f %.1f %.1f)\n", s, v.x, v.y, v.z);
// }

// void	print_ray(char *s, t_ray v)
// {
// 	printf("%s DIR: (%.1f %.1f %.1f)\n", s, v.dir.x, v.dir.y, v.dir.z);
// 	printf("%s POS: (%.1f %.1f %.1f)\n", s, v.pos.x, v.pos.y, v.pos.z);
// }

// void	print_amb(t_ambient *amb)
// {
// 	printf("[A]:\n  Range: %.1f\n", amb->ratio);
// 	printf("  ");
// 	print_clr(amb->color);
// }

// void	print_cam(t_cam *cam)
// {
// 	printf("[C]:\n");
// 	print_3d("  POS: ", *cam->pos);
// 	print_3d("  DIR: ", *cam->dir);
// 	printf("  FOV: %.1f\n", cam->fov);
// }

// void	print_l(t_light *l)
// {
// 	printf("[L]:\n");
// 	print_3d("  POS: ", *l->pos);
// 	printf("  Range: %.1f\n", l->brightness);
// 	printf("  ");
// 	print_clr(l->color);
// }

// void	print_sp(t_sphere *s)
// {
// 	if (s->pos == NULL)
// 		return ;
// 	printf("[S]:\n");
// 	print_3d("  POS: ", *s->pos);
// 	printf("  Diameter: %.1f\n", s->diameter);
// 	printf("  ");
// 	print_clr(s->color);
// }

// void	print_pl(t_plane *p)
// {
// 	if (p->pos == NULL)
// 		return ;
// 	printf("[P]:\n");
// 	print_3d("  POS: ", *p->pos);
// 	print_3d("  NORMAL: ", *p->normal);
// 	printf("  ");
// 	print_clr(p->color);
// }

// void	print_cyl(t_cyl *c)
// {
// 	if (c->pos == NULL)
// 		return ;
// 	printf("[CYL]:\n");
// 	print_3d("  POS: ", *c->pos);
// 	print_3d("  NORMAL: ", *c->axis);
// 	printf("  DIAMETER: %.1f\n  HEIGHT: %.1f\n", c->diameter, c->height);
// 	printf("  ");
// 	print_clr(c->color);
// }

// void	print_mrt(t_mrt *m)
// {
// 	int	i;

// 	i = -1;
// 	if (m->amb)
// 		print_amb(m->amb);
// 	if (m->cam)
// 		print_cam(m->cam);
// 	if (m->l)
// 		print_l(m->l);
// 	if (m->sp)
// 		while (++i < m->sp_count)
// 			print_sp(m->sp + i);
// 	i = -1;
// 	if (m->pl)
// 		while (++i < m->pl_count)
// 			print_pl(m->pl + i);
// 	i = -1;
// 	if (m->cyl)
// 		while (++i < m->cyl_count)
// 			print_cyl(m->cyl + i);
// }

// void	print_camera(t_camera *c)
// {
// 	print_3d("pos", *c->pos);
// 	print_3d("dir", *c->dir);
// 	print_3d("vup", *c->vup);
// 	print_3d("u", c->u);
// 	print_3d("v", c->v);
// 	print_3d("horizontal", c->horizontal);
// 	print_3d("vertical", c->vertical);
// 	print_3d("llc", c->llc);
// }

// void	print_hit(t_hit h)
// {
// 	// print_3d("  pos", h.pos);
// 	// print_3d("  normal", h.normal);
// 	printf("  t: %f\n", h.t);
// 	printf("  ");
// 	print_clr(h.clr);
// }

// void	print_plane(t_coor_plane pl)
// {
// 	printf("  a: %f\n", pl.a);
// 	printf("  b: %f\n", pl.b);
// 	printf("  c: %f\n", pl.c);
// 	printf("  d: %f\n\n", pl.d);
// }