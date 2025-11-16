/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypacileo <ypacileo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 13:14:33 by yuliano           #+#    #+#             */
/*   Updated: 2025/11/16 15:54:34 by ypacileo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


int get_tex_color(t_img *tex, int tx, int ty)
{
    char            *pix;
    unsigned int    color;

    pix = tex->addr + (ty * tex->line_len
        + tx * (tex->bpp / 8));
    color = *(unsigned int *)pix;
    return ((int)color);
}

/* -------------------------------------------------------------------------- */
/*  shade_from_dist                                                           */
/*  Objetivo: Calcular factor de sombreado (0.2..1.0) a partir de la          */
/*            distancia **corregida** (anti fish-eye).                         */
/*            - Cerca  ⇒ k≈1 (más claro)                                       */
/*            - Lejos  ⇒ k≈0.2 (más oscuro)                                    */
/* -------------------------------------------------------------------------- */
double shade_from_dist(double corr)
{
    double k = 1.0 / (1.0 + 0.15 * corr * corr); // Curva suave decreciente con la distancia
    if (k < 0.20) k = 0.20;                      // Clamp mínimo (evita negro total)
    return (k);
}