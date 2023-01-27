/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:12:49 by bhagenlo          #+#    #+#             */
/*   Updated: 2023/01/27 12:34:48 by bhagenlo         ###   ########.fr       */
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

void	fill_cyl(t_tmp_cyl tmp_cyl, t_cyl *cyl)
{
	cyl->pos = tmp_cyl.pos;
	cyl->axis = tmp_cyl.axis;
	cyl->diameter = tmp_cyl.diameter;
	cyl->height = tmp_cyl.height;
	cyl->color = tmp_cyl.clr;
}
