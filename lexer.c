/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:56:20 by bhagenlo          #+#    #+#             */
/*   Updated: 2023/02/01 09:38:34 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	open_file(char *infile, int *fd)
{
	*fd = open(infile, O_RDONLY);
	return (*fd >= 0);
}

char	***file_to_sens(char *file)
{
	int		i;
	char	**lines;
	char	***sens;

	if (!file)
		return (NULL);
	lines = ft_split(file, '\n');
	sens = ft_calloc(strslen(lines) + 1, sizeof(char **));
	i = -1;
	while (lines[++i])
	{
		sens[i] = ft_split(lines[i], ' ');
	}
	free(file);
	free_strs(lines);
	return (sens);
}

char	*get_first_line(char *tmp)
{
	char	*file;

	file = ft_strdup(tmp);
	free(tmp);
	return (file);
}

char	***lex(int argc, char **argv)
{
	int		fd;
	char	*file;
	char	*tmp;
	char	*tmp_two;

	if (argc != 2 || !open_file(argv[1], &fd))
		return (NULL);
	tmp = get_next_line(fd);
	file = NULL;
	while (tmp)
	{
		if (!file)
			file = get_first_line(tmp);
		else
		{
			tmp_two = file;
			file = ft_strjoin(file, tmp);
			free(tmp_two);
			free(tmp);
		}
		tmp = get_next_line(fd);
	}
	return (file_to_sens(file));
}
