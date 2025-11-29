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

int	check_player(t_map *map, int y, int x, int *player_count)
{
	char	c;

	c = map->map[y][x];
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		(*player_count)++;
		if (*player_count > 1)
			return (0);
	}
	return (1);
}

static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ');
}

int	validate_characters(t_map *map)
{
	int	y;
	int	x;
	int	player_count;

	player_count = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width && map->map[y][x])
		{
			if (!is_valid_char(map->map[y][x]))
				return (0);
			if (!check_player(map, y, x, &player_count))
				return (0);
			x++;
		}
		y++;
	}
	if (player_count != 1)
		return (0);
	return (1);
}

void	validate_map(t_map *map)
{
	if (!validate_characters(map))
	{
		ft_putstr_fd("Error\nInvalid map characters or player count\n", 2);
		exit(EXIT_FAILURE);
	}
	if (!check_map_closed(map))
	{
		ft_putstr_fd("Error\nMap is not closed by walls\n", 2);
		exit(EXIT_FAILURE);
	}
}
