/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(char const *s, char c)
{
	int	state;
	int	wcount;

	state = 0;
	wcount = 0;
	while (*s != '\0')
	{
		if (*s != c && state == 0)
		{
			state = 1;
			wcount++;
		}
		else if (*s == c)
			state = 0;
		s++;
	}
	return (wcount);
}

static char	*extract_word(char const *s, char c)
{
	int		len;
	char	*word;
	int		i;

	len = 0;
	while (s[len] != c && s[len] != '\0')
		len++;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (word == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static char const	*next_word_start(char const *s, char c)
{
	while (*s != c && *s != '\0')
		s++;
	while (*s == c && *s != '\0')
		s++;
	return (s);
}

static void	free_words(char **words, int word_ind)
{
	while (word_ind >= 0)
	{
		free(words[word_ind]);
		word_ind--;
	}
	free(words);
}

char	**ft_split(char const *s, char c)
{
	int		word_ind;
	char	**words;
	int		wc;

	wc = word_count(s, c);
	words = malloc(sizeof(char *) * (wc + 1));
	if (words == NULL)
		return (NULL);
	word_ind = 0;
	if (*s == c)
		s = next_word_start(s, c);
	while (*s != '\0')
	{
		words[word_ind] = extract_word(s, c);
		if (words[word_ind] == NULL)
			return (free_words(words, word_ind - 1), NULL);
		s = next_word_start(s, c);
		word_ind++;
	}
	words[word_ind] = NULL;
	return (words);
}
