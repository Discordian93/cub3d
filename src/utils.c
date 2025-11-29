/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypacileo <ypacileo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 18:46:47 by ypacileo          #+#    #+#             */
/*   Updated: 2025/11/29 18:46:51 by ypacileo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	degrees_to_radians(double degrees)
{
	return (degrees * (M_PI / 180.0));
}

int	map_is_wall(t_map *map, int mx, int my)
{
	if (mx < 0 || mx >= map->width || my < 0 || my >= map->height)
		return (1);
	if (map->map[my][mx] == ' ' || map->map[my][mx] == '\0')
		return (1);
	return (map->map[my][mx] == '1');
}

double	normalize_angle(double angle)
{
	double	two_pi;

	two_pi = 2.0 * M_PI;
	angle = fmod(angle, two_pi);
	if (angle < 0.0)
		angle += two_pi;
	return (angle);
}

static int	is_player_char(char c)
{
	return (c == 'E' || c == 'N' || c == 'W' || c == 'S');
}

void	find_player(t_player *pl, t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width && map->map[y][x])
		{
			if (is_player_char(map->map[y][x]))
			{
				init_pos_pl(pl, map, y, x);
				return ;
			}
			x++;
		}
		y++;
	}
}
