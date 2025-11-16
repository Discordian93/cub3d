/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypacileo <ypacileo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 21:20:22 by yuliano           #+#    #+#             */
/*   Updated: 2025/11/16 12:12:22 by ypacileo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"
#include "cub3D.h"


void	ft_free_contex(t_contex **context)
{
	if((*context)->pl)
		free((*context)->pl);
	if ((*context)->text)
		free((*context)->text);
	if ((*context)->img)
		free((*context)->img);
	if(*context)
		free(context);
}


void init_contex(t_contex **contex)
{
	t_player	*pl;
	t_img		*text;
	t_img		*img;
	
	*contex = malloc(sizeof(t_contex));
	if(!*contex)
		ft_error("ERROR\n");
	pl = malloc(sizeof(t_player));
	if (!pl)
	{
		ft_free_contex(contex);
		ft_error("ERROR\n");
	}
	(*contex)->pl = pl;
	text =malloc(sizeof(t_img));
	if (!text)
	{
		ft_free_contex(contex);
		ft_error("ERROR\n");
	}
	(*contex)->text = text;
	img = malloc(sizeof(t_img));
	if (!img)
	{
		ft_free_contex(contex);
		ft_error("ERROR\n");
	}
	(*contex)->img = img;
	(*contex)->mlx = NULL;
	(*contex)->map_g = NULL;
	(*contex)->win = NULL;
	(*contex)->proj_dist = 0.0;
}



int main(int argc, char **argv)
{
	t_contex *contex;
	int i;
	
	
	init_contex(&contex);
	map_validation(&contex->map_g, argc, argv);
	contex->map_g->width = 40;
	
	contex->mlx = mlx_init();                           // Inicializa MLX
    if (!contex->mlx)
        return (1); // pendiente liberar memoria
	
    contex->win = mlx_new_window(contex->mlx, WIDTH, HEIGHT, \
    							"Cub3D"); // Crea ventana
    if (!contex->win)
        return (1);                                 // Error al crear ventana, pendiente liberar memoria

    contex->img->ptr = mlx_new_image(contex->mlx, WIDTH, HEIGHT); // Crea imagen
    contex->img->addr = mlx_get_data_addr(contex->img->ptr,   // Obtiene buffer crudo
                                       &contex->img->bpp,
                                       &contex->img->line_len,
                                       &contex->img->endian);


	contex->text->ptr = mlx_xpm_file_to_image(contex->mlx, "textures/wall.xpm",
                                             &contex->text->widht,
                                             &contex->text->height);
	contex->text->addr = mlx_get_data_addr(contex->text->ptr,
                 &contex->text->bpp,
                 &contex->text->line_len,
                 &contex->text->endian);


    find_player(contex->pl, contex->map_g);                           // Localiza 'p' en el mapa y centra jugador
    contex->proj_dist = (WIDTH / 2.0) / tan(FOV_RAD / 2.0); // Distancia al plano de proyección

    mlx_loop_hook(contex->mlx, &loop_hook, contex);      // Hook de render por frame
	// Gancho de teclado: llama a handle_keypress cuando se pulsa una tecla.
	mlx_key_hook(contex->win, handle_keypress, (void *)contex);
    mlx_loop(contex->mlx);                             // Bucle de eventos MLX
    return (0);                                    // Fin (normalmente no se alcanza)
	
	}