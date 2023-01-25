/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:15:27 by mhedtman          #+#    #+#             */
/*   Updated: 2023/01/25 16:28:19 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "objects.h"

typedef struct s_tmp_cyl
{
	t_3d	*pos;
	t_3d	*axis;
	double	diameter;
	double	height;
	t_clr	clr;

}	t_tmp_cyl;

bool	parse_cylinder(t_mrt *m, char **line);
bool	parse_plane(t_mrt *m, char **line);
bool	parse_sphere(t_mrt *m, char **line);
bool	parse_light(t_mrt *m, char **line);
bool	parse_camera(t_mrt *m, char **line);

bool	parse_rgb(char *s, t_clr *clr);
bool	parse_point(t_lst *save_lst, char *s, t_3d **p);
bool	parse_normalized(t_lst *save_lst, char *s, t_3d **p);
bool	parse_ambient(t_mrt *m, char **line);

bool	check_one_strslen(char **parts, double *d, double value);
bool	parse_double(char *s, double *d);
bool	parse_double_range(char *s, double *d, double lo, double hi);
bool	ft_parse_int_range(char *s, int *n, int lo, int hi);

void	count_bodies(int *bodies, char ***sens);
void	parse_error(char **line);
void	free_sens(char ***sens);
t_mrt	*mk_mrt(int *bodies);

#endif