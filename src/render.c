/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypacileo <ypacileo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 18:46:36 by ypacileo          #+#    #+#             */
/*   Updated: 2025/11/29 18:46:41 by ypacileo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_column(t_column *col, t_contex *contex)
{
	col->wall_h_real = contex->pl->wall_h;
	if (col->wall_h_real < 1.0)
		col->wall_h_real = 1.0;
	col->y_top_real = (HEIGHT - col->wall_h_real) * 0.5;
	col->y_top = (int)col->y_top_real;
	if (col->y_top < 0)
		col->y_top = 0;
	col->y_bot = (int)(col->y_top_real + col->wall_h_real);
	if (col->y_bot > HEIGHT)
		col->y_bot = HEIGHT;
	col->tex_x = (int)(contex->pl->tex_x_rel * contex->selec_text.width);
	if (col->tex_x < 0)
		col->tex_x = 0;
	if (col->tex_x >= contex->selec_text.width)
		col->tex_x = contex->selec_text.width - 1;
}

static void	draw_wall_stripe(t_contex *ctx, int x, t_column *col)
{
	int		y;
	int		tex_y;
	double	rel;
	int		color;

	y = col->y_top;
	while (y < col->y_bot)
	{
		rel = ((double)y - col->y_top_real) / col->wall_h_real;
		tex_y = (int)(rel * ctx->selec_text.height);
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= ctx->selec_text.height)
			tex_y = ctx->selec_text.height - 1;
		color = get_tex_color(&ctx->selec_text, col->tex_x, tex_y);
		color = apply_shade(color, ctx->pl->shade);
		put_px(ctx->img, x, y, color);
		y++;
	}
}

void	draw_column(t_contex *contex, int x)
{
	t_column	col;
	int			y;

	init_column(&col, contex);
	y = 0;
	while (y < col.y_top)
	{
		put_px(contex->img, x, y, contex->config->ceil_color);
		y++;
	}
	draw_wall_stripe(contex, x, &col);
	y = col.y_bot;
	while (y < HEIGHT)
	{
		put_px(contex->img, x, y, contex->config->floor_color);
		y++;
	}
}
