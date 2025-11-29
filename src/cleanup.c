/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_error(const char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd((char *)msg, 2);
	exit(EXIT_FAILURE);
}

void	free_config(t_config *config)
{
	if (config == NULL)
		return ;
	if (config->no_texture)
		free(config->no_texture);
	if (config->so_texture)
		free(config->so_texture);
	if (config->ea_texture)
		free(config->ea_texture);
	if (config->we_texture)
		free(config->we_texture);
	free(config);
}

void	free_map(t_map **map)
{
	int	i;

	if (map == NULL || *map == NULL)
		return ;
	if ((*map)->map != NULL)
	{
		i = 0;
		while (i < (*map)->height)
		{
			free((*map)->map[i]);
			i++;
		}
		free((*map)->map);
		(*map)->map = NULL;
	}
	free(*map);
	*map = NULL;
}

void	ft_free_contex(t_contex *context)
{
	if (context == NULL)
		return ;
	if (context->pl != NULL)
	{
		free(context->pl);
		context->pl = NULL;
	}
	if (context->img != NULL)
	{
		free(context->img);
		context->img = NULL;
	}
	if (context->config != NULL)
		free_config(context->config);
	context->config = NULL;
	if (context->map_g != NULL)
		free_map(&context->map_g);
	free(context);
}
