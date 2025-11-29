/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esteizag <esteizag@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 18:44:28 by esteizag          #+#    #+#             */
/*   Updated: 2025/11/29 18:44:31 by esteizag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_texture_identifier(const char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (1);
	return (0);
}

int	validate_path(char *path)
{
	char	*firstdot;

	firstdot = ft_strchr(path, '.');
	if (!firstdot || ft_strlen(path) == ft_strlen(firstdot)
		|| ft_strlen(firstdot) != 4 || ft_strncmp(firstdot, ".xpm", 4) != 0)
		return (0);
	return (1);
}

int	parse_texture(const char *line, char **dest)
{
	char	*path;
	char	*trimmed;

	if (*dest != NULL)
	{
		ft_putstr_fd("Error\nDuplicate texture\n", 2);
		return (0);
	}
	while (*line && ft_isspace(*line))
		line++;
	path = ft_strdup(line);
	if (!path || validate_path(path))
		return (0);
	trimmed = ft_strtrim(path, " \t\n\r");
	free(path);
	if (!trimmed || ft_strlen(trimmed) == 0)
	{
		free(trimmed);
		return (0);
	}
	*dest = trimmed;
	return (1);
}
