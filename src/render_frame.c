/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypacileo <ypacileo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 18:46:27 by ypacileo          #+#    #+#             */
/*   Updated: 2025/11/29 18:46:31 by ypacileo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static double	calc_wall_x(t_contex *contex, double cell_x, double cell_y)
{
	double	wall_x;

	if (contex->pl->face == FACE_EA)
		wall_x = 1.0 - cell_y;
	else if (contex->pl->face == FACE_WE)
		wall_x = cell_y;
	else if (contex->pl->face == FACE_NO)
		wall_x = 1.0 - cell_x;
	else
		wall_x = cell_x;
	if (wall_x < 0.0)
		wall_x = 0.0;
	if (wall_x >= 1.0)
		wall_x = 1.0;
	return (wall_x);
}

static void	process_column(t_contex *contex, int x, double ray_ang)
{
	double	cell_x;
	double	cell_y;

	contex->pl->dist = cast_ray(ray_ang, contex);
	contex->pl->corr = contex->pl->dist * cos(ray_ang - contex->pl->dir);
	contex->pl->wall_h = (TILE_SZ * contex->proj_dist)
		/ (contex->pl->corr + EPS);
	cell_x = contex->pl->hit_x - floor(contex->pl->hit_x);
	cell_y = contex->pl->hit_y - floor(contex->pl->hit_y);
	contex->pl->tex_x_rel = calc_wall_x(contex, cell_x, cell_y);
	contex->selec_text = contex->text[contex->pl->face];
	contex->pl->shade = shade_from_dist(contex->pl->corr);
	draw_column(contex, x);
}

void	render_frame(t_contex *contex)
{
	int		x;
	double	ray_ang;

	x = 0;
	while (x < WIDTH)
	{
		ray_ang = contex->pl->dir
			+ atan(((double)x - (WIDTH / 2.0)) / contex->proj_dist);
		process_column(contex, x, ray_ang);
		x++;
	}
}

int	loop_hook(t_contex *contex)
{
	render_frame(contex);
	mlx_put_image_to_window(contex->mlx, contex->win, contex->img->ptr, 0, 0);
	return (0);
}
