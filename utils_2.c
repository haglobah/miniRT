/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 09:47:13 by mhedtman          #+#    #+#             */
/*   Updated: 2023/02/01 13:29:50 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	printstrs_n(char **slist)
{
	int	i;

	i = -1;
	while (slist[++i])
	{
		ft_printf("'%s'\n", slist[i]);
	}
}

void	printstrs(char **slist)
{
	int	i;

	i = -1;
	while (slist[++i])
	{
		ft_printf("%s\n", slist[i]);
	}
}

void	printsens(char ***sentence_list)
{
	int	i;

	i = -1;
	while (sentence_list[++i])
	{
		printstrs(sentence_list[i]);
	}
}

void	free_mrt(t_mrt *m)
{
	free_from_list(m->save_lst);
	free(m->sp);
	free(m->pl);
	free(m->cyl);
	free(m->amb);
	free(m->cam);
	free(m->l);
	free(m);
	return ;
}

void	free_opt(t_options *o)
{
	free_mrt(o->m);
	free(o->camera);
	free(o);
}
