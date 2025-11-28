/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

static int	is_valid_map_char(char c)
{
	if (c == '0' || c == '1' || c == ' ')
		return (1);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

static int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	check_player(t_mapdata *data, int x, int y, char c)
{
	if (data->spawn.found)
		return (parse_error("Multiple player spawns found"));
	data->spawn.x = x;
	data->spawn.y = y;
	data->spawn.dir = c;
	data->spawn.found = 1;
	return (0);
}

int	validate_characters(t_mapdata *data)
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
			if (!is_valid_map_char(data->map[y][x]))
				return (parse_error("Invalid character in map"));
			if (is_player_char(data->map[y][x]))
				if (check_player(data, x, y, data->map[y][x]))
					return (1);
			x++;
		}
		y++;
	}
	if (!data->spawn.found)
		return (parse_error("No player spawn position found"));
	return (0);
}
