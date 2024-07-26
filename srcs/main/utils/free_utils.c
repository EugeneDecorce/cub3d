/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdias-ba <rdias-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 18:08:09 by rdias-ba          #+#    #+#             */
/*   Updated: 2024/07/12 14:59:18 by rdias-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//free un array de complet

int	free_array(char ***array, int err)
{
	int	i;

	if (*array == NULL)
		return (0);
	i = 0;
	while ((*array)[i])
	{
		free((*array)[i]);
		i++;
	}
	free(*array);
	if (err)
		return (print_error(ERR_CHAR, -1));
	return (0);
}

void	free_partial_array(char ***array, int last)
{
	int	i;

	i = 0;
	while (i < last)
	{
		free(*(array[i]));
		i++;
	}
	free(*array);
}

int	free_texture(t_cub3d *map)
{
	if (map->no_texture->is_init)
		mlx_destroy_image(map->mlx, map->no_texture->img);
	if (map->so_texture->is_init)
		mlx_destroy_image(map->mlx, map->so_texture->img);
	if (map->ea_texture->is_init)
		mlx_destroy_image(map->mlx, map->ea_texture->img);
	if (map->we_texture->is_init)
		mlx_destroy_image(map->mlx, map->we_texture->img);
	free(map->no_texture);
	free(map->so_texture);
	free(map->ea_texture);
	free(map->we_texture);
	return (0);
}

int	free_all(t_cub3d *map)
{
	int	i;

	i = 0;
	while (i < map->map_height)
	{
		free(map->map[i]);
		i++;
	}
	free(map->frame);
	free(map->map);
	free_texture(map);
	if (map->mlx_img.img)
		mlx_destroy_image(map->mlx, map->mlx_img.img);
	mlx_destroy_window(map->mlx, map->mlx_win);
	mlx_destroy_display(map->mlx);
	free(map->mlx);
	exit(EXIT_SUCCESS);
	return (0);
}
