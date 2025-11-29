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

int	is_map_line(const char *line)
{
	while (*line)
	{
		if (*line != '0' && *line != '1' && *line != ' '
			&& *line != 'N' && *line != 'S' && *line != 'E'
			&& *line != 'W' && *line != '\t')
			return (0);
		line++;
	}
	return (1);
}

int	grow_map_array(t_mapdata *data, int *capacity)
{
	char	**new_lines;
	int		i;

	*capacity *= 2;
	new_lines = malloc(sizeof(char *) * (*capacity));
	if (!new_lines)
		return (0);
	i = 0;
	while (i < data->count)
	{
		new_lines[i] = data->lines[i];
		i++;
	}
	free(data->lines);
	data->lines = new_lines;
	return (1);
}

int	add_map_line(t_mapdata *data, char *line, int *cap)
{
	char	*copy;
	int		len;

	if (data->count >= *cap - 1)
	{
		if (!grow_map_array(data, cap))
			return (0);
	}
	copy = ft_strdup(line);
	if (!copy)
		return (0);
	len = ft_strlen(copy);
	if (len > 0 && copy[len - 1] == '\n')
		copy[len - 1] = '\0';
	data->lines[data->count] = copy;
	data->count++;
	len = ft_strlen(copy);
	if (len > data->width)
		data->width = len;
	return (1);
}

int	process_map_line(t_mapdata *d, char *line, int *cap, int *found)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, " \t\n\r");
	if (!trimmed)
		return (0);
	if (ft_strlen(trimmed) == 0)
	{
		if (d->count > 0)
			*found = 1;
		free(trimmed);
		return (1);
	}
	free(trimmed);
	if (*found)
	{
		ft_putstr_fd("Error\nEmpty line in map\n", 2);
		return (0);
	}
	return (add_map_line(d, line, cap));
}
