/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:06:27 by mhedtman          #+#    #+#             */
/*   Updated: 2023/01/25 15:22:35 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_error(char **line)
{
	ft_printf("In this line:\n\n  ");
	printstrs(line);
	ft_printf("\n\n");
}

t_mrt	*mk_mrt(int *bodies)
{
	t_mrt	*m;

	m = ft_calloc(1, sizeof(t_mrt));
	m->amb = NULL;
	m->l = NULL;
	m->cam = NULL;
	m->sp = ft_calloc(bodies[0] + 1, sizeof(t_sphere));
	m->pl = ft_calloc(bodies[1] + 1, sizeof(t_plane));
	m->cyl = ft_calloc(bodies[2] + 1, sizeof(t_cyl));
	m->save_lst = mk_node(NULL, NULL, NULL);
	m->sp_count = bodies[0];
	m->pl_count = bodies[1];
	m->cyl_count = bodies[2];
	return (m);
}

void	free_sens(char ***sens)
{
	int	i;

	i = -1;
	while(sens[++i])
	{
		free_strs(sens[i]);
	}
	free(sens);
}

void	count_bodies(int *bodies, char ***sens)
{
	int	i;

	bodies[0] = 0;
	bodies[1] = 0;
	bodies[2] = 0;
	i = -1;
	while (sens[++i])
	{
		if (s_iseq("sp", sens[i][0]))
			bodies[0]++;
		if (s_iseq("pl", sens[i][0]))
			bodies[1]++;
		if (s_iseq("cy", sens[i][0]))
			bodies[2]++;
	}
}