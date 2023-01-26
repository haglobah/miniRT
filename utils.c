/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:13:53 by bhagenlo          #+#    #+#             */
/*   Updated: 2023/01/26 13:09:58 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_free(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
	else
	{
		// ft_printf("%s: freeing a NULL pointer/a pointer twice.\n");
	}
}

int	s_isneq(char *s1, char *s2, int n)
{
	if (!s1)
	{
		ft_printf("There is no token.\n");
		return (0);
	}
	return (!ft_strncmp(s1, s2, n));
}

int	s_iseq(char *s1, char *s2)
{
	return (!ft_strcmp(s1, s2));
}

int	strslen(char **strs)
{
	int	i;

	i = -1;
	if (strs == NULL)
		return (0);
	while (strs[++i] != NULL)
		;
	return (i);
}

int	free_strs(char **sp)
{
	int	i;

	i = -1;
	while (sp[++i] != NULL)
	{
		ft_free(sp[i]);
	}
	ft_free(sp);
	return (0);
}

void	printnstrs(char **slist)
{
	int	i;

	i = -1;
	while (slist[++i])
	{
		ft_printf("%i: %s\n", i, slist[i]);
	}
}

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
		ft_printf("%s ", slist[i]);
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