/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_whitespace_split.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 19:08:29 by bhagenlo          #+#    #+#             */
/*   Updated: 2023/02/01 15:05:30 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	num_words_whitespaces(char const *str)
{
	int	word_count;
	int	was_word;

	word_count = 0;
	was_word = 0;
	while (*str)
	{
		if ((*str == ' ' || *str == '\t') && was_word)
		{
			word_count++;
			was_word = 0;
		}
		else if ((*str != ' ' || *str != '\t') && !was_word)
			was_word = 1;
		str++;
	}
	if (was_word)
		word_count++;
	return (word_count);
}

static int	wordlen_whitespace(char const *str)
{
	int	wlen;

	wlen = 0;
	while (str[wlen] && str[wlen] != ' ' && str[wlen] != '\t')
		wlen++;
	return (wlen);
}

static void	*free_split(char **str, int words_created_so_far)
{
	int	i;

	i = 0;
	while (i < words_created_so_far)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

char	**split_whitespace(char const *s)
{
	char	**res;
	int		words;
	int		chr;
	int		word_count;

	if (!s)
		return (NULL);
	words = num_words_whitespaces(s);
	res = (char **)malloc(sizeof(char *) * (words + 1));
	if (!res)
		return (NULL);
	chr = 0;
	word_count = 0;
	while (word_count < words)
	{
		while (s[chr] && (s[chr] == ' ' || s[chr] == '\t'))
			chr++;
		res[word_count] = ft_substr(s, chr, wordlen_whitespace(s + chr));
		if (!res[word_count])
			return (free_split(res, word_count - 1));
		chr += wordlen_whitespace(s + chr);
		word_count++;
	}
	res[words] = NULL;
	return (res);
}
