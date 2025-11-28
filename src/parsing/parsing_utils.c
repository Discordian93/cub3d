/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

void	init_mapdata(t_mapdata *data)
{
	data->tex.north = NULL;
	data->tex.south = NULL;
	data->tex.east = NULL;
	data->tex.west = NULL;
	data->floor.r = 0;
	data->floor.g = 0;
	data->floor.b = 0;
	data->floor.is_set = 0;
	data->ceiling.r = 0;
	data->ceiling.g = 0;
	data->ceiling.b = 0;
	data->ceiling.is_set = 0;
	data->map = NULL;
	data->map_width = 0;
	data->map_height = 0;
	data->spawn.x = -1;
	data->spawn.y = -1;
	data->spawn.dir = 0;
	data->spawn.found = 0;
}

int	is_empty_line(char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	parse_error(const char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd((char *)msg, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

char	*ft_strtrim_space(char *str)
{
	char	*start;
	char	*end;

	if (!str)
		return (NULL);
	start = str;
	while (*start == ' ' || *start == '\t')
		start++;
	if (*start == '\0')
		return (start);
	end = start + ft_strlen(start) - 1;
	while (end > start && (*end == ' ' || *end == '\t' || *end == '\n'))
		end--;
	*(end + 1) = '\0';
	return (start);
}
