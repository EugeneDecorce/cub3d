/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:59:18 by rdias-ba          #+#    #+#             */
/*   Updated: 2024/07/26 12:05:36 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// enregistre la texture et ses composantes

int	load_texture(t_text *texture, t_cub3d *map, char *path)
{
	texture->img = mlx_xpm_file_to_image(map->mlx, path, \
					&texture->width, &texture->height);
	if (!texture->img)
		return (print_error(ERR_TEXTURE, 0));
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel, \
					&texture->line_length, &texture->endian);
	if (!texture->addr)
		return (print_error(ERR_ADDR, 0));
	return (1);
}

int	get_texture_color(t_text *text, int x, int y)
{
	int	pixel_offset;

	if (x < 0 || x >= text->width)
		return (0);
	if (y < 0 || y >= text->height)
		return (0);
	pixel_offset = y * text->line_length + x * (text->bits_per_pixel / 8);
	return (*(int *)(text->addr + pixel_offset));
}

// modifie le format de couleurs pour mlx

int	create_mlx_color(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

static int	key_hook(int key, t_cub3d *map)
{
	if (key == LEFT_ARROW)
	{
		map->player.ori = correct_angle(map->player.ori - ROT_SPEED);
		mlx_destroy_image(map->mlx, map->mlx_img.img);
		create_frame(map);
	}
	else if (key == RIGHT_ARROW)
	{
		map->player.ori = correct_angle(map->player.ori + ROT_SPEED);
		mlx_destroy_image(map->mlx, map->mlx_img.img);
		create_frame(map);
	}
	else if (key == FORWARD)
		move_forward(map);
	else if (key == BACKWARD)
		move_backward(map);
	else if (key == LEFT)
		move_left(map);
	else if (key == RIGHT)
		move_right(map);
	if (key == ESC)
		free_all(map);
	return (0);
}

void	game(t_cub3d *map)
{
	mlx_do_key_autorepeaton(map->mlx);
	mlx_hook(map->mlx_win, 2, 1L << 0, key_hook, map);
	mlx_hook(map->mlx_win, 6, 1L << 6, (int (*)())mouse_move, map);
	mlx_hook(map->mlx_win, 17, (1L << 2), free_all, map);
	mlx_loop_hook(map->mlx, animation_loop, map);
	create_frame(map);
	mlx_loop(map->mlx);
}
