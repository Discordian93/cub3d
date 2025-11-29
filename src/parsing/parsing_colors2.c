/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colors2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	parse_color_line(const char *line, int *color, int *flag)
{
	char	*trimmed;
	int		result;

	if (*flag)
	{
		ft_putstr_fd("Error\nDuplicate color\n", 2);
		return (0);
	}
	while (*line && ft_isspace(*line))
		line++;
	trimmed = ft_strtrim(line, " \t\n\r");
	if (!trimmed)
		return (0);
	result = parse_color(trimmed);
	free(trimmed);
	if (result == -1)
		return (0);
	*color = result;
	*flag = 1;
	return (1);
}
