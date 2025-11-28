/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	set_wall_side(t_raycast *rc, double dx, double dy)
{
	if (fabs(dx) > fabs(dy))
	{
		if (dx > 0)
			rc->side = 0;
		else
			rc->side = 1;
	}
	else
	{
		if (dy > 0)
			rc->side = 3;
		else
			rc->side = 2;
	}
}

static void	set_wall_x(t_raycast *rc, double rx, double ry)
{
	if (rc->side == 0 || rc->side == 1)
		rc->wall_x = ry - floor(ry);
	else
		rc->wall_x = rx - floor(rx);
}

double	cast_ray(t_game *game, double angle, t_raycast *rc)
{
	double	rx;
	double	ry;
	double	delta[2];

	rx = game->player.x;
	ry = game->player.y;
	delta[0] = cos(angle) * STEP;
	delta[1] = sin(angle) * STEP;
	rc->dist = 0.0;
	while (rc->dist < 64.0)
	{
		rx += delta[0];
		ry += delta[1];
		rc->dist += STEP;
		if (is_wall(game, rx, ry))
		{
			set_wall_side(rc, delta[0], delta[1]);
			set_wall_x(rc, rx, ry);
			return (rc->dist);
		}
	}
	return (rc->dist);
}

void	render_frame(t_game *game)
{
	int			x;
	double		ray_angle;
	double		corrected_dist;
	double		wall_h;
	t_raycast	rc;

	x = 0;
	while (x < WIDTH)
	{
		ray_angle = game->player.dir
			+ atan(((double)x - WIDTH / 2.0) / game->proj_dist);
		cast_ray(game, ray_angle, &rc);
		corrected_dist = rc.dist * cos(ray_angle - game->player.dir);
		wall_h = (TILE_SZ * game->proj_dist) / (corrected_dist + EPS);
		draw_column(game, x, wall_h, &rc);
		x++;
	}
}
