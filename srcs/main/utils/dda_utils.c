/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdias-ba <rdias-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:44:58 by rdias-ba          #+#    #+#             */
/*   Updated: 2024/07/18 14:54:01 by rdias-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// arrondie les coordonnées de la rencontre avec un mur potentiel

double	get_wall_y(t_dda utils, int up)
{
	double	wall_y;

	if (up)
		wall_y = floor(utils.y - 1);
	else
		wall_y = floor(utils.y);
	return (wall_y);
}

/* l'axe est set à 0 (horizontal) et l'orientation des mur est
 * définie par l'angle du rayon
 */

void	fill_hor(t_frame *frame, t_dda data, int up)
{
	frame->point.x = data.x;
	frame->point.y = data.y;
	frame->axis = 0;
	if (up)
		frame->wall_face = SOUTH;
	else
		frame->wall_face = NORTH;
}

/* Calcule la distance en utilisant le theorème de pythagore
 * l'axe est set à 1 (vertical) et l'orientation des mur est
 * définie par l'angle du rayon
 */

void	fill_ver(t_frame *frame, t_cub3d *map, t_dda data, int right)
{
	frame->distance = sqrt(pow(data.x - map->player.map_pos.x, 2) + \
		pow(data.y - map->player.map_pos.y, 2));
	frame->point.x = data.x;
	frame->point.y = data.y;
	frame->axis = 1;
	if (right)
		frame->wall_face = WEST;
	else
		frame->wall_face = EAST;
}

// vérifie si les coordonnées sont dans la map

int	coords_valid(t_cub3d *map, int x, int y)
{
	if (x >= 0 && x < map->map_width * CUBE_SIZE && \
		y >= 0 && y < map->map_height * CUBE_SIZE)
		return (1);
	return (0);
}

// vérifie si les coordonnées sont sur un mur

int	is_wall(t_cub3d *map, int x, int y)
{
	x = (int)floor(x / CUBE_SIZE);
	y = (int)floor(y / CUBE_SIZE);
	if (map->map[y][x] == '1')
		return (1);
	return (0);
}
