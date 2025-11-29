/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypacileo <ypacileo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 18:44:58 by ypacileo          #+#    #+#             */
/*   Updated: 2025/11/29 18:45:04 by ypacileo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	destroy_textures(t_contex *contex)
{
	int	i;

	i = 0;
	while (i < NUM_TEX)
	{
		if (contex->text[i].ptr != NULL && contex->mlx != NULL)
		{
			mlx_destroy_image(contex->mlx, contex->text[i].ptr);
			contex->text[i].ptr = NULL;
		}
		i++;
	}
}

static void	destroy_window_display(t_contex *contex)
{
	if (contex->win != NULL && contex->mlx != NULL)
	{
		mlx_destroy_window(contex->mlx, contex->win);
		contex->win = NULL;
	}
	if (contex->mlx != NULL)
	{
		mlx_destroy_display(contex->mlx);
		free(contex->mlx);
		contex->mlx = NULL;
	}
}

int	close_window(t_contex *contex)
{
	if (contex == NULL)
		return (0);
	destroy_textures(contex);
	if (contex->img != NULL && contex->img->ptr != NULL && contex->mlx != NULL)
	{
		mlx_destroy_image(contex->mlx, contex->img->ptr);
		contex->img->ptr = NULL;
	}
	destroy_window_display(contex);
	return (0);
}

void	ft_clean(t_contex *contex)
{
	if (contex == NULL)
		return ;
	close_window(contex);
	ft_free_contex(contex);
}

int	handle_destroy(t_contex *contex)
{
	ft_clean(contex);
	exit(0);
	return (0);
}
