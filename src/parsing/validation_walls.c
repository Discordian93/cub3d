/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_walls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	is_space_or_edge(t_map *map, int y, int x)
{
	if (y < 0 || y >= map->height)
		return (1);
	if (x < 0 || x >= map->width)
		return (1);
	if (map->map[y][x] == ' ' || map->map[y][x] == '\0')
		return (1);
	return (0);
}

int	check_adjacent(t_map *map, int y, int x)
{
	if (is_space_or_edge(map, y - 1, x))
		return (0);
	if (is_space_or_edge(map, y + 1, x))
		return (0);
	if (is_space_or_edge(map, y, x - 1))
		return (0);
	if (is_space_or_edge(map, y, x + 1))
		return (0);
	return (1);
}

int	is_exposed(t_map *map, int y, int x)
{
	if (!is_walkable(map->map[y][x]))
		return (0);
	return (!check_adjacent(map, y, x));
}

int	check_map_closed(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width && map->map[y][x])
		{
			if (is_exposed(map, y, x))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}
