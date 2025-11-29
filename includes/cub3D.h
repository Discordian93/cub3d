/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft.h"

# define WIDTH   1920
# define HEIGHT  1080
# define KEY_LEFT   65363
# define KEY_RIGHT  65361
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100

# define FOV_DEG 60.0
# define TILE_SZ 1.0
# define EPS 1e-9
# define MOVE_SPEED 0.08

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define FOV_RAD (FOV_DEG * (M_PI / 180.0))

enum e_face
{
	FACE_NO,
	FACE_SO,
	FACE_EA,
	FACE_WE,
	NUM_TEX
};

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		height;
	int		width;
}	t_img;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir;
	double	dist;
	double	corr;
	double	shade;
	double	wall_h;
	double	hit_x;
	double	hit_y;
	double	tex_x_rel;
	int		face;
}	t_player;

typedef struct s_map
{
	char	*name;
	int		width;
	int		height;
	char	**map;
}	t_map;

typedef struct s_config
{
	char	*no_texture;
	char	*so_texture;
	char	*ea_texture;
	char	*we_texture;
	int		floor_color;
	int		ceil_color;
	int		floor_set;
	int		ceil_set;
}	t_config;

typedef struct s_contex
{
	void		*mlx;
	void		*win;
	t_img		*img;
	t_img		text[NUM_TEX];
	t_img		selec_text;
	t_player	*pl;
	double		proj_dist;
	t_map		*map_g;
	t_config	*config;
}	t_contex;

typedef struct s_column
{
	int		y_top;
	int		y_bot;
	double	wall_h_real;
	double	y_top_real;
	int		tex_x;
}	t_column;


typedef struct s_ray
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	delta_x;
	double	delta_y;
	double	side_x;
	double	side_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
}	t_ray;

/* ======================== Raycasting & Rendering ======================== */
double	cast_ray(double ax, t_contex *contex);
void	draw_column(t_contex *contex, int x);
void	render_frame(t_contex *contex);
int		loop_hook(t_contex *contex);

/* ======================== Color & Pixel Functions ======================= */
void	put_px(t_img *img, int x, int y, int rgb);
int		get_tex_color(t_img *tex, int tx, int ty);
double	shade_from_dist(double corr);
int		apply_shade(int color, double shade);

/* ======================== Player & Movement ============================= */
void	find_player(t_player *pl, t_map *map);
void	init_pos_pl(t_player *pl, t_map *map, int y, int x);
int		handle_keypress(int keycode, t_contex *contex);
void	move_player(t_player *pl, t_map *map, double move_x, double move_y);
double	normalize_angle(double angle);
double	degrees_to_radians(double degrees);

/* ======================== Map Utilities ================================= */
int		map_is_wall(t_map *map, int mx, int my);

/* ======================== Initialization ================================ */
void	init_contex(t_contex **contex);
void	load_textures(t_contex *contex);

/* ======================== Cleanup ======================================= */
void	ft_error(const char *msg);
void	free_map(t_map **map);
void	ft_free_contex(t_contex *context);
int		close_window(t_contex *contex);
void	ft_clean(t_contex *contex);
int		handle_destroy(t_contex *contex);
void	free_config(t_config *config);

#endif
