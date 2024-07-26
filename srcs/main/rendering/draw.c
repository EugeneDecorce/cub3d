/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:58:16 by rdias-ba          #+#    #+#             */
/*   Updated: 2024/07/26 07:28:23 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* si les coordonnées sont dans l'image, applique le pixel de couleur
 * à l'addresse de destination
 */

void	ft_mlx_pixel_put(t_mlx_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static t_text	*get_texture(t_cub3d *map, enum e_pos side)
{
	if (side == NORTH)
		return (map->no_texture);
	else if (side == SOUTH)
		return (map->so_texture);
	else if (side == EAST)
		return (map->ea_texture);
	else
		return (map->we_texture);
}

/* dessine la texture du mur en fonction de son orientation
 * et sa distance entre elle et le joueur
 * x_offset et text_y sont nécessaire pour choisir le bon pixel dans l'image
 * 1 == vertical, 0 == horizontal
 */

static void	draw_texture_col(t_cub3d *map, t_frame frame, int x, int offset)
{
	float	scale;
	float	text_y;
	int		texture_x_offset;
	t_text	*texture;
	int		y;

	texture = get_texture(map, frame.wall_face);
	scale = texture->height / frame.height;
	if (frame.axis == 1)
		texture_x_offset = frame.point.y % CUBE_SIZE;
	else
		texture_x_offset = frame.point.x % CUBE_SIZE;
	text_y = 0;
	if (frame.height > HEIGHT)
		text_y = ((frame.height - HEIGHT) / 2) * scale;
	y = 0;
	while (y < frame.height)
	{
		ft_mlx_pixel_put(&map->mlx_img, x, y + offset, \
			get_texture_color(texture, texture_x_offset, \
			(int)text_y % texture->height));
		text_y += scale;
		y++;
	}
}

//Dessine dans l'ordre le plafond, le mur et le sol


void	draw_slice(t_cub3d *map, t_frame frame, int index)
{
	int	i;
	int	y_offset;

	i = 0;
	y_offset = (HEIGHT - frame.height) / 2;
	if (y_offset < 0)
		y_offset = 0;
	while (i < y_offset)
	{
		ft_mlx_pixel_put(&map->mlx_img, index, i, map->ceiling_color + map->shade);
		i++;
	}
	draw_texture_col(map, frame, index, i);
	i = frame.height + y_offset;
	while (i < HEIGHT)
	{
		ft_mlx_pixel_put(&map->mlx_img, index, i, map->floor_color);
		i++;
	}
}
