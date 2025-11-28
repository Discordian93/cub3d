/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	destroy_texture(void *mlx, t_img *img)
{
	if (img->ptr)
		mlx_destroy_image(mlx, img->ptr);
	img->ptr = NULL;
}

static void	destroy_all_textures(t_game *game)
{
	destroy_texture(game->mlx, &game->textures.north);
	destroy_texture(game->mlx, &game->textures.south);
	destroy_texture(game->mlx, &game->textures.east);
	destroy_texture(game->mlx, &game->textures.west);
}

void	cleanup_game(t_game *game)
{
	if (game->mlx)
	{
		destroy_all_textures(game);
		if (game->frame.ptr)
			mlx_destroy_image(game->mlx, game->frame.ptr);
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free_mapdata(&game->mapdata);
}
