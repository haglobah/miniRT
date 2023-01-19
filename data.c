/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:12:49 by bhagenlo          #+#    #+#             */
/*   Updated: 2023/01/19 13:49:07 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ambient	*mk_amb(t_d ratio, t_clr *clr)
{
	t_ambient	*ambient;

	ambient = (t_ambient *)ft_calloc(1, sizeof(t_ambient));
	ambient->ratio = ratio;
	ambient->color = *clr;
	return (ambient);
}

t_cam	*mk_cam(t_3d *pos, t_3d *dir, t_d fov)
{
	t_cam	*cam;

	cam = (t_cam *)ft_calloc(1, sizeof(t_cam));
	cam->pos = pos;
	cam->dir = dir;
	cam->fov = fov;
	return (cam);
}

t_light	*mk_l(t_3d *pos, t_clr *clr, t_d brightness)
{
	t_light	*light;

	light = (t_light *)ft_calloc(1, sizeof(t_light));
	light->pos = pos;
	light->color = *clr;
	light->brightness = brightness;
	return (light);
}

void	fill_sp(t_3d *pos, t_d diameter, t_clr *clr, t_sphere *sphere)
{
	sphere->pos = pos;
	sphere->color = *clr;
	sphere->diameter = diameter;
}

void	fill_pl(t_3d *pos, t_3d *normal, t_clr *clr, t_plane *plane)
{
	plane->pos = pos;
	plane->normal = normal;
	plane->color = *clr;
}

void	fill_cyl(t_3d *pos, t_3d *normal, t_d diameter, t_d height, t_clr *clr, t_cyl *cyl)
{
	cyl->pos = pos;
	cyl->normal = normal;
	cyl->diameter = diameter;
	cyl->height = height;
	cyl->color = *clr;
}

// void	print_amb(t_ambient *amb)
// {
// 	printf("[A]:\n  Range: %f\n", amb->ratio);
// 	printf("  ");
// 	print_clr(amb->color);
// }

// void	print_cam(t_cam *cam)
// {
// 	printf("[C]:\n");
// 	print3d("  POS: ", *cam->pos);
// 	print3d("  DIR: ", *cam->dir);
// 	printf("  FOV: %f\n", cam->fov);
// }

// void	print_l(t_light *l)
// {
// 	printf("[L]:\n");
// 	print3d("  POS: ", *l->pos);
// 	printf("  Range: %f\n", l->brightness);
// 	printf("  ");
// 	print_clr(l->color);
// }

// void	print_sp(t_sphere *s)
// {
// 	printf("[S]:\n");
// 	print3d("  POS: ", *s->pos);
// 	printf("  Diameter: %f\n", s->diameter);
// 	printf("  ");
// 	print_clr(s->color);
// }

// void	print_pl(t_plane *p)
// {
// 	printf("[P]:\n");
// 	print3d("  POS: ", *p->pos);
// 	print3d("  NORMAL: ", *p->normal);
// 	printf("  ");
// 	print_clr(p->color);
// }

// void	print_cyl(t_cyl *c)
// {
// 	printf("[CYL]:\n");
// 	print3d("  POS: ", *c->pos);
// 	print3d("  NORMAL: ", *c->normal);
// 	printf("  DIAMETER: %f\n  HEIGHT: %f\n", c->diameter, c->height);
// 	printf("  ");
// 	print_clr(c->color);
// }

// void	print_mrt(t_mrt *m)
// {
// 	if (m->amb)
// 		print_amb(m->amb);
// 	if (m->cam)
// 		print_cam(m->cam);
// 	if (m->l)
// 		print_l(m->l);
// 	if (m->sp)
// 		print_sp(m->sp);
// 	if (m->pl)
// 		print_pl(m->pl);
// 	if (m->cyl)
// 		print_cyl(m->cyl);
// }