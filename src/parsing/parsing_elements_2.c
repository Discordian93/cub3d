/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_elements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esteizag <esteizag@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 18:44:28 by esteizag          #+#    #+#             */
/*   Updated: 2025/11/29 18:44:31 by esteizag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	handle_map_start(char *line, t_mapdata *data)
{
	int	cap;

	cap = 16;
	data->lines = malloc(sizeof(char *) * cap);
	if (!data->lines)
		return (0);
	return (add_map_line(data, line, &cap));
}
