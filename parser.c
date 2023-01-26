/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 12:34:46 by bhagenlo          #+#    #+#             */
/*   Updated: 2023/01/26 13:11:03 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	parse_comment(char **line)
{
	if (!s_iseq(line[0], "#"))
		return (false);
	return (true);
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
	else if (parse_comment(line) == true)
		return (true);
	printf("Error\n");
	return (parse_error(line), false);
}

t_mrt	*parse(char ***sens)
{
	int		bodies[3];
	t_mrt	*m;
	int		i;

	count_bodies(bodies, sens);
	m = mk_mrt(bodies);
	if (m == NULL)
		return (NULL);
	i = -1;
	while (sens[++i])
	{
		if (!parse_line(m, sens[i]))
		{
			free_mrt(m);
			free_sens(sens);
			return (NULL);
		}
	}
	free_sens(sens);
	return (m);
}
