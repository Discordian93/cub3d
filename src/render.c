/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_texture_pixel(t_img *tex, int tex_x, int tex_y)
{
	char	*pixel;

	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= tex->height)
		tex_y = tex->height - 1;
	pixel = tex->addr + (tex_y * tex->line_len + tex_x * (tex->bpp / 8));
	return (*(unsigned int *)pixel);
}

t_img	*select_texture(t_game *game, int side)
{
	if (side == 0)
		return (&game->textures.east);
	else if (side == 1)
		return (&game->textures.west);
	else if (side == 2)
		return (&game->textures.north);
	return (&game->textures.south);
}

static void	draw_ceiling_floor(t_game *game, int x, int *bounds)
{
	int	y;

	y = 0;
	while (y < bounds[0])
	{
		put_pixel(&game->frame, x, y, game->ceiling_color);
		y++;
	}
	y = bounds[1];
	while (y < HEIGHT)
	{
		put_pixel(&game->frame, x, y, game->floor_color);
		y++;
	}
}

static void	init_draw_bounds(int *bounds, double wall_h)
{
	bounds[0] = (HEIGHT - (int)wall_h) / 2;
	bounds[1] = (HEIGHT + (int)wall_h) / 2;
	if (bounds[0] < 0)
		bounds[0] = 0;
	if (bounds[1] >= HEIGHT)
		bounds[1] = HEIGHT - 1;
}

void	draw_column(t_game *game, int x, double wall_h, t_raycast *rc)
{
	int		bounds[2];

	init_draw_bounds(bounds, wall_h);
	draw_ceiling_floor(game, x, bounds);
	draw_wall_stripe(game, x, bounds, rc);
}
