/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:12:49 by bhagenlo          #+#    #+#             */
/*   Updated: 2023/01/11 14:41:17 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ambient	*mk_amb(t_d ratio, t_clr *clr)
{
	t_ambient	*ambient;

	ambient = (t_ambient *)ft_calloc(1, sizeof(t_ambient));
	ambient->range = ratio;
	ambient->color = *clr;
	return (ambient);
}

t_cam		*mk_cam(t_3d *pos, t_3d *dir, t_d fov)
{
	t_cam	*cam;

	cam = (t_cam *)ft_calloc(1, sizeof(t_cam));
	cam->pos = pos;
	cam->dir = dir;
	cam->fov = fov;
	return (cam);
}

t_light		*mk_l(t_3d *pos, t_clr *clr, t_d brightness)
{
	t_light	*light;

	light = (t_light *)ft_calloc(1, sizeof(t_light));
	light->pos = pos;
	light->color = *clr;
	light->range = brightness;
	return (light);
}

t_sphere	*mk_sp(t_3d *pos, t_d diameter, t_clr *clr)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)ft_calloc(1, sizeof(t_sphere));
	sphere->pos = pos;
	sphere->color = *clr;
	sphere->diameter = diameter;
	return (sphere);
}

t_plane		*mk_pl(t_3d *pos, t_3d *normal, t_clr *clr)
{
	t_plane	*plane;

	plane = (t_plane *)ft_calloc(1, sizeof(t_plane));
	plane->pos = pos;
	plane->normal = normal;
	plane->color = *clr;
	return (plane);
}

t_cyl		*mk_cyl(t_3d *pos, t_3d *normal, t_d diameter, t_d height, t_clr *clr)
{
	t_cyl	*cyl;

	cyl = (t_cyl *)ft_calloc(1, sizeof(t_cyl));
	cyl->pos = pos;
	cyl->normal = normal;
	cyl->diameter = diameter;
	cyl->height = height;
	cyl->color = *clr;
	return (cyl);
}
