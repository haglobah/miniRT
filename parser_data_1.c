/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_data_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 12:20:31 by mhedtman          #+#    #+#             */
/*   Updated: 2023/02/01 12:21:00 by mhedtman         ###   ########.fr       */
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
