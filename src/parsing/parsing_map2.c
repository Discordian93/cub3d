/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

int	grow_map_array(t_mapdata *data, int *capacity)
{
	char	**new_map;
	int		new_cap;
	int		i;

	new_cap = (*capacity) * 2;
	if (new_cap == 0)
		new_cap = 16;
	new_map = malloc(sizeof(char *) * (new_cap + 1));
	if (!new_map)
		return (1);
	i = 0;
	while (i < data->map_height)
	{
		new_map[i] = data->map[i];
		i++;
	}
	while (i <= new_cap)
		new_map[i++] = NULL;
	free(data->map);
	data->map = new_map;
	*capacity = new_cap;
	return (0);
}

int	process_map_line(t_mapdata *data, char *line, int *cap, int *found_empty)
{
	if (is_empty_line(line))
	{
		*found_empty = 1;
		return (0);
	}
	if (*found_empty)
		return (parse_error("Map must be last (content after map)"));
	if (add_map_line(data, line, cap))
		return (parse_error("Memory allocation failed"));
	return (0);
}
