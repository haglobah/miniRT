/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:56:20 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/12/14 15:21:41 by bhagenlo         ###   ########.fr       */
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

char	***lex_file(char *file)
{
	int		i;
	char	**lines;
	char	***words;

	if (!file)
		return (NULL);
	lines = ft_split(file, '\n');
	i = -1;
	while (lines[++i])
		continue;		
	words = ft_calloc(i + 1, sizeof(char **));
	i = -1;
	while (lines[++i])
	{
		words[i] = ft_split(lines[i], ' ');
	}
	return (words);
}

char	***read_file_all(int fd)
{
	char	*file;
	char	*tmp;

	tmp = get_next_line(fd);
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
	return (lex_file(file));
}

t_mrt	*parse_file(int argc, char **argv)
{
	int		fd;
	char	***file;
	t_mrt	*parsed_input;

	if (argc != 2 || !open_file(argv[1], &fd))
		return (NULL);
	file = read_file_all(fd);
	int	j = -1;
	while (file[++j])
	{
		int i = -1;
		while (file[j][++i])
			printf("%s ", file[j][i]);
		printf("\n");
	}
	return (NULL);
}