/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 12:21:06 by user              #+#    #+#             */
/*   Updated: 2024/07/26 12:30:13 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"
/*
Add draw minimap here:

void create_frame(t_cub3d *map)
{
	map->mlx_img.img = mlx_new_image(map->mlx, WIDTH, HEIGHT);
	if (!map->mlx_img.img)
		free_all(map);
	map->mlx_img.addr = mlx_get_data_addr(map->mlx_img.img, \
		&map->mlx_img.bits_per_pixel, &map->mlx_img.line_length, \
		&map->mlx_img.endian);
	if (!map->mlx_img.addr)
		free_all(map);

	raycasting(map);
	create_image(map);
	draw_minimap(map);  // Draw the minimap <----------------------------------
	mlx_put_image_to_window(map->mlx, map->mlx_win, map->mlx_img.img, 0, 0);
}
*/

// Création de l'image et de ses composantes
#include "cub3d.h"

void my_mlx_pixel_put(t_mlx_data *img, int x, int y, int color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) // Ensure within bounds of the whole window
	{
		char *dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}
	
void draw_minimap(t_cub3d *map)
{
	int minimap_scale = 4;  // Change this scale as needed
	int minimap_size = 100; // Size of the minimap in pixels
	int player_size = 3;	// Size of the player dot on the minimap
	int offset_x = 10;	  // Offset from the left of the screen
	int offset_y = 10;	  // Offset from the top of the screen
	int x, y;

	// Draw the map
	for (y = 0; y < map->map_height; y++)
	{
		for (x = 0; x < map->map_width; x++)
		{
			int color = (map->map[y][x] == '1') ? 0xFFFFFF : 0x000000; // White for walls, black for empty space
			int draw_x = x * minimap_scale + offset_x;
			int draw_y = y * minimap_scale + offset_y;

			int i, j;
			for (i = 0; i < minimap_scale; i++)
			{
				for (j = 0; j < minimap_scale; j++)
				{
					int pixel_x = draw_x + i;
					int pixel_y = draw_y + j;
					if (pixel_x >= offset_x && pixel_x < minimap_size + offset_x &&
						pixel_y >= offset_y && pixel_y < minimap_size + offset_y)
					{
						my_mlx_pixel_put(&map->mlx_img, pixel_x, pixel_y, color);
					}
				}
			}
		}
	}

	// Draw the player
	//printf("[%d-%d][%d-%d]\n", map->player.map_pos.x, map->player.map_pos.y, map->map_height, map->map_width);
	int player_minimap_x = map->player.map_pos.x / CUBE_SIZE * minimap_scale + offset_x;
	int player_minimap_y = map->player.map_pos.y  / CUBE_SIZE * minimap_scale + offset_y;
	for (y = -player_size; y <= player_size; y++)
	{
		for (x = -player_size; x <= player_size; x++)
		{
			int pixel_x = player_minimap_x + x;
			int pixel_y = player_minimap_y + y;
			if (pixel_x >= offset_x && pixel_x < minimap_size + offset_x &&
				pixel_y >= offset_y && pixel_y < minimap_size + offset_y)
			{
				//printf("%d-%d", pixel_x, pixel_y);
				my_mlx_pixel_put(&map->mlx_img, pixel_x, pixel_y, 0xFF0000); // Red for player
			}
		}
	}
}
