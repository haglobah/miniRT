/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_items_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:05:57 by mhedtman          #+#    #+#             */
/*   Updated: 2023/01/25 15:53:10 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	parse_camera(t_mrt *m, char **line)
{
	t_3d	*pos;
	t_3d	*dir;
	double	fov;

	if (!s_iseq(line[0], "C"))
		return (false);
	if (parse_point(m->save_lst, line[1], &pos) == false)
		return (false);
	if (parse_normalized(m->save_lst, line[2], &dir) == false)
		return (false);
	if (parse_double_range(line[3], &fov, 0, 180) == false)
		return (false);
	m->cam = mk_cam(pos, dir, fov);
	return (true);
}

bool	parse_light(t_mrt *m, char **line)
{
	t_3d	*pos;
	t_clr	clr;
	double	brightness;

	if (!s_iseq(line[0], "L"))
		return (false);
	if (parse_point(m->save_lst, line[1], &pos) == false)
		return (false);
	if (parse_double_range(line[2], &brightness, 0, 1) == false)
		return (false);
	if (parse_rgb(line[3], &clr) == false)
		return (false);
	m->l = mk_l(pos, &clr, brightness);
	return (true);
}

bool	parse_sphere(t_mrt *m, char **line)
{
	t_3d		*pos;
	double		diameter;
	t_clr		clr;
	static int	i;

	if (!s_iseq(line[0], "sp"))
		return (false);
	if (parse_point(m->save_lst, line[1], &pos) == false)
		return (false);
	if (parse_double_range(line[2], &diameter, 0, 1e10) == false)
		return (false);
	if (parse_rgb(line[3], &clr) == false)
		return (false);
	fill_sp(pos, diameter, &clr, &m->sp[i++]);
	return (true);
}

bool	parse_plane(t_mrt *m, char **line)
{
	t_3d		*pos;
	t_3d		*normal;
	t_clr		clr;
	static int	i;

	if (!s_iseq(line[0], "pl"))
		return (false);
	if (parse_point(m->save_lst, line[1], &pos) == false)
		return (false);
	if (parse_normalized(m->save_lst, line[2], &normal) == false)
		return (false);
	if (parse_rgb(line[3], &clr) == false)
		return (false);
	fill_pl(pos, normal, &clr, &m->pl[i++]);
	return (true);
}

bool	parse_cylinder(t_mrt *m, char **line)
{
	t_tmp_cyl	tmp_cyl;
	static int	i;

	if (!s_iseq(line[0], "cy"))
		return (false);
	if (parse_point(m->save_lst, line[1], &tmp_cyl.pos) == false)
		return (false);
	if (parse_normalized(m->save_lst, line[2], &tmp_cyl.axis) == false)
		return (false);
	if (parse_double_range(line[3], &tmp_cyl.diameter, 0, 1e10) == false)
		return (false);
	if (parse_double_range(line[4], &tmp_cyl.height, 0, 1e10) == false)
		return (false);
	if (parse_rgb(line[5], &tmp_cyl.clr) == false)
		return (false);
	fill_cyl(tmp_cyl, &m->cyl[i++]);
	return (true);
}
