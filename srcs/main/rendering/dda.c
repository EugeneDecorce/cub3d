/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdias-ba <rdias-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:04:12 by rdias-ba          #+#    #+#             */
/*   Updated: 2024/07/18 15:30:03 by rdias-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* calcule la data pour le DDA vertical grace à la pente
 * et au premier point d'intersection du rayon aux lignes verticales
 */
static t_dda	get_ver_data(t_dda data, t_cub3d *map, int right)
{
	double	tang;

	tang = data.angle_sin / data.angle_cos;
	if (right)
		data.delta_x = 1;
	else
		data.delta_x = -1;
	data.delta_y = data.delta_x * tang;
	if (right)
		data.x = ceil(map->player.map_pos.x);
	else
		data.x = floor(map->player.map_pos.x);
	data.y = map->player.map_pos.y + (data.x - map->player.map_pos.x) * tang;
	return (data);
}

// calcule la data pour le DDA horizontal

static t_dda	get_hor_data(t_dda data, t_cub3d *map, int up)
{
	double	tang;

	tang = data.angle_cos / data.angle_sin;
	if (up)
		data.delta_y = -1;
	else
		data.delta_y = 1;
	data.delta_x = data.delta_y * tang;
	if (up)
		data.y = floor(map->player.map_pos.y);
	else
		data.y = ceil(map->player.map_pos.y);
	data.x = map->player.map_pos.x + (data.y - map->player.map_pos.y) * tang;
	return (data);
}

/* localise le mur dans l'axe vertical avec le rayon
 * depuis les coordonnées de la première intersection verticale
 */

static void	ver_dda(t_dda data, t_cub3d *map, t_frame *frame, double angle)
{
	int		right;
	double	wall_x;
	double	wall_y;

	right = (angle > PI_3_2 || angle < PI_2);
	data = get_ver_data(data, map, right);
	while (coords_valid(map, data.x, data.y))
	{
		if (right)
			wall_x = floor(data.x);
		else
			wall_x = floor(data.x - 1);
		wall_y = floor(data.y);
		if (is_wall(map, wall_x, wall_y))
		{
			fill_ver(frame, map, data, right);
			break ;
		}
		data.x += data.delta_x;
		data.y += data.delta_y;
	}
}

/* localise le mur dans l'axe horizontal avec rayon
 * et enregistre la distance entre le mur et le joueur
 * depuis les coordonnées de la première intersection horizontale
 */

static void	hori_dda(t_dda data, t_cub3d *map, t_frame *frame, double angle)
{
	int		up;
	double	wall_x;
	double	wall_y;
	double	dist;

	up = (angle < 0 || angle > PI);
	data = get_hor_data(data, map, up);
	while (coords_valid(map, data.x, data.y))
	{
		wall_y = get_wall_y(data, up);
		wall_x = floor(data.x);
		if (is_wall(map, wall_x, wall_y))
		{
			dist = sqrt(pow(data.x - map->player.map_pos.x, 2) + \
				pow(data.y - map->player.map_pos.y, 2));
			if (!frame->distance || dist < frame->distance)
			{
				frame->distance = dist;
				fill_hor(frame, data, up);
			}
			break ;
		}
		data.x += data.delta_x;
		data.y += data.delta_y;
	}
}

/*Utilisation de l'algorithme DDA (Digital Differential Analyzer)
 *pour trouver la distance entre le joueur et le prochain mur
 *en vérifient l'axe horizontal et vertical de la grille par où
 *passe le rayon en corrigeant les effets de distortion*/

void	dda(t_cub3d *map, double ray_ori, t_frame *frame)
{
	t_dda	data;
	double	fishbowl_corr;

	fishbowl_corr = cos(correct_angle(ray_ori - map->player.ori));
	frame->distance = 0;
	frame->angle = ray_ori;
	data.angle_cos = cos(ray_ori);
	data.angle_sin = sin(ray_ori);
	ver_dda(data, map, frame, ray_ori);
	hori_dda(data, map, frame, ray_ori);
	frame->distance *= fishbowl_corr;
	frame->height = CUBE_SIZE / frame->distance * PROJ_DISTANCE;
}
