/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_items_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:11:05 by mhedtman          #+#    #+#             */
/*   Updated: 2023/02/01 12:15:48 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	check_one_strslen(char **parts, double *d, double value, double factor)
{
	if (strslen(parts) == 1)
	{
		*d = factor * value;
		free_strs(parts);
		return (true);
	}
	return (false);
}

void	get_negative(char **parts, double *factor)
{
	if (parts[0][0] == '-')
	{
		parts[0] = ft_strtrim(parts[0], "-");
		*factor = -1;
	}
	else
		*factor = 1;
}

bool	parse_double(char *s, double *d)
{
	char	**parts;
	int		i;
	int		pre_i;
	double	value;
	double	factor;

	parts = ft_split(s, '.');
	if (strslen(parts) > 2)
		return (free_strs(parts), false);
	get_negative(parts, &factor);
	if (ft_parse_int(parts[0], &pre_i) == false)
		return (free_strs(parts), false);
	value = (double)pre_i;
	if (check_one_strslen(parts, d, value, factor))
		return (true);
	i = 0;
	while (parts[1][i] >= '0' && parts[1][i] <= '9')
	{
		value = value * 10.0 + (parts[1][i] - '0');
		factor = factor / 10.0;
		i++;
	}
	*d = value * factor;
	free_strs(parts);
	return (true);
}

bool	parse_double_range(char *s, double *d, double lo, double hi)
{
	parse_double(s, d);
	if (*d <= hi && *d >= lo)
		return (true);
	else
	{
		printf("Error\n");
		printf("'%s' is not in the specified range [%.1f, %.1f]\n", s, lo, hi);
		return (false);
	}
}

bool	ft_parse_int_range(char *s, int *n, int lo, int hi)
{
	ft_parse_int(s, n);
	if (*n <= hi && *n >= lo)
		return (true);
	else
	{
		printf("Error\n");
		printf("'%s' is not in the specified range [%i, %i]\n", s, lo, hi);
		return (false);
	}
}
