/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypacileo <ypacileo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 19:24:37 by yuliano           #+#    #+#             */
/*   Updated: 2025/11/09 15:24:32 by ypacileo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


/* -------------------------------------------------------------------------- */
/*  cast_ray                                                                  */
/*  Objetivo: Lanzar un rayo con ángulo 'ax' desde la posición del jugador,   */
/*            avanzando en pasos 'STEP' hasta colisionar con un muro.         */
/*            Devuelve la distancia recorrida en unidades de mundo.           */
/* -------------------------------------------------------------------------- */
double cast_ray(double ax, const t_player *pl, t_map *map)
{
    double rx = pl->x;                          // Posición X del rayo (inicia en jugador)
    double ry = pl->y;                          // Posición Y del rayo
    double dirx = cos(ax);                      // Dirección unitaria X del rayo
    double diry = sin(ax);                      // Dirección unitaria Y del rayo
    double dist = 0.0;                          // Distancia acumulada

    while (dist < 64.0)                         // Tope de seguridad
    {
        rx += dirx * STEP;                      // Avanza un paso en X
        ry += diry * STEP;                      // Avanza un paso en Y
        dist += STEP;                           // Suma distancia recorrida
        if (map_is_wall(map, (int)floor(rx), (int)floor(ry)))
            break;                              // Si impacta con muro, detiene el rayo
    }
    return (dist);                              // Devuelve la distancia de impacto
}


/* -------------------------------------------------------------------------- */
/*  draw_column                                                               */
/*  Objetivo: Dibujar la columna x con una pared centrada de altura wall_h,   */
/*            rellenando techo y suelo con sus colores.                        */
/* -------------------------------------------------------------------------- */
void	draw_column(t_contex *contex, int x, double wall_h, int wall_rgb)
{
    int y_top;                                   // Y inicial de pared
    int y;                                       // Iterador vertical
    int y_bot;                                   // Y final de pared

    if (wall_h > HEIGHT)
        wall_h = HEIGHT;                         // Recorte si excede el alto de ventana
    y_top = (int)((HEIGHT - wall_h) * 0.5);      // Centrado vertical de la pared
    if (y_top < 0) y_top = 0;                    // No permitir negativos
    y_bot = y_top + (int)wall_h;                 // Fin de pared

    y = 0;                                       // Empieza en el tope de pantalla
    while (y < y_top)
        put_px(&contex->img, x, y++, CEIL_COL);   // Techo (cielo)
    while (y < y_bot)
        put_px(&contex->img, x, y++, wall_rgb);   // Pared (ya sombreada)
    while (y < HEIGHT)
        put_px(&contex->img, x, y++, FLOOR_COL);  // Suelo
}

/* -------------------------------------------------------------------------- */
/*  render_frame                                                              */
/*  Objetivo: Para cada columna de pantalla:                                  */
/*            - Calcular ángulo del rayo con modelo pinhole.                  */
/*            - Medir distancia hasta muro.                                   */
/*            - Corregir fish-eye: corr = dist * cos(rel).                    */
/*            - Proyectar altura: wall_h = TILE_SZ * proj_dist / corr.        */
/*            - Sombrear y dibujar columna.                                   */
/* -------------------------------------------------------------------------- */
void render_frame(t_contex *app)
{
    int     x;                                // Columna actual
    double  ray_ang;                              // Ángulo del rayo para x
    //double  rel;                                  // Ángulo relativo al frente de la cámara
    //double  dist;                                 // Distancia sin corregir
    //double  corr;                                 // Distancia corregida (anti fish-eye)
    //double  wall_h;                               // Altura proyectada en píxeles
    double  shade;                                // Factor de sombreado [0.2..1]

    x = 0;
    while (x < WIDTH)
    {
        // Pinhole: ángulo relativo = atan((x - WIDTH/2) / proj_dist)
        ray_ang = app->pl->dir + atan(((double)x - (WIDTH / 2.0)) / app->proj_dist);

        app->pl->dist = cast_ray(ray_ang, app->pl, app->map_g);       // Distancia a primer muro

        app->pl->rel  = ray_ang - app->pl->dir;             // Diferencia angular respecto al frente
        app->pl->corr = app->pl->dist * cos(app->pl->rel);                    // Distancia corregida (proyección ortogonal)

        app->pl->wall_h = (TILE_SZ * app->proj_dist) / (app->pl->corr + EPS); // Altura proyectada estable

        shade = shade_from_dist(app->pl->corr);             // Luz decreciente con distancia
        draw_column(app, x, app->pl->wall_h, mul_color_rgb(WALL_COL, shade)); // Dibuja columna
        x++;                                       // Siguiente columna
    }
}

/* -------------------------------------------------------------------------- */
/*  loop_hook                                                                 */
/*  Objetivo: Función de refresco por frame. Dibuja el frame y lo blittea     */
/*            a la ventana.                                                    */
/* -------------------------------------------------------------------------- */
int loop_hook(t_contex *app)
{
    render_frame(app);                              // Rellena el framebuffer con la escena
    mlx_put_image_to_window(app->mlx,               // Blit a la ventana en (0,0)
                            app->win, app->img.ptr, 0, 0);
    return (0);                                     // Continuar el loop
}


