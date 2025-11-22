/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 21:20:22 by yuliano           #+#    #+#             */
/*   Updated: 2025/11/22 17:10:37 by yuliano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"
#include "cub3D.h"

void init_contex(t_contex **contex)
{
    *contex = malloc(sizeof(t_contex));
    if (!(*contex))
        ft_error("ERROR\n");

    ft_bzero(*contex, sizeof(t_contex));

    (*contex)->pl = malloc(sizeof(t_player));
    if (!(*contex)->pl)
    {
        ft_free_contex(*contex);
        ft_error("ERROR\n");
    }

    (*contex)->img = malloc(sizeof(t_img));
    if (!(*contex)->img)
    {
        ft_free_contex(*contex);
        ft_error("ERROR\n");
    }
}



/*
** Carga de texturas: si falla algo, limpia y sale.
*/
void	load_text(t_img text[num_tex], t_contex *context)
{
	int	i;

	text[FACE_NO].name = "textures/brick_final.xpm";
	text[FACE_SO].name = "textures/blue_wall.xpm";
	text[FACE_EA].name = "textures/red_wall.xpm";
	text[FACE_WE].name = "textures/gray_wall.xpm";
	i = 0;
	while (i < num_tex)
	{
		text[i].ptr = mlx_xpm_file_to_image(context->mlx,
				text[i].name, &text[i].width, &text[i].height);
		if (text[i].ptr == NULL)
		{
			ft_clean(context);
			ft_error("Error loading texture\n");
		}
		text[i].addr = mlx_get_data_addr(text[i].ptr,
				&text[i].bpp, &text[i].line_len, &text[i].endian);
		if (text[i].addr == NULL)
		{
			ft_clean(context);
			ft_error("Error loading texture\n");
		}
		i++;
	}
}

/*
** Handler para la cruz roja (evento 17 de la MLX).
*/
int	handle_destroy(t_contex *contex)
{
	ft_clean(contex);
	exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_contex	*contex;

	init_contex(&contex);
	map_validation(&contex->map_g, argc, argv);
	contex->map_g->width = 40;
	contex->mlx = mlx_init();
	if (contex->mlx == NULL)
	{
		ft_clean(contex);
		ft_error("Error initializing mlx\n");
	}
	contex->win = mlx_new_window(contex->mlx, WIDTH, HEIGHT, "Cub3D");
	if (contex->win == NULL)
	{
		ft_clean(contex);
		ft_error("Error initializing window\n");
	}
	contex->img->ptr = mlx_new_image(contex->mlx, WIDTH, HEIGHT);
	if (contex->img->ptr == NULL)
	{
		ft_clean(contex);
		ft_error("Error creating image\n");
	}
	contex->img->addr = mlx_get_data_addr(contex->img->ptr,
			&contex->img->bpp,
			&contex->img->line_len,
			&contex->img->endian);
	load_text(contex->text, contex);
	find_player(contex->pl, contex->map_g);
	contex->proj_dist = (WIDTH / 2.0) / tan(FOV_RAD / 2.0);
	mlx_loop_hook(contex->mlx, &loop_hook, contex);
	/* KeyPress o KeyRelease según prefieras */
	mlx_hook(contex->win, 3, 1L << 1, handle_keypress, contex);
	mlx_hook(contex->win, 17, 0, handle_destroy, contex);
	mlx_loop(contex->mlx);
	return (0);
}
