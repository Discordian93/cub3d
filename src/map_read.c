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


/*
** map_validation
**
** This function validates the command‑line arguments, reads the map file
** contents into the t_map structure and performs several consistency
** checks:
**
**  1. Exactly one argument must be provided (the path to the .cub file).
**  2. The file must have the ".cub" extension.
**  3. The map is read from disk and the height is determined.
**  4. The longest line determines the map width. All shorter lines are
**     padded with walls ('1') to simplify boundary checks. Trailing
**     newline characters are removed and space characters are converted
**     to walls as required by the subject (spaces are valid map
**     characters and up to us to handle – here they behave like walls).
**  5. Each character of the map is validated: only '0', '1', 'N', 'S',
**     'E' or 'W' are accepted. Exactly one player start (N/S/E/W) must
**     exist. Finally, the outer border of the map must consist solely
**     of walls; if any open space or player start touches the edge the
**     program exits with an error.
**
** On error this function calls ft_error() with an explicit message and
** exits the program. Upon success it leaves the fully initialised map
** in *map for further use.
*/

/*
** Check that the supplied filename ends with the .cub extension.
*/
static int	extension_is_valid(const char *filename)
{
    const char *dot;

    dot = ft_strrchr(filename, '.');
    if (!dot || ft_strncmp(dot, ".cub", 5) != 0)
        return (0);
    return (1);
}

/*
** Pads every row in the map to the same width with walls ('1'). Spaces
** within the original map are also converted to '1' to behave like
** blocking walls. After this function returns, each string in
** map->map has length map->width and can safely be indexed across the
** entire width.
*/
static void	pad_and_sanitize_map(t_map *map)
{
    int i;
    int j;
    size_t len;
    char *row;
    char *new_row;

    /* First pass: compute maximum width and strip trailing newlines */
    i = 0;
    while (i < map->height)
    {
        row = map->map[i];
        len = ft_strlen(row);
        if (len > 0 && row[len - 1] == '\n')
        {
            row[len - 1] = '\0';
            len--;
        }
        if ((int)len > map->width)
            map->width = (int)len;
        i++;
    }
    /* Second pass: allocate new rows padded to map->width */
    i = 0;
    while (i < map->height)
    {
        row = map->map[i];
        len = ft_strlen(row);
        new_row = (char *)malloc((map->width + 1) * sizeof(char));
        if (!new_row)
            ft_error("Error\nFallo de asignación de memoria al ajustar filas del mapa\n");
        j = 0;
        while (j < map->width)
        {
            if (j < (int)len)
            {
                if (row[j] == ' ')
                    new_row[j] = '1';
                else
                    new_row[j] = row[j];
            }
            else
                new_row[j] = '1';
            j++;
        }
        new_row[map->width] = '\0';
        free(row);
        map->map[i] = new_row;
        i++;
    }
}

/*
** Validates that only permitted characters exist in the map and that
** exactly one player start is present. Also verifies that the
** outermost border of the map is fully enclosed by walls.
*/
static void	validate_map_chars(t_map *map)
{
    int y;
    int x;
    int player_count;

    player_count = 0;
    y = 0;
    while (y < map->height)
    {
        x = 0;
        while (x < map->width)
        {
            char c = map->map[y][x];
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
                player_count++;
            else if (c != '0' && c != '1')
                ft_error("Error\nCaracter no permitido en el mapa\n");
            x++;
        }
        y++;
    }
    if (player_count != 1)
        ft_error("Error\nDebe haber exactamente una posicion inicial del jugador\n");
    /* Comprueba que el borde exterior está cerrado por paredes */
    x = 0;
    while (x < map->width)
    {
        if (map->map[0][x] != '1' || map->map[map->height - 1][x] != '1')
            ft_error("Error\nEl mapa no está cerrado por paredes\n");
        x++;
    }
    y = 0;
    while (y < map->height)
    {
        if (map->map[y][0] != '1' || map->map[y][map->width - 1] != '1')
            ft_error("Error\nEl mapa no está cerrado por paredes\n");
        y++;
    }
}

void	map_validation(t_map **map, int argc, char **argv)
{
    if (argc != 2)
        ft_error("Error\nUso: ./cub3D <archivo.cub>\n");
    if (!extension_is_valid(argv[1]))
        ft_error("Error\nEl archivo debe tener extensión .cub\n");
    *map = (t_map *)malloc(sizeof(t_map));
    if (!(*map))
        ft_error("Error\nFallo de asignación de memoria para el mapa\n");
    (*map)->name = argv[1];
    (*map)->height = 0;
    (*map)->width = 0;
    read_map(*map);
    /* Ajusta filas al mismo ancho, convierte espacios en muros y elimina \n */
    pad_and_sanitize_map(*map);
    /* Valida caracteres y fronteras */
    validate_map_chars(*map);
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
