/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:36:05 by rdias-ba          #+#    #+#             */
/*   Updated: 2024/07/26 07:22:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// enregistre la ligne de la map dans le buffer et rajoute un espace a la fin

static int	fill_map_row(char *buff, t_cub3d *map, int row)
{
	int	i;

	i = 0;
	while (buff[i] != '\n' && buff[i] != '\0')
	{
		if (buff[i] == ' ' || buff[i] == '1' || buff[i] == '0' || buff[i] == 'N'\
		|| buff[i] == 'S' || buff[i] == 'E' || buff[i] == 'W' || buff[i] == 'D')
			map->map[row][i] = buff[i];
		else
			return (print_error(ERR_MAP_CHAR, 0));
		i++;
	}
	while (i < map->map_width)
	{
		map->map[row][i] = ' ';
		i++;
	}
	map->map[row][i] = '\0';
	return (1);
}

// enregistre la map dans le buffer

static int	fill_map(char *map_file, t_cub3d *map)
{
	int		i;
	int		fd;
	char	*buff;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		return (print_error(ERR_MAP_READ, 0));
	buff = "";
	i = 0;
	while (buff)
	{
		buff = get_next_line(fd);
		if (is_map_desc(buff))
		{
			if (!fill_map_row(buff, map, i))
			{
				free(buff);
				return (close(fd));
			}
			i++;
		}
		free(buff);
	}
	close(fd);
	return (1);
}

// parse les textures, les couleurs et check la map pour les dimensions

static int	parse_line(char *buff, t_cub3d *map)
{
	static int	width = 0;
	static int	height = 0;
	int			res_t;
	int			res_c;

	if (!buff || buff[0] == '\0' || buff[0] == '\n')
		return (1);
	res_t = add_text(buff, map);
	if (res_t == 1 || res_t == 0)
		return (res_t);
	res_c = add_color(buff, map);
	if (res_c == 1 || res_c == 0)
		return (res_c);
	if (is_text_valid(map) && is_map_char(buff[0]))
	{
		height++;
		if ((int)ft_strlen_wnl(buff) > width)
			width = ft_strlen_wnl(buff);
	}
	else
		return (print_error(ERR_CHAR, 0));
	map->map_height = height + 1;
	map->map_width = width;
	return (1);
}

// parse ligne par ligne le fichier .cub à l'aide de read et gnl

static int	get_map(char *map_file, t_cub3d *map)
{
	int		fd;
	char	*buff;
	int		read_err;

	read_err = 0;
	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		return (print_error(ERR_MAP_READ, 0));
	if (!map_init(map))
		return (0);
	buff = "";
	while (buff)
	{
		buff = get_next_line(fd);
		if (!read_err && !parse_line(buff, map))
			read_err = 1;
		free(buff);
	}
	close(fd);
	if (read_err)
		return (free_texture(map));
	return (1);
}

// parse le contenu du fichier .cub

int	parsing(char *map_file, t_cub3d *map)
{
	if (!get_map(map_file, map))
		return (0);
	if (!init_map_array(map, map->map_height, map->map_width))
		return (free_texture(map));
	if (fill_map(map_file, map) <= 0)
	{
		free_array(&map->map, 0);
		return (free_texture(map));
	}
	if (!check_one_player(map->map))
	{
		free_array(&map->map, 0);
		return (free_texture(map));
	}
	if (!is_map_closed(map->map))
	{
		free_array(&map->map, 0);
		return (free_texture(map));
	}
	get_player_pos(map);
	return (1);
}
