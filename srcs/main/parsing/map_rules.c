/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_rules.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdias-ba <rdias-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:24:39 by rdias-ba          #+#    #+#             */
/*   Updated: 2024/07/12 15:21:53 by rdias-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// vérifie que tout à bien été enregistré

int	is_text_valid(t_cub3d *map)
{
	if (map->floor_color < 0 || map->ceiling_color < 0)
		return (0);
	if (!map->no_texture->img || !map->so_texture->img || \
		!map->ea_texture->img || !map->we_texture->img)
		return (0);
	return (1);
}

// vérifie qu'il y a un seul joueur dans la map

int	check_one_player(char **map)
{
	int	i;
	int	j;
	int	is_player;

	is_player = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!is_player && is_player_char(map[i][j]))
				is_player = 1;
			else if (is_player && is_player_char(map[i][j]))
				return (print_error(ERR_TM_PLAYERS, 0));
			j++;
		}
		i++;
	}
	if (!is_player)
		return (print_error(ERR_NO_PLAYERS, 0));
	return (1);
}

static int	is_valid_pos(char **map, int i, int j)
{
	if ((i == 0 || j == 0) && map[i][j] == '0')
		return (0);
	if (map[i - 1][j] == ' ' || map[i + 1][j] == ' ' \
		|| map[i][j - 1] == ' ' || map[i][j + 1] == ' ' \
		|| !map[i - 1][j] || !map[i + 1][j] \
		|| !map[i][j - 1] || !map[i][j + 1])
		return (0);
	return (1);
}

/* vérifie la validité de la map:
 * -pas de joueur n'y de vide en première casse
 * -pas de vide autour du joueur
 * -pas de vide autour d'un 0
 */

int	is_map_closed(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (i == 0 && ft_strchr("NSWE", map[i][j]))
				return (print_error(ERR_POS_PLAYER, 0));
			if (ft_strchr("NSWE", map[i][j]) && !is_valid_pos(map, i, j))
				return (print_error(ERR_POS_PLAYER, 0));
			if (map[i][j] == '0' && !is_valid_pos(map, i, j))
				return (print_error(ERR_MAP_BORDER, 0));
			j++;
		}
		i++;
	}
	return (1);
}
