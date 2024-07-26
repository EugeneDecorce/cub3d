/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdias-ba <rdias-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:50:01 by rdias-ba          #+#    #+#             */
/*   Updated: 2024/07/12 15:22:44 by rdias-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	get_player_orientation(char c)
{
	if (c == 'E')
		return (0.0);
	else if (c == 'W')
		return (PI);
	else if (c == 'S')
		return (PI_2);
	return (PI_3_2);
}

// enregistre les coordonnées du joueurs

void	get_player_pos(t_cub3d *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == 'N' || map->map[i][j] == 'S' || \
			map->map[i][j] == 'E' || map->map[i][j] == 'W')
			{
				map->player.map_pos.x = j * CUBE_SIZE + (CUBE_SIZE / 2);
				map->player.map_pos.y = i * CUBE_SIZE + (CUBE_SIZE / 2);
				map->player.speed = SPEED;
				map->player.ori = get_player_orientation(map->map[i][j]);
				return ;
			}
			j++;
		}
		i++;
	}
}
