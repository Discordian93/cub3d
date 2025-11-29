/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:10:20 by yuliano           #+#    #+#             */
/*   Updated: 2025/03/11 21:00:37 by yuliano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*next_string(char *read_string)
{
	char	*next_string;
	int		i;
	int		j;

	i = 0;
	while (read_string[i] != '\n' && read_string[i] != '\0')
		i++;
	if (read_string[i] == '\0')
	{
		free(read_string);
		return (NULL);
	}
	next_string = malloc(sizeof(char) * (ft_strlen(read_string) - i + 1));
	if (next_string == NULL)
		return (NULL);
	i++;
	j = 0;
	while (read_string[i] != '\0')
	{
		next_string[j++] = read_string[i++];
	}
	next_string[j] = '\0';
	free(read_string);
	return (next_string);
}

char	*new_line(char *read_string)
{
	char	*line;
	int		i;

	i = 0;
	if (read_string[0] == '\0')
		return (NULL);
	while (read_string[i] != '\n' && read_string[i] != '\0')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (line == NULL)
		return (NULL);
	i = 0;
	while (read_string[i] != '\n' && read_string[i] != '\0')
	{
		line[i] = read_string[i];
		i++;
	}
	if (read_string[i] == '\n')
	{
		line[i] = read_string[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

void	gnl_clear(void)
{
	get_next_line(-42);
}

static int	fill_big_string(int fd, char **big_string)
{
	char	buffer[BUFFER_SIZE + 1];
	int		readbytes;

	readbytes = 1;
	while (!ft_strchr(*big_string, '\n') && readbytes > 0)
	{
		readbytes = read(fd, buffer, BUFFER_SIZE);
		if (readbytes == -1)
			return (-1);
		if (readbytes > 0)
		{
			buffer[readbytes] = '\0';
			*big_string = ft_strjoin_gnl(*big_string, buffer);
			if (*big_string == NULL)
				return (-1);
		}
	}
	return (readbytes);
}

char	*get_next_line(int fd)
{
	static char	*big_string;
	char		*line;
	int			ret;

	if (fd == -42)
	{
		free(big_string);
		big_string = NULL;
		return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ret = fill_big_string(fd, &big_string);
	if (ret == -1 || big_string == NULL)
		return (NULL);
	line = new_line(big_string);
	big_string = next_string(big_string);
	return (line);
}
