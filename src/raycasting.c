/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 19:24:37 by yuliano           #+#    #+#             */
/*   Updated: 2025/11/18 21:02:21 by yuliano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* -------------------------------------------------------------------------- */
/*  cast_ray                                                                  */
/*  Objetivo: Lanzar un rayo con ángulo 'ax' desde la posición del jugador,   */
/*            avanzando en pasos 'STEP' hasta colisionar con un muro.         */
/*            Devuelve la distancia recorrida en unidades de mundo.           */
/* -------------------------------------------------------------------------- */
double  cast_ray(double ax, t_player *pl, t_map *map)
{
    double  rx;
    double  ry;
    double  prev_rx;
    double  prev_ry;
    double  dirx;
    double  diry;
    double  dist;
    int     mx;
    int     my;
    int     pmx;
    int     pmy;

    rx = pl->x;
    ry = pl->y;
    dirx = cos(ax);
    diry = sin(ax);
    dist = 0.0;
    pmx = (int)floor(rx);
    pmy = (int)floor(ry);
    while (dist < 64.0)
    {
        prev_rx = rx;
        prev_ry = ry;
        rx += dirx * STEP;
        ry += diry * STEP;
        dist += STEP;
        mx = (int)floor(rx);
        my = (int)floor(ry);
        if (map_is_wall(map, mx, my))
        {
            pl->hit_x = prev_rx;
            pl->hit_y = prev_ry;
            if (mx != pmx && my == pmy)
            {
                if (mx > pmx)
                    pl->face = FACE_WE;  /* venías desde la izquierda */
                else
                    pl->face = FACE_EA;  /* venías desde la derecha  */
            }
            else if (my != pmy && mx == pmx)
            {
                if (my > pmy)
                    pl->face = FACE_NO;  /* venías desde arriba      */
                else
                    pl->face = FACE_SO;  /* venías desde abajo       */
            }
            else
                pl->face = FACE_NO;      /* caso raro (esquina)     */
            break ;
        }
        pmx = mx;
        pmy = my;
    }
    return (dist);
}


/* -------------------------------------------------------------------------- */
/*  draw_column                                                               */
/*  Objetivo: Dibujar la columna x con una pared centrada de altura wall_h,   */
/*            rellenando techo y suelo con sus colores.                        */
/* -------------------------------------------------------------------------- */
void    draw_column(t_contex *contex, int x)
{
    int     y_top;
    int     y_bot;
    int     y;
    int     tex_x;
    int     tex_y;
    double  rel;
    int     color;
    double  wall_h;

    wall_h = contex->pl->wall_h;
    if (wall_h > HEIGHT)
        wall_h = HEIGHT;
    y_top = (int)((HEIGHT - wall_h) * 0.5);
    if (y_top < 0)
        y_top = 0;
    y_bot = y_top + (int)wall_h;
    if (y_bot > HEIGHT)
        y_bot = HEIGHT;
    y = 0;
    while (y < y_top)
        put_px(contex->img, x, y++, CEIL_COL);
    tex_x = (int)(contex->pl->tex_x_rel * contex->selec_text.width);
    if (tex_x < 0)
        tex_x = 0;
    if (tex_x >= contex->selec_text.width)
        tex_x = contex->selec_text.width - 1;
    while (y < y_bot)
    {
        rel = (double)(y - y_top) / wall_h;
        tex_y = (int)(rel * contex->selec_text.height);
        if (tex_y < 0)
            tex_y = 0;
        if (tex_y >= contex->selec_text.height)
            tex_y = contex->selec_text.height - 1;
        color = get_tex_color(&contex->selec_text, tex_x, tex_y);
        color = apply_shade(color, contex->pl->shade);
        put_px(contex->img, x, y, color);
        y++;
    }
    while (y < HEIGHT)
        put_px(contex->img, x, y++, FLOOR_COL);
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
void    render_frame(t_contex *contex)
{
    int     x;
    double  ray_ang;
    double  cell_x;
    double  cell_y;
    double  wall_x;

    x = 0;
    while (x < WIDTH)
    {
        ray_ang = contex->pl->dir
            + atan(((double)x - (WIDTH / 2.0)) / contex->proj_dist);

        contex->pl->dist = cast_ray(ray_ang, contex->pl, contex->map_g);

        contex->pl->rel = ray_ang - contex->pl->dir;
        contex->pl->corr = contex->pl->dist * cos(contex->pl->rel);
        contex->pl->wall_h = (TILE_SZ * contex->proj_dist)
            / (contex->pl->corr + EPS);

        cell_x = contex->pl->hit_x - floor(contex->pl->hit_x);
        cell_y = contex->pl->hit_y - floor(contex->pl->hit_y);

        /* 
        Si la cara es EA o WE → pared vertical → se recorre en Y (cell_y)
        Si la cara es NO o SO → pared horizontal → se recorre en X (cell_x)
        */
        if (contex->pl->face == FACE_EA || contex->pl->face == FACE_WE)
            wall_x = cell_y;
        else
            wall_x = cell_x;

        contex->pl->tex_x_rel = wall_x;

        /* seleccionar textura según face */
        contex->selec_text = contex->text[contex->pl->face];

        contex->pl->shade = shade_from_dist(contex->pl->corr);
        draw_column(contex, x);
        x++;
    }
}


/* -------------------------------------------------------------------------- */
/*  loop_hook                                                                 */
/*  Objetivo: Función de refresco por frame. Dibuja el frame y lo blittea     */
/*            a la ventana.                                                    */
/* -------------------------------------------------------------------------- */
int loop_hook(t_contex *contex)
{
    render_frame(contex);                              // Rellena el framebuffer con la escena
    mlx_put_image_to_window(contex->mlx,               // Blit a la ventana en (0,0)
                            contex->win, contex->img->ptr, 0, 0);
    return (0);                                     // Continuar el loop
}