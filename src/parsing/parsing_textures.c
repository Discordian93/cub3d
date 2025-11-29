/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student          ###   ########.fr       */
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
	if (!path)
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
