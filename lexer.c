/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:56:20 by bhagenlo          #+#    #+#             */
/*   Updated: 2023/01/11 13:33:12 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	open_file(char *infile, int *fd)
{
	*fd = open(infile, O_RDONLY);
	return (*fd >= 0);
}

// t_mrt	*parse_line(char *line)
// {
// 	(void)line;
// 	return (NULL);
// }

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
	free_strs(lines);
	return (sens);
}

char	***lex(int argc, char **argv)
{
	int		fd;
	char	*file;
	char	*tmp;

	if (argc != 2 || !open_file(argv[1], &fd))
		return (NULL);
	tmp = get_next_line(fd);
	file = NULL;
	while (tmp)
	{
		if (!file)
		{
			file = ft_strdup(tmp);
			free(tmp);
		}
		else
		{
			file = ft_strjoin(file, tmp);
			free(tmp);
		}
		tmp = get_next_line(fd);
	}
	return (file_to_sens(file));
}
