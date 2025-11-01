/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypacileo <ypacileo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:03:53 by ypacileo          #+#    #+#             */
/*   Updated: 2025/11/01 17:10:32 by ypacileo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
#define CUB3D_H

#include <mlx.h>                 // API de MiniLibX: ventanas e imágenes
#include <math.h>                // Trigonometría y constantes (cos, sin, atan, tan, M_PI)
#include <stdlib.h>              // Utilidades estándar

#define WIDTH   800              // Ancho de la ventana en píxeles
#define HEIGHT  600              // Alto de la ventana en píxeles

#define TILE_SZ  1.0             // Altura/escala de una pared en el mundo (1 unidad por celda)
#define STEP     0.02            // Paso de avance incremental para el rayo
#define EPS      1e-9            // Épsilon para evitar divisiones por cero

typedef struct s_img 
{
    void    *ptr;        // Puntero a la imagen MLX
    char    *addr;       // Dirección de memoria del buffer de píxeles
    int     bpp;         // Bits por píxel (normalmente 32 en MLX Linux)
    int     line_len;    // Bytes por fila (stride)
    int     endian;      // Endianness del buffer
}   t_img;

typedef struct s_player 
{
    double x;            // Posición X en el mundo (columna), en unidades de celda
    double y;            // Posición Y en el mundo (fila), en unidades de celda
    double dir;          // Dirección de la cámara en radianes (0 = Este)
}   t_player;

typedef struct s_contex 
{
    void     *mlx;       // Contexto MLX
    void     *win;       // Ventana MLX
    t_img     frame;     // Framebuffer donde dibujamos
    t_player  pl;        // Estado del jugador/cámara
    double    proj_dist; // Distancia al plano de proyección: (WIDTH/2)/tan(FOV/2)
}   t_contex;


#endif

