/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_alloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdias-ba <rdias-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:40:37 by rdias-ba          #+#    #+#             */
/*   Updated: 2024/07/12 14:59:41 by rdias-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// vérifie la couleurs

static int	check_color(char *str)
{
	int		i;
	int		color;
	char	*tmp;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (ft_strlen_wnl(&str[i]) == 0)
		return (-1);
	tmp = ft_strdup_wnls(&str[i]);
	i = 0;
	while (tmp[i] != '\0' && ft_isdigit(tmp[i]))
		i++;
	while (tmp[i] != '\0')
	{
		if (tmp[i] != ' ')
		{
			free(tmp);
			return (-1);
		}
		i++;
	}
	color = ft_atoi(tmp);
	free(tmp);
	return (color);
}

// split les couleurs en r,g,b et les return en format adapté

static int	get_color(char *str)
{
	int		r;
	int		g;
	int		b;
	char	**split;

	split = ft_split(str, ',');
	if (!split)
		return (print_error(ERR_MALLOC, -1));
	if (array_len(split) != 3)
	{
		free_array(&split, 0);
		return (print_error(ERR_COL_FORMAT, -1));
	}
	r = check_color(split[0]);
	g = check_color(split[1]);
	b = check_color(split[2]);
	free_array(&split, 0);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (print_error(ERR_COL_FORMAT, -1));
	return (create_mlx_color(0, r, g, b));
}

static int	add_floor_color(char *buff, t_cub3d *map)
{
	int	i;
	int	color;

	if (map->floor_color != -1)
		return (print_error(ERR_DD_COLOR, 0));
	i = 1;
	while (buff[i] == ' ')
		i++;
	color = get_color(&buff[i]);
	if (color < 0)
		return (0);
	map->floor_color = color;
	return (1);
}

static int	add_ceiling_color(char *buff, t_cub3d *map)
{
	int	i;
	int	color;

	if (map->ceiling_color != -1)
		return (print_error(ERR_DD_COLOR, 0));
	i = 1;
	while (buff[i] == ' ')
		i++;
	color = get_color(&buff[i]);
	if (color < 0)
		return (0);
	map->ceiling_color = color;
	return (1);
}

// parsing des couleurs

int	add_color(char *buff, t_cub3d *map)
{
	if (ft_strncmp(buff, "F ", 2) == 0)
	{
		if (!add_floor_color(buff, map))
			return (0);
		return (1);
	}
	else if (ft_strncmp(buff, "C ", 2) == 0)
	{
		if (!add_ceiling_color(buff, map))
			return (0);
		return (1);
	}
	return (-1);
}
