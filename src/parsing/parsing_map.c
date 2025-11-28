/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

static void	remove_newline(char *str)
{
	int	len;

	if (!str)
		return ;
	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}

static void	replace_tabs(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\t')
			str[i] = ' ';
		i++;
	}
}

int	add_map_line(t_mapdata *data, char *line, int *capacity)
{
	int	len;

	if (data->map_height >= *capacity)
	{
		if (grow_map_array(data, capacity))
			return (1);
	}
	remove_newline(line);
	replace_tabs(line);
	data->map[data->map_height] = ft_strdup(line);
	if (!data->map[data->map_height])
		return (1);
	len = ft_strlen(data->map[data->map_height]);
	if (len > data->map_width)
		data->map_width = len;
	data->map_height++;
	return (0);
}

int	parse_map_lines(int fd, char *first_line, t_mapdata *data)
{
	char	*line;
	int		capacity;
	int		found_empty;

	capacity = 0;
	data->map = NULL;
	data->map_height = 0;
	data->map_width = 0;
	if (add_map_line(data, first_line, &capacity))
		return (parse_error("Memory allocation failed"));
	found_empty = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (process_map_line(data, line, &capacity, &found_empty))
			return (free(line), 1);
		free(line);
		line = get_next_line(fd);
	}
	if (data->map_height == 0)
		return (parse_error("Empty map"));
	return (0);
}
