/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 22:04:41 by yuliano           #+#    #+#             */
/*   Updated: 2025/11/08 22:47:13 by yuliano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* -------------------------------------------------------------------------- */
/*  map_is_wall                                                               */
/*  Objetivo: Indicar si la celda (mx,my) es un muro. Si está fuera del mapa, */
/*            se considera muro para cerrar el mundo.                          */
/* -------------------------------------------------------------------------- */
int map_is_wall(t_map *map, int mx, int my)
{
    if (mx < 0 || mx >= map->width || my < 0 || my >= map->width)
        return (1);                             // Fuera de límites ⇒ muro implícito
    return (map->map[my][mx] == '1');              // '1' representa muro
}

/* -------------------------------------------------------------------------- */
/*  find_player                                                               */
/*  Objetivo: Localizar 'p' en el mapa y posicionar al jugador en el centro   */
/*            de esa celda, mirando al Este (dir=0).                           */
/* -------------------------------------------------------------------------- */
void find_player(t_player *pl, t_map *map)
{
    int y = 0;                                  // Iterador filas
    int x;                                      // Iterador columnas

    while (y < map->height)
    {
        x = 0;                                  // Reinicia columnas en cada fila
        while (x < map->width)
        {
            if (map->map[y][x] == 'E')             // ¿Encontramos la 'p'?
            {
                pl->x = x + 0.5;                // Centro de celda en X
                pl->y = y + 0.5;                // Centro de celda en Y
                pl->dir = 0.0;                  // Mirando al Este
                return;                          // Termina al ubicar al jugador
            }
            x++;                                // Siguiente columna
        }
        y++;                                    // Siguiente fila
    }
    pl->x = 1.5; pl->y = 1.5; pl->dir = 0.0;    // Fallback si no se encontró 'p'
}



int handle_keypress(int keycode, t_contex *contex)
{
    if (keycode == KEY_ESC)
    {
        mlx_loop_end(contex->mlx);
        exit(0);
    }
    else if(keycode == left_arrow)
    {
        contex->pl.dir += 0.05; 
    }
    else if(keycode == right_arrow)
    {
        contex->pl.dir -= 0.05;
    }
    
    return (0);
}
