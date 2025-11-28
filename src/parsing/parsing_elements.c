/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_elements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

int	all_elements_set(t_mapdata *data)
{
	if (!data->tex.north || !data->tex.south)
		return (0);
	if (!data->tex.east || !data->tex.west)
		return (0);
	if (!data->floor.is_set || !data->ceiling.is_set)
		return (0);
	return (1);
}

int	parse_element_line(char *line, t_mapdata *data)
{
	char	*trimmed;
	int		result;

	trimmed = ft_strtrim_space(line);
	if (!trimmed || *trimmed == '\0')
		return (0);
	result = try_parse_texture(trimmed, data);
	if (result != -1)
		return (result);
	result = try_parse_color(trimmed, data);
	if (result != -1)
		return (result);
	return (-1);
}
