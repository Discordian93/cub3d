/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
	int		is_set;
}	t_color;

typedef struct s_textures
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
}	t_textures;

typedef struct s_spawn
{
	int		x;
	int		y;
	char	dir;
	int		found;
}	t_spawn;

typedef struct s_mapdata
{
	t_textures	tex;
	t_color		floor;
	t_color		ceiling;
	char		**map;
	int			map_width;
	int			map_height;
	t_spawn		spawn;
}	t_mapdata;

int			parse_cub_file(const char *filename, t_mapdata *data);
int			parse_elements(int fd, t_mapdata *data, char **first_map_line);
int			parse_element_line(char *line, t_mapdata *data);
int			all_elements_set(t_mapdata *data);
int			try_parse_texture(char *line, t_mapdata *data);
int			parse_color(char *line, t_color *color);
int			try_parse_color(char *line, t_mapdata *data);
int			parse_map_lines(int fd, char *first_line, t_mapdata *data);
int			add_map_line(t_mapdata *data, char *line, int *capacity);
int			grow_map_array(t_mapdata *data, int *capacity);
int			process_map_line(t_mapdata *data, char *ln, int *cap, int *empty);
int			validate_map(t_mapdata *data);
int			check_map_closed(t_mapdata *data);
int			validate_characters(t_mapdata *data);
char		*ft_strtrim_space(char *str);
int			is_empty_line(char *line);
int			is_map_line(char *line);
void		free_mapdata(t_mapdata *data);
void		init_mapdata(t_mapdata *data);
int			parse_error(const char *msg);

#endif
