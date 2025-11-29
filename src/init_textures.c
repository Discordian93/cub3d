/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	load_single_texture(t_contex *contex, int index, char *path)
{
	contex->text[index].ptr = mlx_xpm_file_to_image(contex->mlx,
			path, &contex->text[index].width, &contex->text[index].height);
	if (contex->text[index].ptr == NULL)
		return (0);
	contex->text[index].addr = mlx_get_data_addr(contex->text[index].ptr,
			&contex->text[index].bpp,
			&contex->text[index].line_len,
			&contex->text[index].endian);
	if (contex->text[index].addr == NULL)
		return (0);
	return (1);
}

void	load_textures(t_contex *contex)
{
	if (!load_single_texture(contex, FACE_NO, contex->config->no_texture))
	{
		ft_clean(contex);
		ft_error("Error loading NO texture\n");
	}
	if (!load_single_texture(contex, FACE_SO, contex->config->so_texture))
	{
		ft_clean(contex);
		ft_error("Error loading SO texture\n");
	}
	if (!load_single_texture(contex, FACE_EA, contex->config->ea_texture))
	{
		ft_clean(contex);
		ft_error("Error loading EA texture\n");
	}
	if (!load_single_texture(contex, FACE_WE, contex->config->we_texture))
	{
		ft_clean(contex);
		ft_error("Error loading WE texture\n");
	}
}
