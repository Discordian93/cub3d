/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_pos_pl(t_player *pl, t_map *map, int y, int x)
{
	double	dir;

	dir = 0.0;
	if (map->map[y][x] == 'E')
		dir = degrees_to_radians(0);
	else if (map->map[y][x] == 'N')
		dir = degrees_to_radians(90);
	else if (map->map[y][x] == 'W')
		dir = degrees_to_radians(180);
	else if (map->map[y][x] == 'S')
		dir = degrees_to_radians(270);
	pl->y = y + 0.5;
	pl->x = x + 0.5;
	pl->corr = 0.0;
	pl->dir = normalize_angle(dir);
}

void	move_player(t_player *pl, t_map *map, double move_x, double move_y)
{
	double	new_x;
	double	new_y;

	new_x = pl->x + move_x;
	new_y = pl->y + move_y;
	if (!map_is_wall(map, (int)new_x, (int)new_y))
	{
		pl->x = new_x;
		pl->y = new_y;
	}
}

static void	handle_move_forward(t_contex *contex)
{
	double	dist_front;
	double	min_dist;

	min_dist = 0.20;
	dist_front = cast_ray(contex->pl->dir, contex);
	if (dist_front > min_dist)
		move_player(contex->pl, contex->map_g,
			cos(contex->pl->dir) * MOVE_SPEED,
			sin(contex->pl->dir) * MOVE_SPEED);
}

static void	handle_move_backward(t_contex *contex)
{
	double	dist_back;
	double	min_dist;

	min_dist = 0.20;
	dist_back = cast_ray(contex->pl->dir + M_PI, contex);
	if (dist_back > min_dist)
		move_player(contex->pl, contex->map_g,
			cos(contex->pl->dir) * -MOVE_SPEED,
			sin(contex->pl->dir) * -MOVE_SPEED);
}

int	handle_keypress(int keycode, t_contex *contex)
{
	double	step;

	step = 0.20;
	if (keycode == KEY_ESC)
	{
		ft_clean(contex);
		exit(0);
	}
	else if (keycode == KEY_LEFT)
		contex->pl->dir = normalize_angle(contex->pl->dir + step);
	else if (keycode == KEY_RIGHT)
		contex->pl->dir = normalize_angle(contex->pl->dir - step);
	else if (keycode == KEY_W)
		handle_move_forward(contex);
	else if (keycode == KEY_S)
		handle_move_backward(contex);
	else if (keycode == KEY_A)
		move_player(contex->pl, contex->map_g,
			cos(contex->pl->dir - M_PI / 2.0) * MOVE_SPEED,
			sin(contex->pl->dir - M_PI / 2.0) * MOVE_SPEED);
	else if (keycode == KEY_D)
		move_player(contex->pl, contex->map_g,
			cos(contex->pl->dir + M_PI / 2.0) * MOVE_SPEED,
			sin(contex->pl->dir + M_PI / 2.0) * MOVE_SPEED);
	return (0);
}
