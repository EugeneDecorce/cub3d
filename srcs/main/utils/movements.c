/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdias-ba <rdias-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:31:52 by rdias-ba          #+#    #+#             */
/*   Updated: 2024/07/16 15:55:44 by rdias-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_pos(t_cub3d *map, int new_x, int new_y)
{
	if (is_blocking_up(map, new_x, new_y))
		return (1);
	if (is_blocking_down(map, new_x, new_y))
		return (1);
	if (is_blocking_right(map, new_x, new_y))
		return (1);
	if (is_blocking_left(map, new_x, new_y))
		return (1);
	return (0);
}

/* fonctions de mouvement
 * sin() composante y du déplacement
 * cos() composante x du déplacement
 * map->player.ori + PI / 2, orientation de la pov de 90° pour right et left
 */

void	move_forward(t_cub3d *map)
{
	double	new_x;
	double	new_y;

	new_x = map->player.map_pos.x + cos(map->player.ori) * SPEED;
	new_y = map->player.map_pos.y + sin(map->player.ori) * SPEED;
	if (!is_valid_pos(map, new_x, new_y))
	{
		map->player.map_pos.x = new_x;
		map->player.map_pos.y = new_y;
		mlx_destroy_image(map->mlx, map->mlx_img.img);
		create_frame(map);
	}
}

void	move_backward(t_cub3d *map)
{
	double	new_x;
	double	new_y;

	new_x = map->player.map_pos.x - cos(map->player.ori) * SPEED;
	new_y = map->player.map_pos.y - sin(map->player.ori) * SPEED;
	if (!is_valid_pos(map, new_x, new_y))
	{
		map->player.map_pos.x = new_x;
		map->player.map_pos.y = new_y;
		mlx_destroy_image(map->mlx, map->mlx_img.img);
		create_frame(map);
	}
}

void	move_right(t_cub3d *map)
{
	double	new_x;
	double	new_y;

	new_x = map->player.map_pos.x + cos(map->player.ori + PI / 2) * SPEED;
	new_y = map->player.map_pos.y + sin(map->player.ori + PI / 2) * SPEED;
	if (!is_valid_pos(map, new_x, new_y))
	{
		map->player.map_pos.x = new_x;
		map->player.map_pos.y = new_y;
		mlx_destroy_image(map->mlx, map->mlx_img.img);
		create_frame(map);
	}
}

void	move_left(t_cub3d *map)
{
	double	new_x;
	double	new_y;

	new_x = map->player.map_pos.x - cos(map->player.ori + PI / 2) * SPEED;
	new_y = map->player.map_pos.y - sin(map->player.ori + PI / 2) * SPEED;
	if (!is_valid_pos(map, new_x, new_y))
	{
		map->player.map_pos.x = new_x;
		map->player.map_pos.y = new_y;
		mlx_destroy_image(map->mlx, map->mlx_img.img);
		create_frame(map);
	}
}
