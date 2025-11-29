/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

typedef struct s_ray
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	delta_x;
	double	delta_y;
	double	side_x;
	double	side_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
}	t_ray;

static void	init_ray(t_ray *r, double ax, t_player *pl)
{
	r->pos_x = pl->x;
	r->pos_y = pl->y;
	r->dir_x = cos(ax);
	r->dir_y = sin(ax);
	r->map_x = (int)r->pos_x;
	r->map_y = (int)r->pos_y;
	if (r->dir_x == 0)
		r->delta_x = 1e30;
	else
		r->delta_x = fabs(1.0 / r->dir_x);
	if (r->dir_y == 0)
		r->delta_y = 1e30;
	else
		r->delta_y = fabs(1.0 / r->dir_y);
}

static void	calc_step_dist(t_ray *r)
{
	if (r->dir_x < 0)
	{
		r->step_x = -1;
		r->side_x = (r->pos_x - r->map_x) * r->delta_x;
	}
	else
	{
		r->step_x = 1;
		r->side_x = ((r->map_x + 1.0) - r->pos_x) * r->delta_x;
	}
	if (r->dir_y < 0)
	{
		r->step_y = -1;
		r->side_y = (r->pos_y - r->map_y) * r->delta_y;
	}
	else
	{
		r->step_y = 1;
		r->side_y = ((r->map_y + 1.0) - r->pos_y) * r->delta_y;
	}
}

static void	perform_dda(t_ray *r, t_map *map)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (r->side_x < r->side_y)
		{
			r->side_x += r->delta_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_y += r->delta_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (map_is_wall(map, r->map_x, r->map_y))
			hit = 1;
	}
}

static void	set_face(t_player *pl, t_ray *r)
{
	if (r->side == 0)
	{
		if (r->dir_x > 0)
			pl->face = FACE_WE;
		else
			pl->face = FACE_EA;
	}
	else
	{
		if (r->dir_y > 0)
			pl->face = FACE_NO;
		else
			pl->face = FACE_SO;
	}
}

double	cast_ray(double ax, t_contex *contex)
{
	t_ray	r;
	double	dist;

	init_ray(&r, ax, contex->pl);
	calc_step_dist(&r);
	perform_dda(&r, contex->map_g);
	if (r.side == 0)
		dist = (r.map_x - r.pos_x + (1 - r.step_x) / 2.0) / r.dir_x;
	else
		dist = (r.map_y - r.pos_y + (1 - r.step_y) / 2.0) / r.dir_y;
	contex->pl->hit_x = r.pos_x + r.dir_x * dist;
	contex->pl->hit_y = r.pos_y + r.dir_y * dist;
	set_face(contex->pl, &r);
	return (dist);
}
