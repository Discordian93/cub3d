 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 22:04:41 by yuliano           #+#    #+#             */
/*   Updated: 2025/11/08 22:47:13 by yuliano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3D.h"
#include <math.h>
#include <stdio.h>

#define MOVE_SPEED 0.08


double	degrees_to_radians(double degrees)
{
	return (degrees * (M_PI / 180.0));
}

int	map_is_wall(t_map *map, int mx, int my)
{
	if (mx < 0 || mx >= map->width || my < 0 || my >= map->height)
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

int	is_there_a_player(t_map *map, int y, int x)
{
	if (map->map[y][x] == 'E' || map->map[y][x] == 'N'
		|| map->map[y][x] == 'W' || map->map[y][x] == 'S')
		return (1);
	return (0);
}

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
	pl->rel = 0.0;
	pl->dir = normalize_angle(dir);
}

void	find_player(t_player *pl, t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (is_there_a_player(map, y, x))
			{
				init_pos_pl(pl, map, y, x);
				return ;
			}
			x++;
		}
		y++;
	}
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

/*
** Movimiento y rotación. ESC libera todo y sale.
*/

/*
int	handle_keypress(int keycode, t_contex *contex)
{
	double	step;

	step = 0.25;
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
		move_player(contex->pl, contex->map_g,
			cos(contex->pl->dir) * MOVE_SPEED,
			sin(contex->pl->dir) * MOVE_SPEED);
	else if (keycode == KEY_S)
		move_player(contex->pl, contex->map_g,
			cos(contex->pl->dir) * -MOVE_SPEED,
			sin(contex->pl->dir) * -MOVE_SPEED);
	else if (keycode == KEY_A)
		move_player(contex->pl, contex->map_g,
			cos(contex->pl->dir - M_PI / 2.0) * MOVE_SPEED,
			sin(contex->pl->dir - M_PI / 2.0) * MOVE_SPEED);
	else if (keycode == KEY_D)
		move_player(contex->pl, contex->map_g,
			cos(contex->pl->dir + M_PI / 2.0) * MOVE_SPEED,
			sin(contex->pl->dir + M_PI / 2.0) * MOVE_SPEED);
	printf("dir = %.2f rad (%.1f°) | pos = (%.2f, %.2f)\n",
		contex->pl->dir,
		contex->pl->dir * 180.0 / M_PI,
		contex->pl->x, contex->pl->y);
	return (0);
}
*/

int	handle_keypress(int keycode, t_contex *contex)
{
	double	step;
	double	dist_front;
	double	dist_back;
	double	min_dist;

	step = 0.20;
	min_dist = 0.20;  /* Distancia mínima de seguridad */

	if (keycode == KEY_ESC)
	{
		ft_clean(contex);
		exit(0);
	}
	else if (keycode == KEY_LEFT)
		contex->pl->dir = normalize_angle(contex->pl->dir + step);
	else if (keycode == KEY_RIGHT)
		contex->pl->dir = normalize_angle(contex->pl->dir - step);

	/* --- Movimiento hacia adelante (W) --- */
	else if (keycode == KEY_W)
	{
		dist_front = cast_ray(contex->pl->dir, contex);
		if (dist_front > min_dist)
			move_player(contex->pl, contex->map_g,
				cos(contex->pl->dir) * MOVE_SPEED,
				sin(contex->pl->dir) * MOVE_SPEED);
	}

	/* --- Movimiento hacia atrás (S) --- */
	else if (keycode == KEY_S)
	{
		dist_back = cast_ray(contex->pl->dir + M_PI, contex);
        if (dist_back > min_dist)
			move_player(contex->pl, contex->map_g,
				cos(contex->pl->dir) * -MOVE_SPEED,
				sin(contex->pl->dir) * -MOVE_SPEED);
	}

	/* --- Strafe izquierda (A) --- */
	else if (keycode == KEY_A)
		move_player(contex->pl, contex->map_g,
			cos(contex->pl->dir - M_PI / 2.0) * MOVE_SPEED,
			sin(contex->pl->dir - M_PI / 2.0) * MOVE_SPEED);

	/* --- Strafe derecha (D) --- */
	else if (keycode == KEY_D)
		move_player(contex->pl, contex->map_g,
			cos(contex->pl->dir + M_PI / 2.0) * MOVE_SPEED,
			sin(contex->pl->dir + M_PI / 2.0) * MOVE_SPEED);

	printf("dir = %.2f rad (%.1f°) | pos = (%.2f, %.2f)\n",
		contex->pl->dir,
		contex->pl->dir * 180.0 / M_PI,
		contex->pl->x, contex->pl->y);

	return (0);
}
