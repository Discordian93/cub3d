/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esteizag <esteizag@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 18:44:28 by esteizag          #+#    #+#             */
/*   Updated: 2025/11/29 18:44:31 by esteizag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	open_cub_file(const char *filename)
{
	int		fd;
	size_t	len;

	len = ft_strlen(filename);
	if (len < 5 || ft_strncmp(filename + len - 4, ".cub", 4) != 0
		|| !ft_strchr(filename, '.')
		|| ft_strlen(ft_strchr(filename, '.')) != 4)
	{
		ft_putstr_fd("Error\nInvalid file extension\n", 2);
		exit(EXIT_FAILURE);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nCannot open file\n", 2);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

static void	init_parse_ctx(t_parse_ctx *p, t_contex *ctx, t_mapdata *d, int fd)
{
	p->ctx = ctx;
	p->data = d;
	p->line = NULL;
	p->fd = fd;
}

static int	parse_loop(int fd, t_contex *ctx, t_mapdata *d, int *state)
{
	char		*line;
	int			cap;
	int			found_empty;
	t_parse_ctx	p;

	cap = 16;
	found_empty = 0;
	init_parse_ctx(&p, ctx, d, fd);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (*state == 0)
			process_element(line, &p, state);
		else
		{
			if (!process_map_line(d, line, &cap, &found_empty))
				return (free(line), 0);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}

int	parse_elements(int fd, t_contex *contex, t_mapdata *data)
{
	int	state;

	state = 0;
	return (parse_loop(fd, contex, data, &state));
}
