/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cub3D.h"

typedef struct s_mapdata
{
	char	**lines;
	int		count;
	int		width;
}	t_mapdata;

/* ======================== Main Parsing ================================== */
void	parse_cub_file(const char *filename, t_contex *contex);

/* ======================== File Parsing ================================== */
int		open_cub_file(const char *filename);
int		parse_elements(int fd, t_contex *contex, t_mapdata *data);
void	process_element(char *line, t_contex *ctx, t_mapdata *d, int *state);
int		handle_map_start(char *line, t_mapdata *data);

/* ======================== Element Parsing =============================== */
int		is_element_line(const char *line);
int		parse_element_line(const char *line, t_config *config);

/* ======================== Texture Parsing =============================== */
int		parse_texture(const char *line, char **dest);
int		is_texture_identifier(const char *line);

/* ======================== Color Parsing ================================= */
int		parse_color_line(const char *line, int *color, int *flag);
int		parse_color(const char *str);
int		validate_color_format(const char *str);
int		count_color_parts(char **parts);
void	free_color_parts(char **parts);

/* ======================== Map Parsing =================================== */
void	free_mapdata(t_mapdata *data);
int		is_map_line(const char *line);
int		add_map_line(t_mapdata *data, char *line, int *cap);
int		grow_map_array(t_mapdata *data, int *capacity);
int		process_map_line(t_mapdata *d, char *line, int *cap, int *found);

/* ======================== Map Building ================================== */
void	build_map(t_mapdata *data, t_map *map);
void	copy_map_lines(t_mapdata *data, t_map *map);

/* ======================== Map Validation ================================ */
void	validate_map(t_map *map);
int		validate_characters(t_map *map);
int		check_player(t_map *map, int y, int x, int *player_count);

/* ======================== Wall Validation =============================== */
int		check_map_closed(t_map *map);
int		is_walkable(char c);
int		check_adjacent(t_map *map, int y, int x);
int		is_exposed(t_map *map, int y, int x);

/* ======================== Utilities ===================================== */
char	*ft_strtrim_free(char *s1, const char *set);
int		is_empty_line(const char *line);
void	skip_spaces(const char **str);
int		ft_isspace(char c);
void	parse_error(const char *msg, t_contex *ctx, t_mapdata *data);

#endif