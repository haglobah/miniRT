/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 12:34:46 by bhagenlo          #+#    #+#             */
/*   Updated: 2023/01/11 16:06:37 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_mrt	*mk_mrt()
{
	t_mrt	*m;

	m = ft_calloc(1, sizeof(t_mrt));
	m->amb = NULL;
	m->l = NULL;
	m->cam = NULL;
	m->sp = NULL;
	m->pl = NULL;
	m->cyl = NULL;
	return (m);
}

bool	parse_double(char *s, double *d)
{
	char	**parts;
	int		i;
	int		pre_i;
	double  value;
	double	factor;

	parts = ft_split(s, '.');
	// printns(parts);
	if (strslen(parts) > 2)
		return (ft_free(parts), false);
	if (ft_parse_int(parts[0], &pre_i) == false)
		return (ft_free(parts), false);
	value = (double)pre_i;
	if (strslen(parts) == 1)
	{
		*d = value;
		return (true);
	}
	factor = 1;
	// printf("value: %f ?= pre_i: %i\n", value, pre_i);
	i = 0;
	while (parts[1][i] >= '0' && parts[1][i] <= '9')
	{
		value = value * 10.0 + (parts[1][i] - '0');
		factor = factor / 10.0;
		// printf("value: %f; factor: %f\n", value, factor);
		i++;
	}
	*d = value * factor;
	return (true);
}

bool	parse_rgb(char *s, t_clr *clr)
{
	char	**rgb;
	int r;
	int g;
	int b;

	rgb = ft_split(s, ',');
	if (strslen(rgb) != 3)
		return (ft_free(rgb), false);
	if (ft_parse_int(rgb[0], &r) == false)
		return (ft_free(rgb), false);
	if (ft_parse_int(rgb[1], &g) == false)
		return (ft_free(rgb), false);
	if (ft_parse_int(rgb[2], &b) == false)
		return (ft_free(rgb), false);
	*clr = (t_clr){(uint8_t)r, (uint8_t)g, (uint8_t)b};
}

bool	parse_point(char *s, t_3d **p)
{
	char	**xyz;
	double x;
	double y;
	double z;

	xyz = ft_split(s, ',');
	// printns(xyz);
	if (strslen(xyz) != 3)
		return (ft_free(xyz), false);
	if (parse_double(xyz[0], &x) == false)
		return (ft_free(xyz), false);
	if (parse_double(xyz[1], &y) == false)
		return (ft_free(xyz), false);
	if (parse_double(xyz[2], &z) == false)
		return (ft_free(xyz), false);
	*p = mk_3d(x, y ,z);
	return (true);
}

bool	parse_ambient(t_mrt *m, char **line)
{
	double	ratio;
	t_clr	clr;

	if (!s_iseq(line[0], "A"))
		return (false);
	if (parse_double(line[1], &ratio) == false)
		return (false);
	if (parse_rgb(line[2], &clr) == false)
		return (false);
	m->amb = mk_amb(ratio, &clr);
	// print_clr(clr);
	// printf("%s as double: %f\n", line[1], ratio);
}

bool	parse_camera(t_mrt *m, char **line)
{
	t_3d	*pos;
	t_3d	*dir;
	double	fov;

	if (!s_iseq(line[0], "C"))
		return (false);
	if (parse_point(line[1], &pos) == false)
		return (false);
	if (parse_point(line[2], &dir) == false)
		return (false);
	if (parse_double(line[3], &fov) == false)
		return (false);
	m->cam = mk_cam(pos, dir, fov);
	// print_clr(clr);
	// printf("%s as double: %f\n", line[1], ratio);
}

bool	parse_light(t_mrt *m, char **line)
{
	t_3d	*pos;
	t_clr	clr;
	double	brightness;

	if (!s_iseq(line[0], "L"))
		return (false);
	if (parse_point(line[1], &pos) == false)
		return (false);
	if (parse_double(line[2], &brightness) == false)
		return (false);
	if (parse_rgb(line[3], &clr) == false)
		return (false);
	m->l = mk_l(pos, &clr, brightness);
	// print_clr(clr);
	// printf("%s as double: %f\n", line[1], ratio);
}

bool	parse_sphere(t_mrt *m, char **line)
{
	t_3d	*pos;
	double	diameter;
	t_clr	clr;

	if (!s_iseq(line[0], "sp"))
		return (false);
	if (parse_point(line[1], &pos) == false)
		return (false);
	if (parse_double(line[2], &diameter) == false)
		return (false);
	if (parse_rgb(line[3], &clr) == false)
		return (false);
	m->sp = mk_sp(pos, diameter, &clr);
	// print_clr(clr);
	// printf("%s as double: %f\n", line[1], ratio);
}

bool	parse_plane(t_mrt *m, char **line)
{
	t_3d	*pos;
	t_3d	*normal;
	t_clr	clr;

	if (!s_iseq(line[0], "sp"))
		return (false);
	if (parse_point(line[1], &pos) == false)
		return (false);
	if (parse_point(line[2], &normal) == false)
		return (false);
	if (parse_rgb(line[3], &clr) == false)
		return (false);
	m->pl = mk_pl(pos, normal, &clr);
	// print_clr(clr);
	// printf("%s as double: %f\n", line[1], ratio);
}

bool	parse_cylinder(t_mrt *m, char **line)
{
	t_3d	*pos;
	t_3d	*normal;
	double	diameter;
	double	height;
	t_clr	clr;

	if (!s_iseq(line[0], "sp"))
		return (false);
	if (parse_point(line[1], &pos) == false)
		return (false);
	if (parse_point(line[2], &normal) == false)
		return (false);
	if (parse_double(line[3], &diameter) == false)
		return (false);
	if (parse_double(line[4], &height) == false)
		return (false);
	if (parse_rgb(line[5], &clr) == false)
		return (false);
	m->cyl = mk_cyl(pos, normal, diameter, height, &clr);
	// print_clr(clr);
	// printf("%s as double: %f\n", line[1], ratio);
}

bool	parse_line(t_mrt *m, char **line)
{
	if (parse_ambient(m, line) == true)
		return (true);
	else if (parse_camera(m, line) == true)
		return (true);
	else if (parse_light(m, line) == true)
		return (true);
	else if (parse_sphere(m, line) == true)
		return (true);
	else if (parse_plane(m, line) == true)
		return (true);
	else if (parse_cylinder(m, line) == true)
		return (true);
	return (false);
}

t_mrt	*parse(char ***sens)
{
	t_mrt	*m;
	int		i;

	m = mk_mrt();
	if (m == NULL)
		return (NULL);
	i = -1;
	while (sens[++i])
	{
		parse_line(m, sens[i]);
		// printf("here\n");
	}
	//free_sens();
	print_mrt(m);
	return (m);
}
