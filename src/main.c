/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypacileo <ypacileo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2025/11/29 18:36:01 by ypacileo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "parsing.h"

static void	init_mlx_window(t_contex *contex)
{
	contex->mlx = mlx_init();
	if (contex->mlx == NULL)
	{
		ft_clean(contex);
		ft_error("Error initializing mlx\n");
	}
	contex->win = mlx_new_window(contex->mlx, WIDTH, HEIGHT, "Cub3D");
	if (contex->win == NULL)
	{
		ft_clean(contex);
		ft_error("Error initializing window\n");
	}
}

static void	init_framebuffer(t_contex *contex)
{
	contex->img->ptr = mlx_new_image(contex->mlx, WIDTH, HEIGHT);
	if (contex->img->ptr == NULL)
	{
		ft_clean(contex);
		ft_error("Error creating image\n");
	}
	contex->img->addr = mlx_get_data_addr(contex->img->ptr,
			&contex->img->bpp,
			&contex->img->line_len,
			&contex->img->endian);
}

static void	setup_hooks(t_contex *contex)
{
	mlx_loop_hook(contex->mlx, &loop_hook, contex);
	mlx_hook(contex->win, 2, 1L << 0, handle_keypress, contex);
	mlx_hook(contex->win, 17, 0, handle_destroy, contex);
}

int	main(int argc, char **argv)
{
	t_contex	*contex;

	if (argc != 2)
		ft_error("Usage: ./cub3D <map.cub>\n");
	init_contex(&contex);
	parse_cub_file(argv[1], contex);
	init_mlx_window(contex);
	init_framebuffer(contex);
	load_textures(contex);
	find_player(contex->pl, contex->map_g);
	contex->proj_dist = (WIDTH / 2.0) / tan(FOV_RAD / 2.0);
	setup_hooks(contex);
	mlx_loop(contex->mlx);
	return (0);
}
