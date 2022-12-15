/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:13:53 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/12/15 11:59:39 by bhagenlo         ###   ########.fr       */
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

void	free_all(t_mrt *m)
{
	(void)m;
	return ;
}