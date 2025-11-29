/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	put_px(t_img *img, int x, int y, int rgb)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = (unsigned int)rgb;
}

int	get_tex_color(t_img *tex, int tx, int ty)
{
	char			*pix;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	pix = tex->addr + (ty * tex->line_len + tx * (tex->bpp / 8));
	b = (unsigned char)pix[0];
	g = (unsigned char)pix[1];
	r = (unsigned char)pix[2];
	return ((r << 16) | (g << 8) | b);
}

double	shade_from_dist(double corr)
{
	double	k;

	k = 1.0 - (corr * 0.02);
	if (k > 1.0)
		k = 1.0;
	if (k < 0.60)
		k = 0.60;
	return (k);
}

int	apply_shade(int color, double shade)
{
	int	r;
	int	g;
	int	b;

	if (shade < 0.0)
		shade = 0.0;
	if (shade > 1.0)
		shade = 1.0;
	r = (int)(((color >> 16) & 0xFF) * shade);
	g = (int)(((color >> 8) & 0xFF) * shade);
	b = (int)((color & 0xFF) * shade);
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return ((r << 16) | (g << 8) | b);
}
