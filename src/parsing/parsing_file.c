/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

static int	handle_map_start(t_mapdata *data, char *line, char **first)
{
	if (!all_elements_set(data))
	{
		free(line);
		return (parse_error("Missing elements before map"));
	}
	*first = line;
	return (2);
}

static int	process_element(char *line, t_mapdata *data, char **first)
{
	int	result;

	result = parse_element_line(line, data);
	if (result == 1)
	{
		free(line);
		return (1);
	}
	if (result == -1)
		return (handle_map_start(data, line, first));
	return (0);
}

static int	parse_loop(int fd, t_mapdata *data, char **first_map_line)
{
	char	*line;
	int		ret;

	line = get_next_line(fd);
	while (line)
	{
		if (!is_empty_line(line))
		{
			ret = process_element(line, data, first_map_line);
			if (ret == 1)
				return (1);
			if (ret == 2)
				return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (-1);
}

int	parse_elements(int fd, t_mapdata *data, char **first_map_line)
{
	int	ret;

	*first_map_line = NULL;
	ret = parse_loop(fd, data, first_map_line);
	if (ret == 1)
		return (1);
	if (ret == -1)
	{
		if (!all_elements_set(data))
			return (parse_error("Missing required elements"));
		return (parse_error("No map found in file"));
	}
	return (0);
}
