/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 13:14:33 by yuliano           #+#    #+#             */
/*   Updated: 2025/11/15 13:14:59 by yuliano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


int get_tex_color(t_img *tex, int tx, int ty)
{
    char            *pix;
    unsigned int    color;

    pix = tex->addr + (ty * tex->line_len
        + tx * (tex->bpp / 8));
    color = *(unsigned int *)pix;
    return ((int)color);
}
