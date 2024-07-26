/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 07:52:24 by user              #+#    #+#             */
/*   Updated: 2024/07/26 08:08:44 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
void	game(t_cub3d *map)
{
	mlx_do_key_autorepeaton(map->mlx);
	mlx_hook(map->mlx_win, 2, 1L << 0, key_hook, map);
	mlx_hook(map->mlx_win, 6, 1L << 6, (int (*)())mouse_move, map); <-------------------
	mlx_hook(map->mlx_win, 17, (1L << 2), free_all, map);
	mlx_loop_hook(map->mlx, animation_loop, map);
	create_frame(map);
	mlx_loop(map->mlx);
}
*/

int	mouse_move(int x, int y, t_cub3d *map)
{
	static int	prev_x = -1;

	(void)y;
	if (prev_x == -1)
		prev_x = x;
	map->player.ori = correct_angle(map->player.ori + (x - prev_x) * MOUSE_SENSITIVITY);
	prev_x = x;
	mlx_destroy_image(map->mlx, map->mlx_img.img);
	create_frame(map);
	return (0);
}