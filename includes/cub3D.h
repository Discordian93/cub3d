/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
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
# include "parsing.h"

# define WIDTH   800
# define HEIGHT  600

# define KEY_W       119
# define KEY_A       97
# define KEY_S       115
# define KEY_D       100
# define KEY_LEFT    65361
# define KEY_RIGHT   65363
# define KEY_ESC     65307

# define FOV_RAD     1.0471975511965976
# define TILE_SZ     1.0
# define STEP        0.02
# define EPS         1e-9
# define MOVE_SPEED  0.05
# define ROT_SPEED   0.03

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir;
}	t_player;

typedef struct s_textures_img
{
	t_img	north;
	t_img	south;
	t_img	east;
	t_img	west;
}	t_textures_img;

typedef struct s_raycast
{
	double	dist;
	int		side;
	double	wall_x;
}	t_raycast;

typedef struct s_tex_params
{
	double	tex_step;
	double	tex_pos;
	int		tex_y;
	int		color;
}	t_tex_params;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	t_img			frame;
	t_player		player;
	t_mapdata		mapdata;
	t_textures_img	textures;
	int				floor_color;
	int				ceiling_color;
	double			proj_dist;
}	t_game;

int			init_game(t_game *game, char *map_file);
int			load_textures(t_game *game);
void		init_player(t_game *game);
void		render_frame(t_game *game);
void		draw_column(t_game *game, int x, double wall_h, t_raycast *rc);
void		draw_wall_stripe(t_game *game, int x, int *bounds, t_raycast *rc);
double		cast_ray(t_game *game, double angle, t_raycast *rc);
int			get_texture_pixel(t_img *tex, int tex_x, int tex_y);
t_img		*select_texture(t_game *game, int side);
int			handle_keypress(int keycode, t_game *game);
int			handle_close(t_game *game);
int			loop_hook(t_game *game);
void		move_forward(t_game *game);
void		move_backward(t_game *game);
void		strafe_left(t_game *game);
void		strafe_right(t_game *game);
void		rotate_left(t_game *game);
void		rotate_right(t_game *game);
void		put_pixel(t_img *img, int x, int y, int color);
int			rgb_to_int(int r, int g, int b);
int			is_wall(t_game *game, double x, double y);
void		cleanup_game(t_game *game);
void		ft_error_exit(t_game *game, const char *msg);

#endif
