/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypacileo <ypacileo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 19:24:37 by yuliano           #+#    #+#             */
/*   Updated: 2025/11/16 15:53:26 by ypacileo         ###   ########.fr       */
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
    double  rx;      // Posición actual del rayo en X (coordenadas del mundo)
    double  ry;      // Posición actual del rayo en Y (coordenadas del mundo)
    double  prev_rx; // Posición anterior del rayo en X (antes de avanzar un paso)
    double  prev_ry; // Posición anterior del rayo en Y
    double  dirx;    // Dirección del rayo en el eje X (vector normalizado)
    double  diry;    // Dirección del rayo en el eje Y
    double  dist;    // Distancia total recorrida por el rayo
    int     mx;      // Celda actual X en el mapa (entero)
    int     my;      // Celda actual Y en el mapa (entero)
    int     pmx;     // Celda anterior X en el mapa
    int     pmy;     // Celda anterior Y en el mapa

    /* El rayo empieza exactamente en la posición del jugador */
    rx = pl->x;
    ry = pl->y;

    /* Dirección del rayo calculada a partir del ángulo ax */
    dirx = cos(ax);   // cuánto avanza el rayo en X por cada unidad
    diry = sin(ax);   // cuánto avanza el rayo en Y por cada unidad

    dist = 0.0;       // distancia inicial recorrida = 0

    /* Avanza el rayo de forma incremental en pasos pequeños */
    while (dist < 64.0)     // 64 es un límite de seguridad (máxima distancia permitida)
    {
        /* Guardamos la posición anterior antes de avanzar */
        prev_rx = rx;
        prev_ry = ry;

        /* Avanzamos un pequeño paso en la dirección del rayo */
        rx += dirx * STEP;
        ry += diry * STEP;

        /* Sumamos el avance a la distancia total recorrida */
        dist += STEP;

        /* Convertimos la posición del rayo a una celda del mapa */
        mx = (int)floor(rx);
        my = (int)floor(ry);

        /* Si la celda actual es un muro → el rayo impactó */
        if (map_is_wall(map, mx, my))
        {
            /* Calculamos la celda anterior */
            pmx = (int)floor(prev_rx);
            pmy = (int)floor(prev_ry);

            /* Guardamos en el jugador el punto exacto donde impactó el rayo */
            pl->hit_x = rx;
            pl->hit_y = ry;

            /*
            Determinamos si golpeamos un muro vertical u horizontal:

            - Si cambió solo la X (mx ≠ pmx) → cruzamos una pared vertical.
              Significa que el rayo entró al muro por su lado Este/Oeste.
              → side = 0

            - Si cambió solo la Y (my ≠ pmy) → cruzamos una pared horizontal.
              Significa que el rayo entró al muro por su lado Norte/Sur.
              → side = 1

            Nota:
            Esto funciona porque el rayo avanza paso a paso,
            y podemos comparar la celda justo antes del impacto con la celda actual.
            */
            if (mx != pmx && my == pmy)
                pl->side = 0;   // Muro vertical
            else if (my != pmy && mx == pmx)
                pl->side = 1;   // Muro horizontal
            else
                pl->side = 0;   // Caso raro (diagonal mínima) → tratamos como vertical

            break ;   // Detenemos el avance, ya chocamos con algo
        }
    }

    /* Devolvemos la distancia recorrida por el rayo */
    return (dist);
}




