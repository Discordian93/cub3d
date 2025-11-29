/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:35:18 by yuliano           #+#    #+#             */
/*   Updated: 2025/03/11 21:02:58 by yuliano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// esta funcion concatena dos string en una cadena resultante
char	*ft_strjoin_gnl(char	*end, const char	*buffer)
{
	char	*str;
	int		i;
	int		j;

	if (end == NULL)
	{
		end = (char *)malloc(sizeof(char) * 1);
		end[0] = '\0';
	}
	if (!end || !buffer)
		return (NULL);
	str = (char *)malloc(ft_strlen(end) + ft_strlen(buffer) + 1);
	if (str == NULL)
		return (NULL);
	i = -1;
	j = -1;
	while (end[++i] != '\0')
		str[i] = end[i];
	while (buffer[++j] != '\0')
		str[i + j] = buffer[j];
	str[i + j] = '\0';
	free(end);
	return (str);
}
