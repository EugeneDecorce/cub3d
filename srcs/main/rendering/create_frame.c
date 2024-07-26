/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 08:40:56 by rdias-ba          #+#    #+#             */
/*   Updated: 2024/07/26 08:08:36 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_image(t_cub3d	*map)
{
	int	i;

	i = 0;
	animation_shading(map);
	while (i < NB_RAYS)
	{
		if (map->frame[i].distance > 0)
		{
			draw_slice(map, map->frame[i], 2 * i);
			draw_slice(map, map->frame[i], 2 * i + 1);
		}
		i++;
	}
}

// Appel du raycasting sur 640 frames en partant de la gauche de notre fov

static void	raycasting(t_cub3d	*map)
{
	int		i;
	double	ray_ori;

	if (map->frame)
		free(map->frame);
	map->frame = malloc(sizeof(t_frame) * NB_RAYS);
	if (!map->frame)
	{
		print_error(ERR_MALLOC, 0);
		free_all(map);
	}
	ray_ori = map->player.ori - (HALF_FOV * DEG_RAD);
	ray_ori = correct_angle(ray_ori);
	i = -1;
	while (++i < NB_RAYS)
	{
		dda(map, ray_ori, &map->frame[i]);
		ray_ori += ANGLE_INCR;
		ray_ori = correct_angle(ray_ori);
	}
}


void create_frame(t_cub3d *map)
{
    map->mlx_img.img = mlx_new_image(map->mlx, WIDTH, HEIGHT);
    if (!map->mlx_img.img)
        free_all(map);
    map->mlx_img.addr = mlx_get_data_addr(map->mlx_img.img, \
        &map->mlx_img.bits_per_pixel, &map->mlx_img.line_length, \
        &map->mlx_img.endian);
    if (!map->mlx_img.addr)
        free_all(map);

    raycasting(map);
    create_image(map);
    draw_minimap(map);  // Draw the minimap
    mlx_put_image_to_window(map->mlx, map->mlx_win, map->mlx_img.img, 0, 0);
}

