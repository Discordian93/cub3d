/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypacileo <ypacileo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:11:34 by ypacileo          #+#    #+#             */
/*   Updated: 2025/11/23 18:48:14 by ypacileo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"



/* -------------------------------------------------------------------------- */
/*  put_px                                                                    */
/*  Objetivo: Escribir un color **RGB** (0xRRGGBB) en el píxel (x,y) del      */
/*            framebuffer, siempre que esté dentro de la ventana.             */
/* -------------------------------------------------------------------------- */
void put_px(t_img *img, int x, int y, int rgb)
{
    char *dst;                                 // Puntero destino dentro del buffer

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;                                // Si (x,y) cae fuera de pantalla, no dibujamos
    dst = img->addr + (y * img->line_len       // Avanza 'y' filas completas (bytes)
                       + x * (img->bpp / 8));  // Avanza 'x' píxeles dentro de la fila (bytes)
    *(unsigned int *)dst = (unsigned int)rgb;  // Escribe 0xRRGGBB en el buffer (MLX usa 32 bpp)
}





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
    if (k < 0.60)
        k = 0.60;
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


