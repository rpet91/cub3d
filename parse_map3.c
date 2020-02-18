/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map3.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/11 15:31:37 by rpet          #+#    #+#                 */
/*   Updated: 2020/02/18 14:54:26 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub3d.h"

/*
**		Creates a new map with everything set to zero.
*/

void	create_empty_map(t_map *map)
{
	map->player_coords.x = -1;
	map->player_coords.y = -1;
	map->resolution.x = 0;
	map->resolution.y = 0;
	map->north_tex = 0;
	map->south_tex = 0;
	map->west_tex = 0;
	map->east_tex = 0;
	map->sprite_tex = 0;
	map->floor_rgb = -1;
	map->ceiling_rgb = -1;
	map->check = 0;
	map->map = malloc(sizeof(char *));
	if (map->map == NULL)
		return ;
	map->map[0] = NULL;
}

/*
**		Adds the new created line to the existing map.
*/

char	**add_line_to_map(char **old_map, char *new_line)
{
	char	**new_map;
	int		i;

	i = 0;
	while (old_map[i] != NULL)
		i++;
	new_map = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (old_map[i] != NULL)
	{
		new_map[i] = old_map[i];
		i++;
	}
	new_map[i] = new_line;
	new_map[i + 1] = NULL;
	free(old_map);
	return (new_map);
}

/*
**		Erases the spaces from the given map line.
*/

char	*remove_spaces(char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ')
		{
			str[j] = str[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	return (str);
}

/*
**		Main function about creating the map.
*/

int		map_information(t_map *map, char *line)
{
	char	*new_line;

	if (map->check == 0)
		map->check = 1;
	new_line = ft_strdup(remove_spaces(line));
	if (new_line == NULL || map->check == 2)
	{
		free_array(map->map);
		if (new_line != NULL)
			free(new_line);
		return (-1);
	}
	map->map = add_line_to_map(map->map, new_line);
	return (1);
}
