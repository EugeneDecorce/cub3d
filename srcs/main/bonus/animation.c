/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 07:50:21 by user              #+#    #+#             */
/*   Updated: 2024/07/26 12:12:49 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/*
In header file, in t_cub3d add:
	int			shade;
	int			shade_dir;


void	game(t_cub3d *map)
{
	mlx_do_key_autorepeaton(map->mlx);
	mlx_hook(map->mlx_win, 2, 1L << 0, key_hook, map);
	mlx_hook(map->mlx_win, 6, 1L << 6, (int (*)())mouse_move, map);
	mlx_hook(map->mlx_win, 17, (1L << 2), free_all, map);
	mlx_loop_hook(map->mlx, animation_loop, map);    <----------------------------
	create_frame(map);
	mlx_loop(map->mlx);
}
	
*/

# include <sys/time.h>

long long	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(int ms)
{
	long int	time;

	time = timestamp();
	while (timestamp() - time < ms)
		usleep(ms / 10);
}

int	animation_loop(t_cub3d *map)
{
	create_frame(map);
	usleep(100000);
	return (0);
}

void	animation_shading(t_cub3d	*map)
{
	if (map->shade == 200)
		map->shade_dir = 0;
	else if (map->shade == 0)
		map->shade_dir = 1;
	if (map->shade_dir)
		map->shade++;
	else
		map->shade--;
}
