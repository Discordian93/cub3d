/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colors2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

static char	*skip_whitespace(char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	return (str);
}

int	try_parse_color(char *line, t_mapdata *data)
{
	char	*content;

	if (line[0] == 'F' && (line[1] == ' ' || line[1] == '\t'))
	{
		content = skip_whitespace(line + 1);
		return (parse_color(content, &data->floor));
	}
	else if (line[0] == 'C' && (line[1] == ' ' || line[1] == '\t'))
	{
		content = skip_whitespace(line + 1);
		return (parse_color(content, &data->ceiling));
	}
	return (-1);
}
