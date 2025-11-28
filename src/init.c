/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	color_to_int(t_color *color)
{
	return ((color->r << 16) | (color->g << 8) | color->b);
}

void	init_player(t_game *game)
{
	game->player.x = game->mapdata.spawn.x + 0.5;
	game->player.y = game->mapdata.spawn.y + 0.5;
	if (game->mapdata.spawn.dir == 'N')
		game->player.dir = -M_PI / 2;
	else if (game->mapdata.spawn.dir == 'S')
		game->player.dir = M_PI / 2;
	else if (game->mapdata.spawn.dir == 'E')
		game->player.dir = 0;
	else if (game->mapdata.spawn.dir == 'W')
		game->player.dir = M_PI;
}

static int	init_frame(t_game *game)
{
	game->frame.ptr = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->frame.ptr)
		return (1);
	game->frame.addr = mlx_get_data_addr(game->frame.ptr,
			&game->frame.bpp, &game->frame.line_len, &game->frame.endian);
	if (!game->frame.addr)
		return (1);
	game->frame.width = WIDTH;
	game->frame.height = HEIGHT;
	return (0);
}

static int	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (parse_error("Failed to initialize MLX"));
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	if (!game->win)
		return (parse_error("Failed to create window"));
	if (init_frame(game))
		return (1);
	return (0);
}

int	init_game(t_game *game, char *map_file)
{
	ft_bzero(game, sizeof(t_game));
	if (parse_cub_file(map_file, &game->mapdata))
		return (1);
	game->floor_color = color_to_int(&game->mapdata.floor);
	game->ceiling_color = color_to_int(&game->mapdata.ceiling);
	if (init_mlx(game))
		return (1);
	if (load_textures(game))
		return (1);
	init_player(game);
	game->proj_dist = (WIDTH / 2.0) / tan(FOV_RAD / 2.0);
	return (0);
}
