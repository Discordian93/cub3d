/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 19:24:37 by yuliano           #+#    #+#             */
/*   Updated: 2025/11/22 18:08:18 by yuliano          ###   ########.fr       */
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
    double  dx;         // CAMBIO: desplazamiento del segmento [prev -> actual]
    double  dy;         // CAMBIO: desplazamiento del segmento [prev -> actual]
    double  t_x;        // CAMBIO: factor de intersección con borde vertical
    double  t_y;        // CAMBIO: factor de intersección con borde horizontal
    double  bx;         // CAMBIO: x del borde vertical donde se cruza
    double  by;         // CAMBIO: y del borde horizontal donde se cruza
    double  hit_step;   // CAMBIO: cuánto del STEP realmente recorremos hasta el muro

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
            /* ------------------------------------------------------------------
            ** ANTES:
            ** pl->hit_x = prev_rx;
            ** pl->hit_y = prev_ry;
            ** if (mx != pmx && my == pmy) { ... } else if (my != pmy && mx == pmx) { ... }
            ** else pl->face = FACE_NO;
            **
            ** Problema:
            ** - Tomabas el punto ANTERIOR al muro, no el punto exacto de impacto.
            ** - En diagonales donde mx y my cambian a la vez, se entraba al "caso raro"
            **   y la cara (FACE_*) podía ser incorrecta.
            ** - Eso hacía que la parte fraccionaria (cell_x/cell_y) fuera incoherente y
            **   se colaran píxeles de otras texturas.
            ** ------------------------------------------------------------------ */

            dx = rx - prev_rx;
            dy = ry - prev_ry;
            t_x = 1e9;
            t_y = 1e9;

            /* CAMBIO: calculamos dónde cruza EXACTAMENTE el borde vertical */
            if (mx != pmx)
            {
                if (dirx > 0)
                    bx = (double)mx;   /* venimos desde la izquierda: borde x = mx   */
                else
                    bx = (double)pmx;  /* venimos desde la derecha: borde x = pmx    */
                t_x = (bx - prev_rx) / dx;   /* factor 0..1 dentro del segmento STEP   */
            }

            /* CAMBIO: calculamos dónde cruza EXACTAMENTE el borde horizontal */
            if (my != pmy)
            {
                if (diry > 0)
                    by = (double)my;   /* venimos desde arriba: borde y = my        */
                else
                    by = (double)pmy;  /* venimos desde abajo: borde y = pmy        */
                t_y = (by - prev_ry) / dy;
            }

            /* CAMBIO: elegimos qué borde se ha cruzado primero (vertical u horizontal) */
            if (t_x < t_y)
            {
                /* Golpe en pared VERTICAL */
                pl->hit_x = bx;
                pl->hit_y = prev_ry + t_x * dy;

                /* Ajustamos la distancia real recorrida dentro del último STEP */
                hit_step = STEP * t_x;
                dist -= STEP;
                dist += hit_step;

                /* Cara: si nos movemos hacia +X, vemos la cara Oeste del bloque. */
                if (dirx > 0)
                    pl->face = FACE_WE;  /* bloque a la derecha, lo vemos por su cara Oeste */
                else
                    pl->face = FACE_EA;  /* bloque a la izquierda, lo vemos por su cara Este */
            }
            else
            {
                /* Golpe en pared HORIZONTAL */
                pl->hit_y = by;
                pl->hit_x = prev_rx + t_y * dx;

                hit_step = STEP * t_y;
                dist -= STEP;
                dist += hit_step;

                /* Cara: si nos movemos hacia +Y, vemos la cara Norte del bloque. */
                if (diry > 0)
                    pl->face = FACE_NO;  /* bloque abajo, lo vemos por su cara Norte */
                else
                    pl->face = FACE_SO;  /* bloque arriba, lo vemos por su cara Sur  */
            }
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
/*            rellenando techo y suelo con sus colores.                       */
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

    /* ----------------------------------------------------------------------
    ** ANTES:
    ** tex_x = (int)(contex->pl->tex_x_rel * contex->selec_text.width);
    ** if (tex_x < 0) tex_x = 0;
    ** if (tex_x >= width) tex_x = width - 1;
    **
    ** Esto está bien siempre que tex_x_rel esté en [0,1).
    ** Tras corregir tex_x_rel en render_frame(), esta parte ya no debería
    ** provocar líneas de sangrado, pero mantenemos el clamp por seguridad.
    ** ---------------------------------------------------------------------- */
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

        /* Parte fraccionaria dentro de la celda donde ha impactado el rayo */
        cell_x = contex->pl->hit_x - floor(contex->pl->hit_x);
        cell_y = contex->pl->hit_y - floor(contex->pl->hit_y);

        /* ------------------------------------------------------------------
        ** ANTES:
        **
        ** if (pl->face == FACE_EA || pl->face == FACE_WE)
        **     wall_x = cell_y;
        ** else
        **     wall_x = cell_x;
        **
        ** Problemas:
        ** - No se invertía wall_x según la cara (N/S/E/O), así que en
        **   algunas transiciones la textura aparecía "del revés", generando
        **   líneas finas en los bordes.
        ** - Si hit_x/hit_y no eran el impacto exacto (bug en cast_ray),
        **   cell_x/cell_y quedaban desfasados y se veían píxeles de otra
        **   textura.
        ** ------------------------------------------------------------------ */

        /* CAMBIO: elegimos la coordenada de textura según la cara golpeada,
        **         invirtiendo cuando toca para que la textura no se vea del revés.
        */
        if (contex->pl->face == FACE_EA)
            wall_x = 1.0 - cell_y;  /* Cara Este: invertimos sentido en Y        */
        else if (contex->pl->face == FACE_WE)
            wall_x = cell_y;        /* Cara Oeste: usamos Y directo              */
        else if (contex->pl->face == FACE_NO)
            wall_x = 1.0 - cell_x;  /* Cara Norte: invertimos sentido en X       */
        else /* FACE_SO */
            wall_x = cell_x;        /* Cara Sur: usamos X directo                */

        /* CAMBIO: aseguramos que wall_x ∈ [0, 1) para evitar tex_x == width   */
        if (wall_x < 0.0)
            wall_x = 0.0;
        if (wall_x >= 1.0)
            wall_x = 1.0;

        contex->pl->tex_x_rel = wall_x;

        /* seleccionar textura según face (esto ya lo tenías bien) */
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