/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 21:20:22 by yuliano           #+#    #+#             */
/*   Updated: 2025/11/18 06:38:12 by yuliano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"
#include "cub3D.h"


void	ft_free_contex(t_contex **context)
{
	if((*context)->pl)
		free((*context)->pl);
	if ((*context)->tex_nort)
		free((*context)->tex_nort);
	if ((*context)->tex_so)
		free((*context)->tex_so);
	if ((*context)->tex_we)
		free((*context)->tex_we);
	if((*context)->tex_ea)
		free((*context)->tex_ea);
	if ((*context)->img)
		free((*context)->img);
	if(*context)
		free(context);
}


void init_contex(t_contex **contex)
{
	t_player	*pl;
	t_img		*tex_nort;
	t_img		*tex_so;
	t_img		*tex_we;
	t_img		*tex_ea;
	t_img		*img;
	t_img		*text;
	
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
	tex_nort =malloc(sizeof(t_img));
	if (!tex_nort)
	{
		ft_free_contex(contex);
		ft_error("ERROR\n");
	}
	(*contex)->tex_nort = tex_nort;
	tex_so = malloc(sizeof(t_img));
	if (!tex_so)
	{
		ft_free_contex(contex);
		ft_error("ERROR\n");
	}
	(*contex)->tex_so = tex_so;
	tex_we = malloc(sizeof(t_img));
	if (!tex_we)
	{
		ft_free_contex(contex);
		ft_error("ERROR\n");
	}
	(*contex)->tex_we = tex_we;
	tex_ea = malloc(sizeof(t_img));
	if (!tex_ea)
	{
		ft_free_contex(contex);
		ft_error("ERROR\n");
	}
	(*contex)->tex_ea = tex_ea;
	text = malloc(sizeof(t_img));
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


	contex->tex_nort->ptr = mlx_xpm_file_to_image(contex->mlx, "textures/north.xpm",
                                             &contex->tex_nort->width,
                                             &contex->tex_nort->height);
	contex->tex_nort->addr = mlx_get_data_addr(contex->tex_nort->ptr,
                 &contex->tex_nort->bpp,
                 &contex->tex_nort->line_len,
                 &contex->tex_nort->endian);
	

	contex->tex_so->ptr = mlx_xpm_file_to_image(contex->mlx, "textures/blue_wall.xpm",
                                             &contex->tex_so->width,
                                             &contex->tex_so->height);
	contex->tex_so->addr = mlx_get_data_addr(contex->tex_so->ptr,
                 &contex->tex_so->bpp,
                 &contex->tex_so->line_len,
                 &contex->tex_so->endian);

	contex->tex_we->ptr = mlx_xpm_file_to_image(contex->mlx, "textures/gray_wall.xpm",
                                             &contex->tex_we->width,
                                             &contex->tex_we->height);
	contex->tex_we->addr = mlx_get_data_addr(contex->tex_we->ptr,
                 &contex->tex_we->bpp,
                 &contex->tex_we->line_len,
                 &contex->tex_we->endian);
				 
	
	contex->tex_ea->ptr = mlx_xpm_file_to_image(contex->mlx, "textures/rock.xpm",
                                             &contex->tex_ea->width,
                                             &contex->tex_ea->height);
	contex->tex_ea->addr = mlx_get_data_addr(contex->tex_ea->ptr,
                 &contex->tex_ea->bpp,
                 &contex->tex_ea->line_len,
                 &contex->tex_ea->endian);




				 

    find_player(contex->pl, contex->map_g);                           // Localiza 'p' en el mapa y centra jugador
    contex->proj_dist = (WIDTH / 2.0) / tan(FOV_RAD / 2.0); // Distancia al plano de proyección

    mlx_loop_hook(contex->mlx, &loop_hook, contex);      // Hook de render por frame
	// Gancho de teclado: llama a handle_keypress cuando se pulsa una tecla.
	mlx_key_hook(contex->win, handle_keypress, (void *)contex);
    mlx_loop(contex->mlx);                             // Bucle de eventos MLX
    return (0);                                    // Fin (normalmente no se alcanza)
	
	}