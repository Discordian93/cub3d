/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypacileo <ypacileo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:11:34 by ypacileo          #+#    #+#             */
/*   Updated: 2025/11/16 15:54:27 by ypacileo         ###   ########.fr       */
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

/* -------------------------------------------------------------------------- */
/*  pack_rgb                                                                  */
/*  Objetivo: Empaquetar tres componentes R,G,B (0..255) en un entero 0xRRGGBB.*/
/* -------------------------------------------------------------------------- */
int pack_rgb(int r, int g, int b)
{
    if (r < 0) r = 0; if (r > 255) r = 255;   // Asegura rango válido para R
    if (g < 0) g = 0; if (g > 255) g = 255;   // Asegura rango válido para G
    if (b < 0) b = 0; if (b > 255) b = 255;   // Asegura rango válido para B
    return ((r << 16) | (g << 8) | b);        // Combina R, G y B en 0xRRGGBB
}


/* -------------------------------------------------------------------------- */
/*  mul_color_rgb                                                              */
/*  Objetivo: Aplicar un factor 'k' (0..1) al color RGB 0xRRGGBB, afectando   */
/*            solo los canales R,G,B (sin alfa). Devuelve 0xRRGGBB.           */
/* -------------------------------------------------------------------------- */
int mul_color_rgb(int color, double k)
{
    int r, g, b;                               // Componentes extraídos

    if (k < 0.0) k = 0.0;                      // Clampea k al rango [0,1]
    if (k > 1.0) k = 1.0;

    r = (color >> 16) & 0xFF;                  // Extrae R (bits 23..16)
    g = (color >> 8)  & 0xFF;                  // Extrae G (bits 15..8)
    b =  color        & 0xFF;                  // Extrae B (bits 7..0)

    r = (int)(r * k);                          // Escala R por k
    g = (int)(g * k);                          // Escala G por k
    b = (int)(b * k);                          // Escala B por k

    if (r > 255) r = 255; if (g > 255) g = 255; if (b > 255) b = 255; // Seguridad
    return pack_rgb(r, g, b);                  // Reempaqueta y devuelve 0xRRGGBB
}




/*
** calcular_max_distancia
** Objetivo: Calcular la distancia máxima que puede recorrer un rayo
** en el mapa (diagonal × 1.5 como margen de seguridad).
*/
double calc_max_dist(int width, int height)
{
    double diagonal = sqrt(width * width + height * height);
    return diagonal * 1.5;
}
// Uso:
//double limite = calcular_limite_seguridad(5, 5);
