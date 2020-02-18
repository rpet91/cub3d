/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_validation.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/18 11:02:54 by rpet          #+#    #+#                 */
/*   Updated: 2020/02/18 15:39:05 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub3d.h"

char	**copy_original_map(t_map *map)
{
	char	**result;
	int		i;

	i = 0;
	while (map->map[i])
		i++;
	result = malloc(sizeof(char *) * (i + 1));
	if (result == NULL)
		return (NULL);
	result[i] = NULL;
	i = 0;
	while (map->map[i])
	{
		result[i] = ft_strdup(map->map[i]);
		if (result[i] == NULL)
		{
			free_array(result);
			return (NULL);
		}
		i++;
	}
	return (result);
}

int		flood_fill(t_map *map)
{
	char	**copy_map;

	copy_map = copy_original_map(map);
	if (copy_map == NULL)
		return (-1);
	return (1);
}

int		check_valid_map(t_map *map)
{
	int		x;
	int		y;
	int		start_position;

	y = 0;
	start_position = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x] && start_position <= 1)
		{
			if (ft_strchr("NSEW", map->map[y][x]) == 1)
			{
				map->player_coords.x = x;
				map->player_coords.y = y;
				start_position++;
			}
			else if (map->map[y][x] != '0' && map->map[y][x] != '1' &&
					map->map[y][x] != '2')
				return (-1);
			x++;
		}
		y++;
	}
	if (start_position != 1)
		return (-1);
	return (flood_fill(map));
}
