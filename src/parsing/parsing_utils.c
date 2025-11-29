/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esteizag <esteizag@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 18:44:28 by esteizag          #+#    #+#             */
/*   Updated: 2025/11/29 18:44:31 by esteizag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\f' || c == '\v');
}

void	skip_spaces(const char **str)
{
	while (**str && ft_isspace(**str))
		(*str)++;
}

int	is_empty_line(const char *line)
{
	while (*line)
	{
		if (!ft_isspace(*line))
			return (0);
		line++;
	}
	return (1);
}

char	*ft_strtrim_free(char *s1, const char *set)
{
	char	*result;

	result = ft_strtrim(s1, set);
	free(s1);
	return (result);
}

void	parse_error(const char *msg, t_parse_ctx *p)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd((char *)msg, 2);
	ft_putstr_fd("\n", 2);
	if (p->line)
		free(p->line);
	if (p->fd >= 0)
		close(p->fd);
	gnl_clear();
	if (p->data)
		free_mapdata(p->data);
	if (p->ctx)
		ft_clean(p->ctx);
	exit(EXIT_FAILURE);
}
