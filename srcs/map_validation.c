/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_validation.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/18 11:02:54 by rpet          #+#    #+#                 */
/*   Updated: 2020/06/02 07:54:58 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../cub3d.h"

/*
**		Flood fills in 8 directions to check if the map is surrounded by walls.
*/

int		check_closed(t_data *mlx, char **copy_map, int y, int x)
{
	if (y < 0 || y >= mlx->map.size.y || x < 0 || x >= mlx->map.size.x ||
		copy_map[y][x] == ' ')
		return (-1);
	if (copy_map[y][x] == 'x' || copy_map[y][x] == '1')
		return (1);
	copy_map[y][x] = 'x';
	if (check_closed(mlx, copy_map, y, x - 1) == -1)
		return (-1);
	if (check_closed(mlx, copy_map, y, x + 1) == -1)
		return (-1);
	if (check_closed(mlx, copy_map, y - 1, x) == -1)
		return (-1);
	if (check_closed(mlx, copy_map, y + 1, x) == -1)
		return (-1);
	if (check_closed(mlx, copy_map, y - 1, x - 1) == -1)
		return (-1);
	if (check_closed(mlx, copy_map, y - 1, x + 1) == -1)
		return (-1);
	if (check_closed(mlx, copy_map, y + 1, x - 1) == -1)
		return (-1);
	if (check_closed(mlx, copy_map, y + 1, x + 1) == -1)
		return (-1);
	return (1);
}

/*
**		Creates a copy of the original map.
*/

void	create_copy_map(t_data *mlx, int max_y, int max_x)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (max_y + 1));
	if (copy == NULL)
		error_handling(MALLOC, mlx);
	i = 0;
	while (mlx->map.map[i] != NULL)
	{
		copy[i] = malloc(sizeof(char) * (max_x + 1));
		if (copy[i] == NULL)
		{
			free_array(copy);
			error_handling(MALLOC, mlx);
		}
		ft_memcpy(copy[i], mlx->map.map[i], max_x);
		copy[i][max_x] = '\0';
		i++;
	}
	copy[max_y] = NULL;
	copy[mlx->map.player.y][mlx->map.player.x] = '0';
	i = check_closed(mlx, copy, mlx->map.player.y, mlx->map.player.x);
	free_array(copy);
	if (i == -1)
		error_handling(OPEN_MAP, mlx);
}

/*
**		Checks for invalid characters in the map.
*/

void	check_valid_map(t_data *mlx)
{
	int		x;
	int		y;
	int		check_multiple_players;

	y = 0;
	check_multiple_players = 0;
	while (mlx->map.map[y])
	{
		x = 0;
		while (mlx->map.map[y][x] && check_multiple_players <= 1)
		{
			if (ft_strchr_i("NSEW", mlx->map.map[y][x]) == 1)
				check_multiple_players++;
			else if ((mlx->map.map[y][x] < '0' || mlx->map.map[y][x] > '2') &&
				mlx->map.map[y][x] != ' ')
				error_handling(INVALID_CHAR, mlx);
			x++;
		}
		y++;
	}
	if (check_multiple_players != 1)
		error_handling(WRONG_PLAYER_POS, mlx);
	create_copy_map(mlx, mlx->map.size.y, mlx->map.size.x);
}
