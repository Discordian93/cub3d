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

static char	*pad_line(const char *line, int width)
{
	char	*padded;
	int		len;
	int		i;

	padded = malloc(width + 1);
	if (!padded)
		return (NULL);
	len = ft_strlen(line);
	i = 0;
	while (i < len && i < width)
	{
		padded[i] = line[i];
		i++;
	}
	while (i < width)
	{
		padded[i] = ' ';
		i++;
	}
	padded[width] = '\0';
	return (padded);
}

void	copy_map_lines(t_mapdata *data, t_map *map)
{
	int	i;

	i = 0;
	while (i < data->count)
	{
		map->map[i] = pad_line(data->lines[i], data->width);
		if (!map->map[i])
		{
			while (--i >= 0)
				free(map->map[i]);
			free(map->map);
			ft_putstr_fd("Error\nMemory allocation failed\n", 2);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	map->map[data->count] = NULL;
}

void	build_map(t_mapdata *data, t_map *map)
{
	if (data->count == 0)
	{
		ft_putstr_fd("Error\nNo map found\n", 2);
		exit(EXIT_FAILURE);
	}
	map->height = data->count;
	map->width = data->width;
	map->map = malloc(sizeof(char *) * (data->count + 1));
	if (!map->map)
	{
		ft_putstr_fd("Error\nMemory allocation failed\n", 2);
		exit(EXIT_FAILURE);
	}
	copy_map_lines(data, map);
}
