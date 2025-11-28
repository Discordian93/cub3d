/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	load_texture(void *mlx, char *path, t_img *img)
{
	img->ptr = mlx_xpm_file_to_image(mlx, path, &img->width, &img->height);
	if (!img->ptr)
	{
		ft_putstr_fd("Error\nFailed to load texture: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	img->addr = mlx_get_data_addr(img->ptr, &img->bpp,
			&img->line_len, &img->endian);
	if (!img->addr)
	{
		mlx_destroy_image(mlx, img->ptr);
		img->ptr = NULL;
		return (1);
	}
	return (0);
}

int	load_textures(t_game *game)
{
	if (load_texture(game->mlx, game->mapdata.tex.north,
			&game->textures.north))
		return (1);
	if (load_texture(game->mlx, game->mapdata.tex.south,
			&game->textures.south))
		return (1);
	if (load_texture(game->mlx, game->mapdata.tex.east,
			&game->textures.east))
		return (1);
	if (load_texture(game->mlx, game->mapdata.tex.west,
			&game->textures.west))
		return (1);
	return (0);
}
