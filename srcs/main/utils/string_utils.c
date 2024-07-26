/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdias-ba <rdias-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:32:54 by rdias-ba          #+#    #+#             */
/*   Updated: 2024/07/12 14:55:28 by rdias-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// strlen mais sans retour a la ligne

unsigned int	ft_strlen_wnl(const char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	return (i);
}

// copie la string comme strdup sans le retour à la ligne et les espaces

char	*ft_strdup_wnls(const char *str)
{
	char			*res;
	unsigned int	i;
	unsigned int	j;

	j = ft_strlen_wnl(str);
	if (str && str[0] == '\n')
		return (ft_strdup(""));
	while (str[j] == '\0' || str[j] == '\n' || str[j] == ' ')
		j--;
	res = malloc(sizeof(char) * (j + 2));
	if (!res)
		return (NULL);
	i = 0;
	while (i < j + 1)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

int	array_len(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}
