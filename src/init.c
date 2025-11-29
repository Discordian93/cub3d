/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypacileo <ypacileo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 18:45:42 by ypacileo          #+#    #+#             */
/*   Updated: 2025/11/29 18:45:47 by ypacileo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_player(t_contex *contex)
{
	contex->pl = malloc(sizeof(t_player));
	if (!contex->pl)
	{
		ft_free_contex(contex);
		ft_error("Error allocating player\n");
	}
	ft_bzero(contex->pl, sizeof(t_player));
}

static void	init_image(t_contex *contex)
{
	contex->img = malloc(sizeof(t_img));
	if (!contex->img)
	{
		ft_free_contex(contex);
		ft_error("Error allocating image\n");
	}
	ft_bzero(contex->img, sizeof(t_img));
}

static void	init_config(t_contex *contex)
{
	contex->config = malloc(sizeof(t_config));
	if (!contex->config)
	{
		ft_free_contex(contex);
		ft_error("Error allocating config\n");
	}
	ft_bzero(contex->config, sizeof(t_config));
	contex->config->floor_color = -1;
	contex->config->ceil_color = -1;
}

void	init_contex(t_contex **contex)
{
	*contex = malloc(sizeof(t_contex));
	if (!(*contex))
		ft_error("Error allocating context\n");
	ft_bzero(*contex, sizeof(t_contex));
	init_player(*contex);
	init_image(*contex);
	init_config(*contex);
}
