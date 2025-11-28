/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_tex_params(t_tex_params *tp, t_img *tex, int *bounds)
{
	double	wall_h;

	wall_h = (bounds[1] - bounds[0]);
	if (wall_h < 1)
		wall_h = 1;
	tp->tex_step = (double)tex->height / wall_h;
	tp->tex_pos = (bounds[0] - HEIGHT / 2 + wall_h / 2) * tp->tex_step;
}

void	draw_wall_stripe(t_game *game, int x, int *bounds, t_raycast *rc)
{
	t_img			*tex;
	t_tex_params	tp;
	int				tex_x;
	int				y;

	tex = select_texture(game, rc->side);
	tex_x = (int)(rc->wall_x * tex->width);
	init_tex_params(&tp, tex, bounds);
	y = bounds[0];
	while (y < bounds[1])
	{
		tp.tex_y = (int)tp.tex_pos;
		if (tp.tex_y >= tex->height)
			tp.tex_y = tex->height - 1;
		tp.tex_pos += tp.tex_step;
		tp.color = get_texture_pixel(tex, tex_x, tp.tex_y);
		put_pixel(&game->frame, x, y, tp.color);
		y++;
	}
}
