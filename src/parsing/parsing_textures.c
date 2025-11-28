/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

static int	parse_texture(char *line, char **dest)
{
	char	*path;

	if (*dest != NULL)
		return (parse_error("Duplicate texture definition"));
	path = ft_strtrim_space(line);
	if (!path || *path == '\0')
		return (parse_error("Empty texture path"));
	*dest = ft_strdup(path);
	if (!*dest)
		return (parse_error("Memory allocation failed"));
	return (0);
}

static int	get_texture_type(char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0 && (line[2] == ' ' || line[2] == '\t'))
		return (1);
	if (ft_strncmp(line, "SO", 2) == 0 && (line[2] == ' ' || line[2] == '\t'))
		return (2);
	if (ft_strncmp(line, "WE", 2) == 0 && (line[2] == ' ' || line[2] == '\t'))
		return (3);
	if (ft_strncmp(line, "EA", 2) == 0 && (line[2] == ' ' || line[2] == '\t'))
		return (4);
	return (0);
}

static char	*skip_whitespace(char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	return (str);
}

int	try_parse_texture(char *line, t_mapdata *data)
{
	int		type;
	char	*content;

	type = get_texture_type(line);
	if (type == 0)
		return (-1);
	content = skip_whitespace(line + 2);
	if (type == 1)
		return (parse_texture(content, &data->tex.north));
	else if (type == 2)
		return (parse_texture(content, &data->tex.south));
	else if (type == 3)
		return (parse_texture(content, &data->tex.west));
	else if (type == 4)
		return (parse_texture(content, &data->tex.east));
	return (-1);
}
