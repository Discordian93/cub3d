/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypacileo <ypacileo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 21:20:22 by yuliano           #+#    #+#             */
/*   Updated: 2025/11/09 11:42:22 by ypacileo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"
#include "cub3D.h"



void init_contex(t_contex **contex)
{
	*contex = malloc(sizeof(t_contex));
	if(!*contex)
		ft_error("ERROR\n");
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
        return (1); 
	
    contex->win = mlx_new_window(contex->mlx, WIDTH, HEIGHT,
                             "Ray Casting - Cub3D (RGB)"); // Crea ventana
    if (!contex->win)
        return (1);                                 // Error al crear ventana

    contex->img.ptr = mlx_new_image(contex->mlx, WIDTH, HEIGHT); // Crea imagen
    contex->img.addr = mlx_get_data_addr(contex->img.ptr,       // Obtiene buffer crudo
                                       &contex->img.bpp,
                                       &contex->img.line_len,
                                       &contex->img.endian);

    find_player(&contex->pl, contex->map_g);                           // Localiza 'p' en el mapa y centra jugador
    contex->proj_dist = (WIDTH / 2.0) / tan(FOV_RAD / 2.0); // Distancia al plano de proyección

    mlx_loop_hook(contex->mlx, &loop_hook, contex);      // Hook de render por frame
	// Gancho de teclado: llama a handle_keypress cuando se pulsa una tecla.
	mlx_key_hook(contex->win, handle_keypress, (void *)contex);
    mlx_loop(contex->mlx);                             // Bucle de eventos MLX
    return (0);                                    // Fin (normalmente no se alcanza)
	
	}