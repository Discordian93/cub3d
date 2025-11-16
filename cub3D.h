/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypacileo <ypacileo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:03:53 by ypacileo          #+#    #+#             */
/*   Updated: 2025/11/16 15:57:52 by ypacileo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
#define CUB3D_H

#include <mlx.h>                 // API de MiniLibX: ventanas e imágenes
#include <math.h>                // Trigonometría y constantes (cos, sin, atan, tan, M_PI)
#include <stdlib.h>             // Utilidades estándar
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "libft.h"


# define WIDTH   1200           // Ancho de la ventana en píxeles
# define HEIGHT  800          // Alto de la ventana en píxeles
# define KEY_LEFT   65363
# define KEY_RIGHT  65361
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100


/* ------------------------ Parámetros de proyección ------------------------ */
#define FOV_RAD  (60.0 * (M_PI / 180.0)) // Campo de visión horizontal: 60° en radianes
#define TILE_SZ  1.0             // Altura/escala de una pared en el mundo (1 unidad por celda)
#define STEP     0.02           // Paso de avance incremental para el rayo
#define EPS      1e-9            // Épsilon para evitar divisiones por cero


#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

/* ----------------------------- Colores RGB -------------------------------- */
/* Formato **RGB puro** (0xRRGGBB). 42 exige R, G, B en [0..255].             */
#define CEIL_COL   0xC7E7FF      // Cielo azulado   (R=0xC7, G=0xE7, B=0xFF)
#define FLOOR_COL  0x777777      // Suelo gris      (R=0x77, G=0x77, B=0x77)
#define WALL_COL   0x111111      // Pared base gris muy oscuro

/* --------------------------------- MAPA ----------------------------------- */

typedef struct s_img 
{
    void    *ptr;        // Puntero a la imagen MLX
    char    *addr;       // Dirección de memoria del buffer de píxeles
    int     bpp;         // Bits por píxel (normalmente 32 en MLX Linux)
    int     line_len;    // Bytes por fila (stride)
    int     endian;      // Endianness del buffer
	int     height;
    int     widht;
}   t_img;

typedef struct s_player
{
    double  x;
    double  y;
    double  dir;
    double  dist;
    double  rel;
    double  corr;
    double  wall_h;
    double  hit_x;
    double  hit_y;
    int     side;      // 0 = vertical, 1 = horizontal
    double  tex_rel_x;
}   t_player;

typedef struct s_map
{
    char	*name;
    int		width;
	int		height;
	char	**map;
}	t_map;

typedef struct s_contex 
{
    void        *mlx;       // Contexto MLX
    void        *win;       // Ventana MLX
    t_img       *img;     // Framebuffer donde dibujamos
    t_img       *text;
    t_player    *pl;        // Estado del jugador/cámara
    double      proj_dist; // Distancia al plano de proyección: (WIDTH/2)/tan(FOV/2)
    t_map       *map_g;
    
}   t_contex;

void	counter_row(t_map *map, char *line, int fd);
void	free_trash(char *line, int fd);
void	read_map(t_map *map);
void	put_px(t_img *img, int x, int y, int rgb);
int		pack_rgb(int r, int g, int b);
int		mul_color_rgb(int color, double k);
double shade_from_dist(double corr);
double	degrees_to_radians(double degrees);
double	calc_max_dist(int width, int height);
int		map_is_wall(t_map *map, int mx, int my);
void	find_player(t_player *pl, t_map *map);
double cast_ray(double ax, t_player *pl, t_map *map);
//void	draw_column(t_contex *contex, int x, double wall_h, int wall_rgb);
void	render_frame(t_contex *app);
int		loop_hook(t_contex *app);
int     handle_keypress(int keycode, t_contex *contex);
void	ft_error(const char *msg);
void	map_validation(t_map **map, int argc, char **argv);
void    init_pos_pl(t_player *pl, t_map *map, int y, int x);
int get_tex_color(t_img *tex, int tx, int ty);
void    draw_column(t_contex *contex, int x, double wall_h, double tex_x_rel);
#endif

