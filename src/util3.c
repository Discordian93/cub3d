/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 13:14:33 by yuliano           #+#    #+#             */
/*   Updated: 2025/11/22 17:55:32 by yuliano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


/*int get_tex_color(t_img *tex, int tx, int ty)
{
    char            *pix;
    unsigned int    color;

    pix = tex->addr + (ty * tex->line_len
        + tx * (tex->bpp / 8));
    color = *(unsigned int *)pix;
    return ((int)color);
}*/

int	get_tex_color(t_img *tex, int tx, int ty)
{
	char			*pix;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned int	color;

	pix = tex->addr + (ty * tex->line_len
			+ tx * (tex->bpp / 8));

	/* ------------------------------------------------------------------ */
	/* ANTES:                                                              */
	/* color = *(unsigned int *)pix;                                      */
	/* Esto coge los 4 bytes tal cual están (BGRA en memoria) y los       */
	/* interpreta como un entero según el endian de la CPU (ARGB),        */
	/* mientras que el resto del código trata 'color' como 0xRRGGBB.      */
	/* Resultado: canales desordenados y artefactos de color en bordes.   */
	/* ------------------------------------------------------------------ */

	/* CAMBIO: reconstruimos el color a mano como 0xRRGGBB ignorando alpha,
	   respetando el formato BGRA que usa minilibx en Linux. */
	b = (unsigned char)pix[0];
	g = (unsigned char)pix[1];
	r = (unsigned char)pix[2];
	color = (r << 16) | (g << 8) | b;

	return ((int)color);
}


/* -------------------------------------------------------------------------- */
/*  shade_from_dist                                                           */
/*  Objetivo: Calcular factor de sombreado (0.2..1.0) a partir de la          */
/*            distancia **corregida** (anti fish-eye).                         */
/*            - Cerca  ⇒ k≈1 (más claro)                                       */
/*            - Lejos  ⇒ k≈0.2 (más oscuro)                                    */
/* -------------------------------------------------------------------------- */
double  shade_from_dist(double corr)
{
    double  k;

    /* Atenuación lineal muy suave */
    k = 1.0 - (corr * 0.02);
    if (k > 1.0)
        k = 1.0;
    if (k < 0.40)
        k = 0.40;
    return (k);
}


int apply_shade(int color, double shade)
{
    int r;
    int g;
    int b;

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


/*
t_img *select_texture(t_contex *c, double dirx, double diry)
{
    if (c->pl->side == 0)
    {
        if (dirx > 0)
            return (c->tex_we);
        else
            return (c->tex_ea);
    }
    else
    {
        if (diry > 0)
            return (c->tex_nort);
        else
            return (c->tex_so);
    }
}
*/
