/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 21:16:37 by yuliano           #+#    #+#             */
/*   Updated: 2025/11/19 23:04:58 by yuliano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
** Mensaje de error + salida inmediata.
*/
void	ft_error(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
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

/*
** Libera SOLO la estructura t_contex y sus subestructuras
** reservadas con malloc (pl, img, map_g).
** NO toca nada de MLX (eso lo hace close_window).
*/
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
	if (context->map_g != NULL)
	{
		free_map(&context->map_g);
	}
	free(context);
}

/*
** Destruye todos los recursos de MLX asociados al contexto:
**  - Texturas
**  - Imagen de frame
**  - Ventana
**  - Display + puntero mlx
*/
int	close_window(t_contex *contex)
{
	int	i;

	if (contex == NULL)
		return (0);
	i = 0;
	while (i < num_tex)
	{
		if (contex->text[i].ptr != NULL && contex->mlx != NULL)
		{
			mlx_destroy_image(contex->mlx, contex->text[i].ptr);
			contex->text[i].ptr = NULL;
		}
		i++;
	}
	if (contex->img != NULL && contex->img->ptr != NULL
		&& contex->mlx != NULL)
	{
		mlx_destroy_image(contex->mlx, contex->img->ptr);
		contex->img->ptr = NULL;
	}
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
	return (0);
}

/*
** Limpieza completa:
** 1) Recursos MLX (ventana, imágenes, display, mlx)
** 2) Estructuras de juego (pl, img, map, contex)
** Después de llamar a esto, NO debes volver a usar contex.
*/
void	ft_clean(t_contex *contex)
{
	if (contex == NULL)
		return ;
	close_window(contex);
	ft_free_contex(contex);
}
