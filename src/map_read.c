/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypacileo <ypacileo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 18:15:07 by yuliano           #+#    #+#             */
/*   Updated: 2025/11/09 11:42:28 by ypacileo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_error(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}


void	map_validation(t_map **map, int argc, char **argv)
{
	if (argc != 2)
		ft_error("Error\nUso: ./so_long <mapa.ber>\n");
	*map = (t_map *)malloc(sizeof(t_map));
	if (!(*map))
		ft_error("Error\nFallo de asignación de memoria para el mapa\n");
	(*map)->name = argv[1];
	read_map(*map);
	
}


void	counter_row(t_map *map, char *line, int fd)
{
	if (fd < 0)
	{
		free(map);
		ft_error("Error\nAl abrir el archivo");
	}
	map -> height = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line[0] != '\n' && line[0] != '\0')
			map -> height++;
		free(line);
		line = get_next_line(fd);
	}
	close (fd);
}


void	free_trash(char *line, int fd)
{
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
}

void	read_map(t_map *map)
{
	char	*line;
	int		fd;
	int		i;

	fd = open(map->name, O_RDONLY);
	line = NULL;
	counter_row(map, line, fd);
	fd = open(map->name, O_RDONLY);
	if (fd < 0)
		ft_error("Error\nAl reabrir el archivo\n");
	map->map = (char **)malloc(sizeof(char *) * (map->height + 1));
	if (!map->map)
		ft_error("Error\nFallo de asignación de memoria\n");
	i = 0;
	while (i < map->height)
	{
		line = get_next_line(fd);
		map->map[i] = line;
		i++;
	}
	free_trash(line, fd);
	map->map[i] = NULL;
	close(fd);
}
