/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypacileo <ypacileo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 19:24:37 by yuliano           #+#    #+#             */
/*   Updated: 2025/11/23 18:36:08 by ypacileo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3D.h"

double	cast_ray(double ax, t_contex *contex)
{
	t_player	*pl;
	t_map		*map;
	double		pos_x;
	double		pos_y;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		side_dist_x;
	double		side_dist_y;
	int			step_x;
	int			step_y;
	int			side;
	int			hit;
	double		dist;

	/* Accesos rápidos al player y al mapa desde el contexto */
	pl = contex->pl;
	map = contex->map_g;

	/* Posición inicial del rayo: posición del jugador */
	pos_x = pl->x;
	pos_y = pl->y;

	/* Vector dirección del rayo (a partir del ángulo ax) */
	ray_dir_x = cos(ax);
	ray_dir_y = sin(ax);

	/* Celda del mapa en la que se encuentra el jugador */
	map_x = (int)pos_x;
	map_y = (int)pos_y;

	/* Distancias entre bordes verticales/horizontales del grid (DDA) */
	if (ray_dir_x == 0)
		delta_dist_x = 1e30;
	else
		delta_dist_x = fabs(1.0 / ray_dir_x);
	if (ray_dir_y == 0)
		delta_dist_y = 1e30;
	else
		delta_dist_y = fabs(1.0 / ray_dir_y);

	/* step_x / step_y: sentido en el que avanzamos en el mapa
	   side_dist_x / side_dist_y: distancia hasta la PRIMERA frontera
	   vertical/horizontal desde la posición del jugador */
	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (pos_x - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = ((map_x + 1.0) - pos_x) * delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (pos_y - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = ((map_y + 1.0) - pos_y) * delta_dist_y;
	}

	/* Bucle DDA: avanzamos celda a celda hasta chocar con un muro */
	hit = 0;
	while (!hit)
	{
		/* Elegimos si cruzamos antes una frontera vertical u horizontal */
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1;
		}
		if (map_is_wall(map, map_x, map_y))
			hit = 1;
	}

	/* Distancia perpendicular al muro (fórmula estándar Wolf3D) */
	if (side == 0)
		dist = (map_x - pos_x + (1 - step_x) / 2.0) / ray_dir_x;
	else
		dist = (map_y - pos_y + (1 - step_y) / 2.0) / ray_dir_y;

	/* Punto exacto de impacto en el mundo */
	pl->hit_x = pos_x + ray_dir_x * dist;
	pl->hit_y = pos_y + ray_dir_y * dist;

	/* Seleccionamos qué cara del bloque hemos golpeado (N/S/E/O)
	   Usando la lógica del subject:
	   - side == 0 → muro vertical: miramos ray_dir_x
	   - side == 1 → muro horizontal: miramos ray_dir_y */
	if (side == 0)
	{
		if (ray_dir_x > 0)
			pl->face = FACE_WE; /* rayo hacia +X: bloque a la derecha, cara Oeste */
		else
			pl->face = FACE_EA; /* rayo hacia -X: bloque a la izquierda, cara Este */
	}
	else
	{
		if (ray_dir_y > 0)
			pl->face = FACE_NO; /* rayo hacia +Y: bloque abajo, vemos cara Norte */
		else
			pl->face = FACE_SO; /* rayo hacia -Y: bloque arriba, vemos cara Sur   */
	}
	return (dist);
}

/*
void	draw_column(t_contex *contex, int x)
{
	int		y_top;
	int		y_bot;
	int		y;
	int		tex_x;
	int		tex_y;
	double	rel;
	int		color;
	double	wall_h;

	// Ajustamos altura de pared a la ventana
	wall_h = contex->pl->wall_h;
	if (wall_h > HEIGHT)
		wall_h = HEIGHT;
	y_top = (int)((HEIGHT - wall_h) * 0.5);
	if (y_top < 0)
		y_top = 0;
	y_bot = y_top + (int)wall_h;
	if (y_bot > HEIGHT)
		y_bot = HEIGHT;

	// Techo
	y = 0;
	while (y < y_top)
		put_px(contex->img, x, y++, CEIL_COL);

	// Coordenada X de textura (columna dentro de la textura) 
	tex_x = (int)(contex->pl->tex_x_rel * contex->selec_text.width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= contex->selec_text.width)
		tex_x = contex->selec_text.width - 1;

	// Pared texturada 
	while (y < y_bot)
	{
		// rel: posición relativa dentro de la pared [0..1] 
		rel = (double)(y - y_top) / wall_h;
		tex_y = (int)(rel * contex->selec_text.height);
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= contex->selec_text.height)
			tex_y = contex->selec_text.height - 1;
		color = get_tex_color(&contex->selec_text, tex_x, tex_y);
		color = apply_shade(color, contex->pl->shade);
		put_px(contex->img, x, y++, color);
	}

	// Suelo 
	while (y < HEIGHT)
		put_px(contex->img, x, y++, FLOOR_COL);
}

*/

