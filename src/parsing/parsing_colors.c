/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

static int	is_valid_number(char *str)
{
	int	i;

	if (!str || *str == '\0')
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	parse_color_component(char *str)
{
	int		value;
	char	*trimmed;

	trimmed = ft_strtrim_space(str);
	if (!is_valid_number(trimmed))
		return (-1);
	if (ft_strlen(trimmed) > 3)
		return (-1);
	value = ft_atoi(trimmed);
	if (value < 0 || value > 255)
		return (-1);
	return (value);
}

static void	free_color_parts(char **parts)
{
	int	i;

	i = 0;
	while (parts[i])
	{
		free(parts[i]);
		i++;
	}
	free(parts);
}

static int	count_parts(char **parts)
{
	int	i;

	i = 0;
	while (parts[i])
		i++;
	return (i);
}

int	parse_color(char *line, t_color *color)
{
	char	**parts;
	int		rgb[3];

	if (color->is_set)
		return (parse_error("Duplicate color definition"));
	parts = ft_split(line, ',');
	if (!parts)
		return (parse_error("Memory allocation failed"));
	if (count_parts(parts) != 3)
		return (free_color_parts(parts),
			parse_error("Color must have 3 components (R,G,B)"));
	rgb[0] = parse_color_component(parts[0]);
	rgb[1] = parse_color_component(parts[1]);
	rgb[2] = parse_color_component(parts[2]);
	free_color_parts(parts);
	if (rgb[0] == -1 || rgb[1] == -1 || rgb[2] == -1)
		return (parse_error("Invalid color value (must be 0-255)"));
	color->r = rgb[0];
	color->g = rgb[1];
	color->b = rgb[2];
	color->is_set = 1;
	return (0);
}
