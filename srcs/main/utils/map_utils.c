/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:00:19 by rdias-ba          #+#    #+#             */
/*   Updated: 2024/07/26 07:46:44 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_player_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

// vérifie que les characters utiliser pour le mapping sont valides

int	is_map_char(char c)
{
	if (c == 'D' || c == ' ' || c == '0' || c == '1' || is_player_char(c))
		return (1);
	return (0);
}

// fonction pour indiquer que le read est sur la ligne de la map

int	is_map_desc(char *buff)
{
	if (!buff || buff[0] == '\0' || buff[0] == '\n')
		return (0);
	if (ft_strncmp(buff, "NO ", 3) == 0)
		return (0);
	else if (ft_strncmp(buff, "SO ", 3) == 0)
		return (0);
	else if (ft_strncmp(buff, "WE ", 3) == 0)
		return (0);
	else if (ft_strncmp(buff, "EA ", 3) == 0)
		return (0);
	else if (ft_strncmp(buff, "F ", 2) == 0)
		return (0);
	else if (ft_strncmp(buff, "C ", 2) == 0)
		return (0);
	return (1);
}

// initialise tout les attributs de t_cub3d

int	map_init(t_cub3d *map)
{
	if (!text_init(map))
		return (0);
	map->floor_color = -1;
	map->ceiling_color = -1;
	map->map_width = 0;
	map->map_height = 0;
	map->map = NULL;
	map->player.map_pos.x = 0;
	map->player.map_pos.y = 0;
	map->player.ori = 0;
	map->frame = 0;

	map->shade = 1;
	map->shade_dir = 1;
	return (1);
}

// initialise la carte en fonction de ses dimensions

int	init_map_array(t_cub3d *map, int height, int width)
{
	int	i;

	map->map = malloc(sizeof(char *) * (height + 1));
	if (!map->map)
	{
		free_texture(map);
		return (print_error(ERR_MALLOC, 0));
	}
	map->map[height] = 0;
	i = 0;
	while (i < height)
	{
		map->map[i] = malloc(sizeof (char) * (width + 1));
		if (!map->map[i])
		{
			free_partial_array(&map->map, i);
			return (print_error(ERR_MALLOC, 0));
		}
		map->map[i][width] = '\0';
		while ((i == height - 1) && width > 0)
			map->map[i][--width] = ' ';
		i++;
	}
	return (1);
}
