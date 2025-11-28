/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

static int	is_map_char(char c)
{
	if (c == '0' || c == '1')
		return (1);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	is_map_line(char *line)
{
	int	i;
	int	has_map_char;

	if (!line || is_empty_line(line))
		return (0);
	i = 0;
	has_map_char = 0;
	while (line[i] && line[i] != '\n')
	{
		if (is_map_char(line[i]))
			has_map_char = 1;
		else if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (has_map_char);
}

static void	free_map_array(t_mapdata *data)
{
	int	i;

	if (data->map)
	{
		i = 0;
		while (i < data->map_height)
		{
			if (data->map[i])
				free(data->map[i]);
			i++;
		}
		free(data->map);
	}
}

void	free_mapdata(t_mapdata *data)
{
	if (data->tex.north)
		free(data->tex.north);
	if (data->tex.south)
		free(data->tex.south);
	if (data->tex.east)
		free(data->tex.east);
	if (data->tex.west)
		free(data->tex.west);
	free_map_array(data);
}
