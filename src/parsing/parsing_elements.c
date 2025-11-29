/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esteizag <esteizag@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 18:44:28 by esteizag          #+#    #+#             */
/*   Updated: 2025/11/29 18:44:31 by esteizag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_element_line(const char *line)
{
	while (*line && ft_isspace(*line))
		line++;
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "F ", 2) == 0)
		return (1);
	if (ft_strncmp(line, "C ", 2) == 0)
		return (1);
	return (0);
}

int	parse_element_line(const char *line, t_config *config)
{
	while (*line && ft_isspace(*line))
		line++;
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (parse_texture(line + 3, &config->no_texture));
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (parse_texture(line + 3, &config->so_texture));
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (parse_texture(line + 3, &config->we_texture));
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (parse_texture(line + 3, &config->ea_texture));
	if (ft_strncmp(line, "F ", 2) == 0)
		return (parse_color_line(line + 2, &config->floor_color,
				&config->floor_set));
	if (ft_strncmp(line, "C ", 2) == 0)
		return (parse_color_line(line + 2, &config->ceil_color,
				&config->ceil_set));
	return (0);
}

void	process_element(char *line, t_contex *ctx, t_mapdata *d, int *state)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, " \t\n\r");
	if (!trimmed)
		return ;
	if (ft_strlen(trimmed) == 0)
	{
		free(trimmed);
		return ;
	}
	if (is_element_line(trimmed))
	{
		if (!parse_element_line(trimmed, ctx->config))
		{
			free(trimmed);
			parse_error("Invalid element", ctx, d);
		}
	}
	else if (is_map_line(trimmed))
	{
		*state = 1;
		handle_map_start(line, d);
	}
	else
	{
		free(trimmed);
		parse_error("Unknown element", ctx, d);
	}
	free(trimmed);
}

int	handle_map_start(char *line, t_mapdata *data)
{
	int	cap;

	cap = 16;
	data->lines = malloc(sizeof(char *) * cap);
	if (!data->lines)
		return (0);
	return (add_map_line(data, line, &cap));
}