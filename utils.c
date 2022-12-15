/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:13:53 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/12/15 12:28:57 by bhagenlo         ###   ########.fr       */
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

void	printns(char **slist)
{
	int	i;

	i = -1;
	while (slist[++i])
	{
		ft_printf("%i: %s\n", i, slist[i]);
	}
}

void	prints(char **slist)
{
	int	i;

	i = -1;
	while (slist[++i])
	{
		ft_printf("'%s'\n", slist[i]);
	}
}

void	printsens(char ***sentence_list)
{
	int	i;

	i = -1;
	while (sentence_list[++i])
	{
		prints(sentence_list[i]);
	}
}

void	free_all(t_mrt *m)
{
	(void)m;
	return ;
}