/* -------------------------------------------------------------------------- */
/*  draw_column                                                               */
/*  Objetivo: Dibujar la columna x con una pared centrada de altura wall_h,   */
/*            rellenando techo y suelo con sus colores.                        */
/* -------------------------------------------------------------------------- */
void    draw_column(t_contex *contex, int x, double wall_h, double tex_x_rel)
{
    int     y_top;
    int     y_bot;
    int     y;
    int     tex_x;
    int     tex_y;
    double  rel;
    int     color;

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

    /* --------- AQUÍ DIBUJAS LA TEXTURA EN LA PARTE DE LA PARED --------- */
    tex_x = (int)(tex_x_rel * contex->text->widht);
    if (tex_x < 0)
        tex_x = 0;
    if (tex_x >= contex->text->widht);
        tex_x = contex->text->widht - 1;
    while (y < y_bot)
    {
        rel = (double)(y - y_top) / wall_h;
        tex_y = (int)(rel * contex->text->height);
        if (tex_y < 0)
            tex_y = 0;
        if (tex_y >= contex->text->height)
            tex_y = contex->text->height - 1;
        color = get_tex_color(contex->text, tex_x, tex_y);
        put_px(contex->img, x, y, color);
        y++;
    }
    /* ------------------------------------------------------------------- */

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
void    render_frame(t_contex *app)
{
    int     x;            // Columna actual de la ventana (0 → WIDTH-1)
    double  ray_ang;      // Ángulo del rayo asociado a esta columna
    double  shade;        // Factor de sombreado según la distancia
    double  cell_x;       // Parte fraccionaria de la coordenada X del impacto
    double  cell_y;       // Parte fraccionaria de la coordenada Y del impacto
    double  wall_x;       // Coordenada relativa en la pared (0..1)
  
    x = 0;                // Empezamos por la columna 0 de la pantalla

    // Bucle principal: recorre TODA la ventana de izquierda a derecha
    while (x < WIDTH)
    {
        /*
        --------------------------------------------------------------------------
        CÁLCULO DEL ÁNGULO DEL RAYO PARA LA COLUMNA "x"
        --------------------------------------------------------------------------

        ((x - WIDTH/2) / proj_dist)
            → convierte la posición del píxel en pantalla en un ángulo relativo.

        atan(...)
            → obtiene ese ángulo relativo en radianes.

        app->pl->dir
            → dirección absoluta del jugador en el mundo.

        Suma total:
            → ángulo real del rayo dentro del mundo.
        */
        ray_ang = app->pl->dir
            + atan(((double)x - (WIDTH / 2.0)) / app->proj_dist);

        /*
        --------------------------------------------------------------------------
        LANZAMOS EL RAYO
        --------------------------------------------------------------------------
        cast_ray devuelve la distancia cruda del rayo.
        PERO también modifica dentro de app->pl:
            - hit_x, hit_y  → punto exacto donde colisiona con un muro
            - side          → si golpeó un muro vertical u horizontal
        */
        app->pl->dist = cast_ray(ray_ang, app->pl, app->map_g);

        /*
        --------------------------------------------------------------------------
        CORRECCIÓN DEL FISH-EYE
        --------------------------------------------------------------------------

        Diferencia angular respecto al frente del jugador.
        Si el rayo está muy a la izquierda o derecha, esta diferencia es grande.
        */
        app->pl->rel = ray_ang - app->pl->dir;

        /*
        Distancia corregida:
            dist_corregida = dist * cos(rel)
        
        Esto evita que las paredes se vean curvadas o abombadas.
        */
        app->pl->corr = app->pl->dist * cos(app->pl->rel);

        /*
        --------------------------------------------------------------------------
        CÁLCULO DE LA ALTURA DE LA PARED (PROYECCIÓN PERSPECTIVA)
        --------------------------------------------------------------------------

        wall_h = tamaño_real_del_bloque * distancia_del_plano_proyección /
                 distancia_corregida

        Cuanto mayor sea la distancia corregida → pared se ve más pequeña.
        */
        app->pl->wall_h = (TILE_SZ * app->proj_dist)
            / (app->pl->corr + EPS);

        /*
        --------------------------------------------------------------------------
        OBTENER FRACCIÓN DENTRO DE LA CELDA DONDE IMPACTÓ EL RAYO
        --------------------------------------------------------------------------

        hit_x = 7.25 → el impacto está en la celda 7, al 25% dentro de ella.
        hit_y = 4.80 → en la celda 4, al 80% dentro.

        cell_x = parte fraccionaria (0..1).
        cell_y = parte fraccionaria (0..1).
        */
        cell_x = app->pl->hit_x - floor(app->pl->hit_x);
        cell_y = app->pl->hit_y - floor(app->pl->hit_y);

        /*
        --------------------------------------------------------------------------
        SELECCIONAR SI LA TEXTURA SE RECORRE EN X O EN Y
        --------------------------------------------------------------------------

        Si golpeamos un muro VERTICAL (side == 0):
            → el muro es vertical (pared Este/Oeste)
            → su textura se recorre a lo largo del eje Y
            → usamos cell_y

        Si golpeamos un muro HORIZONTAL (side == 1):
            → pared Norte/Sur
            → su textura se recorre a lo largo del eje X
            → usamos cell_x
        */
        if (app->pl->side == 0)
            wall_x = cell_y;  // Muro vertical
        else
            wall_x = cell_x;  // Muro horizontal

        /*
        wall_x ya está en el rango [0..1).
        Es la posición horizontal relativa dentro de la textura.
        */
        app->pl->tex_rel_x = wall_x;

        /*
        --------------------------------------------------------------------------
        CÁLCULO DE SOMBRA SEGÚN DISTANCIA
        --------------------------------------------------------------------------

        shade disminuye a medida que la pared está más lejos.
        */
        //shade = shade_from_dist(app->pl->corr);

        /*
        --------------------------------------------------------------------------
        DIBUJAR LA COLUMNA DE LA PARED EN LA VENTANA
        --------------------------------------------------------------------------

        De momento se usa color plano:
            mul_color_rgb(WALL_COL, shade)

        Más adelante aquí llamarás a draw_column_textured()
        usando tex_x_rel y la textura correspondiente.
        */
        draw_column(app, x,app->pl->wall_h,app->pl->tex_rel_x );

        x++;  // Siguiente columna de pantalla
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
                            app->win, app->img->ptr, 0, 0);
    return (0);                                     // Continuar el loop
}


