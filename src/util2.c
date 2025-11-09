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

/*
** grados_a_radianes
** Objetivo: Convertir grados a radianes.
*/
double	degrees_to_radians(double degrees)
{
    return degrees * (M_PI / 180.0);
}


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

int is_there_a_player(t_map *map, int y, int x)
{
    if (map->map[y][x] == 'E' || map->map[y][x] == 'N' \
        || map->map[y][x] == 'W' || map->map[y][x] == 'S')
        return (1);
    else
        return (0);
}

void    init_pos_pl(t_player *pl, t_map *map, int y, int x)
{
    if (map->map[y][x] == 'E')
        pl->dir = degrees_to_radians(0);
    else if (map->map[y][x] == 'N')
        pl->dir = degrees_to_radians(90);
    else if (map->map[y][x] == 'W')
        pl->dir = degrees_to_radians(180);
    else if (map->map[y][x] == 'S')
        pl->dir = degrees_to_radians(270);
    
    pl->y = y + 0.5;
    pl->x = x + 0.5;
	pl->corr = 0.0;
	pl->dir = 0.0;
	pl->rel = 0.0;
}

/* -------------------------------------------------------------------------- */
/*  find_player                                                               */
/*  Objetivo: Localizar 'p' en el mapa y posicionar al jugador en el centro   */
/*            de esa celda, mirando al Este (dir=0).                           */
/* -------------------------------------------------------------------------- */
void find_player(t_player *pl, t_map *map)
{
    int y;                                  // Iterador filas
    int x;                                      // Iterador columnas

    y = 0;
    while (y < map->height)
    {
        x = 0;                                  // Reinicia columnas en cada fila
        while (x < map->width)
        {
            if (is_there_a_player(map, y, x))             // ¿Encontramos la 'p'?
            {
                init_pos_pl(pl,map, y, x);
                return ;                          // Termina al ubicar al jugador
            }
            x++;                                // Siguiente columna
        }
        y++;                                    // Siguiente fila
    }
}


void	mover_player(t_player *pl, t_map *map, int cord_y, int cord_x)
{
	int aux_x;
	int aux_y;

	aux_x = (int)pl->x;
	aux_y = (int)pl->y;

	if (cord_y == -1 && cord_x == 0)
	{
		map->map[aux_y][aux_x] = '0';
		pl->y += cord_y;
		pl->x += cord_x;
	}
	else if (cord_y == 1 && cord_x == 0)
	{
		map->map[aux_y][aux_x] = '0';
		pl->y += cord_y;
		pl->x += cord_x;
	}
	else if (cord_y == 0 && cord_x == 1)
	{
		map->map[aux_y][aux_x] = '0';
		pl->y += cord_y;
		pl->x += cord_x;
	}
	else if (cord_y == 0 && cord_x == -1)
	{
		map->map[aux_y][aux_x] = '0';
		pl->y += cord_y;
		pl->x += cord_x;
	}
}



int handle_keypress(int keycode, t_contex *contex)
{
    if (keycode == KEY_ESC)
    {
        mlx_loop_end(contex->mlx);
        exit(0);
    }
    else if(keycode == KEY_LEFT)
    {
        contex->pl->dir = (contex->pl->dir + 0.05) % 2.0*M_PI;
		printf("valores en radianes %f\n", contex->pl->dir);
    }
    else if(keycode == KEY_RIGHT)
    {
        contex->pl->dir -= 0.05 *2*M_PI;
		printf("valores en radianes %f\n", contex->pl->dir);
    }
	else if(keycode == KEY_W)
	{
		mover_player(contex->pl, contex->map_g, 0, 1);
	}
	else if(keycode == KEY_S)
	{
		mover_player(contex->pl, contex->map_g, 0, -1);
	}
    else if(keycode == KEY_A)
	{
		mover_player(contex->pl, contex->map_g, -1, 0);
	}
	else if(keycode == KEY_D)
	{
		mover_player(contex->pl, contex->map_g, 1, 0);
	}
    return (0);
}