void	draw_column(t_contex *contex, int x)
{
	int		y_top;
	int		y_bot;
	int		y;
	int		tex_x;
	int		tex_y;
	double	rel;
	int		color;
	//double	wall_h;        /* altura recortada a la ventana      */
	double	wall_h_real;   /* altura proyectada REAL de la pared */
	double	y_top_real;    /* inicio real (puede ser < 0)        */
	double	y_bot_real;    /* final real (puede ser > HEIGHT)    */

	/* Altura REAL de la pared en pantalla (sin recortar) */
	wall_h_real = contex->pl->wall_h;
	if (wall_h_real < 1.0)
		wall_h_real = 1.0;

	/* Posición REAL de inicio y fin (centrado vertical) */
	y_top_real = (HEIGHT - wall_h_real) * 0.5;
	y_bot_real = y_top_real + wall_h_real;

	/* Recorte a la ventana */
	y_top = (int)y_top_real;
	if (y_top < 0)
		y_top = 0;
	y_bot = (int)y_bot_real;
	if (y_bot > HEIGHT)
		y_bot = HEIGHT;

	/* Techo */
	y = 0;
	while (y < y_top)
		put_px(contex->img, x, y++, CEIL_COL);

	/* Coordenada X de textura (columna dentro de la textura) */
	tex_x = (int)(contex->pl->tex_x_rel * contex->selec_text.width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= contex->selec_text.width)
		tex_x = contex->selec_text.width - 1;

	/* Pared texturada */
	while (y < y_bot)
	{
		/*
		** rel: posición relativa dentro de la pared [0..1]
		** IMPORTANTE: usamos y_top_real y wall_h_real (no los recortados)
		*/
		rel = ((double)y - y_top_real) / wall_h_real;
		tex_y = (int)(rel * contex->selec_text.height);
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= contex->selec_text.height)
			tex_y = contex->selec_text.height - 1;
		color = get_tex_color(&contex->selec_text, tex_x, tex_y);
		color = apply_shade(color, contex->pl->shade);
		put_px(contex->img, x, y++, color);
	}

	/* Suelo */
	while (y < HEIGHT)
		put_px(contex->img, x, y++, FLOOR_COL);
}



void	render_frame(t_contex *contex)
{
	int		x;
	double	ray_ang;
	double	cell_x;
	double	cell_y;
	double	wall_x;

	x = 0;
	while (x < WIDTH)
	{
		/* Modelo pinhole: ángulo del rayo para la columna x */
		ray_ang = contex->pl->dir
			+ atan(((double)x - (WIDTH / 2.0)) / contex->proj_dist);

		/* Lanzamos rayo con DDA: devuelve distancia perpendicular
		   y rellena hit_x, hit_y y face en contex->pl */
		contex->pl->dist = cast_ray(ray_ang, contex);

	
		contex->pl->corr = contex->pl->dist * cos(ray_ang - contex->pl->dir);
		contex->pl->wall_h = (TILE_SZ * contex->proj_dist)
			/ (contex->pl->corr + EPS);

		/* Parte fraccionaria de la celda donde impacta el rayo */
		cell_x = contex->pl->hit_x - floor(contex->pl->hit_x);
		cell_y = contex->pl->hit_y - floor(contex->pl->hit_y);

		/* Elegimos coordenada de textura según la cara golpeada,
		   invirtiendo cuando corresponde para que la textura
		   no se vea del revés en N/S/E/O. */
		if (contex->pl->face == FACE_EA)
			wall_x = 1.0 - cell_y;
		else if (contex->pl->face == FACE_WE)
			wall_x = cell_y;
		else if (contex->pl->face == FACE_NO)
			wall_x = 1.0 - cell_x;
		else
			wall_x = cell_x;

		/* Clamp de seguridad a [0,1] */
		if (wall_x < 0.0)
			wall_x = 0.0;
		if (wall_x >= 1.0)
			wall_x = 1.0;

		/* Guardamos la coordenada relativa X de textura en el player */
		contex->pl->tex_x_rel = wall_x;

		/* Seleccionamos la textura según la cara (N/S/E/O) */
		contex->selec_text = contex->text[contex->pl->face];

		/* Sombreado según la distancia */
		contex->pl->shade = shade_from_dist(contex->pl->corr);

		/* Dibujamos la columna completa en la imagen */
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