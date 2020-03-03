/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_validation.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/18 11:02:54 by rpet          #+#    #+#                 */
/*   Updated: 2020/02/27 15:35:53 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../cub3d.h"

/*
**		Flood fills in 8 directions to check if the map is surrounded by walls.
*/

int		check_closed_map(t_map *map, char **copy_map, int y, int x)
{
	if (y < 0 || y >= map->size.y || x < 0 || x >= map->size.x)
		return (-1);
	if (copy_map[y][x] == 'x' || copy_map[y][x] == '1')
		return (1);
	copy_map[y][x] = 'x';
	if (check_closed_map(map, copy_map, y, x - 1) == -1)
		return (-1);
	if (check_closed_map(map, copy_map, y, x + 1) == -1)
		return (-1);
	if (check_closed_map(map, copy_map, y - 1, x) == -1)
		return (-1);
	if (check_closed_map(map, copy_map, y + 1, x) == -1)
		return (-1);
	if (check_closed_map(map, copy_map, y - 1, x - 1) == -1)
		return (-1);
	if (check_closed_map(map, copy_map, y - 1, x + 1) == -1)
		return (-1);
	if (check_closed_map(map, copy_map, y + 1, x - 1) == -1)
		return (-1);
	if (check_closed_map(map, copy_map, y + 1, x + 1) == -1)
		return (-1);
	return (1);
}

/*
**		Creates a copy of the original map.
*/

void	create_copy_map(t_map *map, int max_y, int max_x)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (max_y + 1));
	if (copy == NULL)
		map_error_handling(MALLOC, map);
	i = 0;
	while (map->map[i] != NULL)
	{
		copy[i] = malloc(sizeof(char) * (max_x + 1));
		if (copy[i] == NULL)
		{
			free_array(copy);
			map_error_handling(MALLOC, map);
		}
		ft_memcpy(copy[i], map->map[i], max_x);
		copy[i][max_x] = '\0';
		i++;
	}
	copy[max_y] = NULL;
	copy[map->player.y][map->player.x] = '0';
	i = check_closed_map(map, copy, map->player.y, map->player.x);
	free_array(copy);
	if (i == -1)
		map_error_handling(OPEN_MAP, map);
}

/*
**		Checks for invalid characters in the map.
*/

void	check_valid_map(t_map *map)
{
	int		x;
	int		y;
	int		check_multiple_players;

	y = 0;
	check_multiple_players = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x] && check_multiple_players <= 1)
		{
			if (ft_strchr("NSEW", map->map[y][x]) == 1)
				check_multiple_players++;
			else if (map->map[y][x] < '0' || map->map[y][x] > '2')
				map_error_handling(INVALID_CHAR, map);
			x++;
		}
		y++;
	}
	if (check_multiple_players != 1)
		map_error_handling(WRONG_PLAYER_POS, map);
	create_copy_map(map, map->size.y, map->size.x);
}
