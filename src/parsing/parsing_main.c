/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esteizag <esteizag@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 18:44:28 by esteizag          #+#    #+#             */
/*   Updated: 2025/11/29 18:44:31 by esteizag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	validate_config(t_config *config)
{
	if (!config->no_texture || !config->so_texture
		|| !config->ea_texture || !config->we_texture)
	{
		ft_putstr_fd("Error\nMissing texture path\n", 2);
		exit(EXIT_FAILURE);
	}
	if (!config->floor_set || !config->ceil_set)
	{
		ft_putstr_fd("Error\nMissing floor or ceiling color\n", 2);
		exit(EXIT_FAILURE);
	}
}

static void	init_mapdata(t_mapdata *data)
{
	data->lines = NULL;
	data->count = 0;
	data->width = 0;
}

void	free_mapdata(t_mapdata *data)
{
	int	i;

	if (data->lines)
	{
		i = 0;
		while (i < data->count)
		{
			free(data->lines[i]);
			i++;
		}
		free(data->lines);
	}
}

static void	alloc_map(t_contex *contex, t_mapdata *data)
{
	contex->map_g = malloc(sizeof(t_map));
	if (!contex->map_g)
	{
		free_mapdata(data);
		ft_clean(contex);
		ft_error("Memory allocation failed\n");
	}
	ft_bzero(contex->map_g, sizeof(t_map));
}

void	parse_cub_file(const char *filename, t_contex *contex)
{
	int			fd;
	t_mapdata	data;

	fd = open_cub_file(filename);
	init_mapdata(&data);
	if (!parse_elements(fd, contex, &data))
	{
		free_mapdata(&data);
		close(fd);
		ft_clean(contex);
		ft_error("Failed to parse file\n");
	}
	close(fd);
	validate_config(contex->config);
	alloc_map(contex, &data);
	build_map(&data, contex->map_g);
	free_mapdata(&data);
	validate_map(contex->map_g);
}
