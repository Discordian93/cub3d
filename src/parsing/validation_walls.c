/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_walls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

static int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	check_adjacent(t_mapdata *data, int x, int y)
{
	if (x >= (int)ft_strlen(data->map[y - 1]))
		return (1);
	if (x >= (int)ft_strlen(data->map[y + 1]))
		return (1);
	if (data->map[y][x - 1] == ' ' || data->map[y][x + 1] == ' ')
		return (1);
	if (data->map[y - 1][x] == ' ' || data->map[y + 1][x] == ' ')
		return (1);
	return (0);
}

static int	is_exposed(t_mapdata *data, int x, int y)
{
	int	len;

	if (y == 0 || y == data->map_height - 1)
		return (1);
	if (x == 0)
		return (1);
	len = ft_strlen(data->map[y]);
	if (x >= len - 1)
		return (1);
	return (check_adjacent(data, x, y));
}

int	check_map_closed(t_mapdata *data)
{
	int	y;
	int	x;
	int	len;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		len = ft_strlen(data->map[y]);
		while (x < len)
		{
			if (is_walkable(data->map[y][x]))
			{
				if (is_exposed(data, x, y))
					return (parse_error("Map is not closed by walls"));
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	validate_map(t_mapdata *data)
{
	if (!data->map || data->map_height == 0)
		return (parse_error("No map found"));
	if (validate_characters(data))
		return (1);
	if (check_map_closed(data))
		return (1);
	return (0);
}
