/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_items_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:05:57 by mhedtman          #+#    #+#             */
/*   Updated: 2023/01/25 15:55:04 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	parse_rgb(char *s, t_clr *clr)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	rgb = ft_split(s, ',');
	if (strslen(rgb) != 3)
		return (free_strs(rgb), false);
	if (ft_parse_int_range(rgb[0], &r, 0, 255) == false)
		return (free_strs(rgb), false);
	if (ft_parse_int_range(rgb[1], &g, 0, 255) == false)
		return (free_strs(rgb), false);
	if (ft_parse_int_range(rgb[2], &b, 0, 255) == false)
		return (free_strs(rgb), false);
	*clr = (t_clr){(uint8_t)r, (uint8_t)g, (uint8_t)b, (uint8_t)0};
	free_strs(rgb);
	return (true);
}

bool	parse_point(t_lst *save_lst, char *s, t_3d **p)
{
	char	**xyz;
	double	x;
	double	y;
	double	z;

	xyz = ft_split(s, ',');
	if (strslen(xyz) != 3)
		return (free_strs(xyz), false);
	if (parse_double(xyz[0], &x) == false)
		return (free_strs(xyz), false);
	if (parse_double(xyz[1], &y) == false)
		return (free_strs(xyz), false);
	if (parse_double(xyz[2], &z) == false)
		return (free_strs(xyz), false);
	*p = mk_3d(save_lst, x, y, z);
	free_strs(xyz);
	return (true);
}

bool	parse_normalized(t_lst *save_lst, char *s, t_3d **p)
{
	char	**xyz;
	double	x;
	double	y;
	double	z;

	xyz = ft_split(s, ',');
	if (strslen(xyz) != 3)
		return (free_strs(xyz), false);
	if (parse_double_range(xyz[0], &x, -1, 1) == false)
		return (free_strs(xyz), false);
	if (parse_double_range(xyz[1], &y, -1, 1) == false)
		return (free_strs(xyz), false);
	if (parse_double_range(xyz[2], &z, -1, 1) == false)
		return (free_strs(xyz), false);
	*p = mk_3d(save_lst, x, y, z);
	free_strs(xyz);
	return (true);
}

bool	parse_ambient(t_mrt *m, char **line)
{
	double	ratio;
	t_clr	clr;

	if (!s_iseq(line[0], "A"))
		return (false);
	if (parse_double_range(line[1], &ratio, 0, 1) == false)
		return (false);
	if (parse_rgb(line[2], &clr) == false)
		return (false);
	m->amb = mk_amb(ratio, &clr);
	return (true);
}
