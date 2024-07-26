/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdias-ba <rdias-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:11:34 by rdias-ba          #+#    #+#             */
/*   Updated: 2024/07/12 14:27:26 by rdias-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	no_text_init(t_cub3d *map)
{
	map->no_texture = malloc(sizeof(t_text));
	if (!map->no_texture)
		return (print_error(ERR_MALLOC, 0));
	map->no_texture->is_init = 0;
	return (1);
}

static int	so_text_init(t_cub3d *map)
{
	map->so_texture = malloc(sizeof(t_text));
	if (!map->so_texture)
	{
		free(map->no_texture);
		return (print_error(ERR_MALLOC, 0));
	}
	map->so_texture->is_init = 0;
	return (1);
}

static int	we_text_init(t_cub3d *map)
{
	map->we_texture = malloc(sizeof(t_text));
	if (!map->we_texture)
	{
		free(map->no_texture);
		free(map->so_texture);
		return (print_error(ERR_MALLOC, 0));
	}
	map->we_texture->is_init = 0;
	return (1);
}

static int	ea_text_init(t_cub3d *map)
{
	map->ea_texture = malloc(sizeof(t_text));
	if (!map->ea_texture)
	{
		free(map->no_texture);
		free(map->so_texture);
		free(map->we_texture);
		return (print_error(ERR_MALLOC, 0));
	}
	map->ea_texture->is_init = 0;
	return (1);
}

// initialise les textures 

int	text_init(t_cub3d *map)
{
	if (!no_text_init(map))
		return (0);
	if (!so_text_init(map))
		return (0);
	if (!we_text_init(map))
		return (0);
	if (!ea_text_init(map))
		return (0);
	return (1);
}
