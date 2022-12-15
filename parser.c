// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   parser.c                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/12/15 12:34:46 by bhagenlo          #+#    #+#             */
// /*   Updated: 2022/12/15 12:36:51 by bhagenlo         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minirt.h"

// t_mrt	*mk_mrt()
// {
// 	t_mrt	*m;

// 	m = ft_calloc(1, sizeof(t_mrt));
// 	m->amb = NULL;
// 	m->l = NULL;
// 	m->cam = NULL;
// 	m->sp = NULL;
// 	m->pl = NULL;
// 	m->cyl = NULL;
// 	return (m);
// }

// bool	parse_double(char *s, double *d)
// {
	
// }

// bool	parse_ambient(t_mrt *m, char **line)
// {
// 	double	ratio;
// 	t_clr	clr;
// 	if (!s_is_eq(line[0], "A"))
// 		return (false);
// 	if (parse_double(line[1], &ratio) == false)
// 		return (false);
// 	if (parse_rgb(line[2], &clr) == false)
// 		return (false);
// }

// bool	parse_line(t_mrt *m, char **line)
// {
// 	if (parse_ambient(m, line) == true)
// 		return (true);
// 	else if (parse_camera(m, line) == true)
// 		return (true);
// 	else if (parse_light(m, line) == true)
// 		return (true);
// 	else if (parse_sphere(m, line) == true)
// 		return (true);
// 	else if (parse_plane(m, line) == true)
// 		return (true);
// 	else if (parse_cylinder(m, line) == true)
// 		return (true);
// 	return (false);
// }

// t_mrt	*parse(char ***sens)
// {
// 	t_mrt	*m;
// 	int		i;

// 	m = mk_mrt(sens);
// 	if (m == NULL)
// 		return (NULL);
// 	i = -1;
// 	while (sens[++i])
// 	{
// 		parse_line(m, sens[i]);
// 	}
// 	//free_sens();
// 	return (m);
// }