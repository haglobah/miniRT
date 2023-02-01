/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_data_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 12:20:21 by mhedtman          #+#    #+#             */
/*   Updated: 2023/02/01 12:21:57 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
