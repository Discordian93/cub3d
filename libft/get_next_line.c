/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*next_string(char *read_string)
{
	char	*next_str;
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
	next_str = malloc(sizeof(char) * (ft_strlen(read_string) - i + 1));
	if (next_str == NULL)
		return (NULL);
	i++;
	j = 0;
	while (read_string[i] != '\0')
		next_str[j++] = read_string[i++];
	next_str[j] = '\0';
	free(read_string);
	return (next_str);
}

static char	*new_line(char *read_string)
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
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*ft_strjoin_gnl(char *end, const char *buffer)
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
	while (end[++i] != '\0')
		str[i] = end[i];
	j = -1;
	while (buffer[++j] != '\0')
		str[i + j] = buffer[j];
	str[i + j] = '\0';
	free(end);
	return (str);
}

static char	*read_file(int fd, char *big_string)
{
	char	buffer[BUFFER_SIZE + 1];
	int		readbytes;

	readbytes = 1;
	while ((!ft_strchr(big_string, '\n')) && readbytes > 0)
	{
		readbytes = read(fd, buffer, BUFFER_SIZE);
		if (readbytes == -1)
			return (NULL);
		if (readbytes > 0)
		{
			buffer[readbytes] = '\0';
			big_string = ft_strjoin_gnl(big_string, buffer);
		}
	}
	return (big_string);
}

char	*get_next_line(int fd)
{
	static char	*big_string;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	big_string = read_file(fd, big_string);
	if (big_string == NULL)
		return (NULL);
	line = new_line(big_string);
	big_string = next_string(big_string);
	return (line);
}
