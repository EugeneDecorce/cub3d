/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_blocking_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdias-ba <rdias-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:31:53 by rdias-ba          #+#    #+#             */
/*   Updated: 2024/06/24 20:51:09 by rdias-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_blocking_down(t_cub3d *map, int new_x, int new_y)
{
	new_x += 16;
	new_y += 16;
	new_x /= CUBE_SIZE;
	new_y /= CUBE_SIZE;
	if (new_x < 0 || new_x >= map->map_width || new_y < 0 || \
		new_y >= map->map_height)
	{
		return (1);
	}
	if (map->map[new_y][new_x] == '1' || map->map[new_y + 1][new_x + 1] == ' ')
		return (1);
	return (0);
}

int	is_blocking_up(t_cub3d *map, int new_x, int new_y)
{
	new_x -= 16;
	new_y -= 16;
	new_x /= CUBE_SIZE;
	new_y /= CUBE_SIZE;
	if (new_x < 0 || new_x >= map->map_width || new_y < 0 || \
		new_y >= map->map_height)
	{
		return (1);
	}
	if (map->map[new_y][new_x] == '1' || map->map[new_y + 1][new_x + 1] == ' ')
		return (1);
	return (0);
}

int	is_blocking_right(t_cub3d *map, int new_x, int new_y)
{
	new_x += 16;
	new_y -= 16;
	new_x /= CUBE_SIZE;
	new_y /= CUBE_SIZE;
	if (new_x < 0 || new_x >= map->map_width || new_y < 0 || \
		new_y >= map->map_height)
	{
		return (1);
	}
	if (map->map[new_y][new_x] == '1' || map->map[new_y + 1][new_x + 1] == ' ')
		return (1);
	return (0);
}

int	is_blocking_left(t_cub3d *map, int new_x, int new_y)
{
	new_x -= 16;
	new_y += 16;
	new_x /= CUBE_SIZE;
	new_y /= CUBE_SIZE;
	if (new_x < 0 || new_x >= map->map_width || new_y < 0 || \
		new_y >= map->map_height)
	{
		return (1);
	}
	if (map->map[new_y][new_x] == '1' || map->map[new_y + 1][new_x + 1] == ' ')
		return (1);
	return (0);
}
