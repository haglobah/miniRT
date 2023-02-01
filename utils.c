/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:13:53 by bhagenlo          #+#    #+#             */
/*   Updated: 2023/02/01 09:48:33 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
		free(sp[i]);
	}
	free(sp);
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
