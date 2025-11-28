/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

int	validate_extension(const char *filename)
{
	int	len;

	if (!filename)
		return (parse_error("No filename provided"));
	len = ft_strlen(filename);
	if (len < 5)
		return (parse_error("Invalid file extension (must be .cub)"));
	if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		return (parse_error("Invalid file extension (must be .cub)"));
	return (0);
}

int	check_required_elements(t_mapdata *data)
{
	if (!data->tex.north)
		return (parse_error("Missing north texture (NO)"));
	if (!data->tex.south)
		return (parse_error("Missing south texture (SO)"));
	if (!data->tex.west)
		return (parse_error("Missing west texture (WE)"));
	if (!data->tex.east)
		return (parse_error("Missing east texture (EA)"));
	if (!data->floor.is_set)
		return (parse_error("Missing floor color (F)"));
	if (!data->ceiling.is_set)
		return (parse_error("Missing ceiling color (C)"));
	return (0);
}

int	parse_cub_file(const char *filename, t_mapdata *data)
{
	int		fd;
	char	*first_map_line;

	init_mapdata(data);
	if (validate_extension(filename))
		return (1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (parse_error("Cannot open file"));
	if (parse_elements(fd, data, &first_map_line))
		return (close(fd), 1);
	if (check_required_elements(data))
		return (free(first_map_line), close(fd), 1);
	if (parse_map_lines(fd, first_map_line, data))
		return (free(first_map_line), close(fd), 1);
	free(first_map_line);
	close(fd);
	if (validate_map(data))
		return (1);
	return (0);
}
