/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdias-ba <rdias-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:53:50 by rdias-ba          #+#    #+#             */
/*   Updated: 2024/07/12 14:22:17 by rdias-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// initialisation de la fenêtre

int	window_init(t_cub3d *map)
{
	map->mlx = mlx_init();
	if (!map->mlx)
		return (print_error(ERR_MLX_INIT, EXIT_FAILURE));
	map->mlx_win = mlx_new_window(map->mlx, WIDTH, HEIGHT, "cub3D");
	if (!map->mlx_win)
	{
		mlx_destroy_display(map->mlx);
		free(map->mlx);
		return (print_error(ERR_WIN_INIT, EXIT_FAILURE));
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_cub3d	map;

	if (ac != 2)
		return (print_error(ERR_ARGS, EXIT_FAILURE));
	if (!check_extension(av[1]))
		return (print_error(ERR_EXT, EXIT_FAILURE));
	if (!window_init(&map))
		return (EXIT_FAILURE);
	if (!parsing(av[1], &map))
	{
		mlx_destroy_window(map.mlx, map.mlx_win);
		mlx_destroy_display(map.mlx);
		free(map.mlx);
		return (EXIT_FAILURE);
	}
	game(&map);
	return (0);
}
