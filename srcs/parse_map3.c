/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map3.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/11 15:31:37 by rpet          #+#    #+#                 */
/*   Updated: 2020/06/02 08:03:30 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../cub3d.h"

/*
**		Checks if every map element received info.
*/

void	element_validation(t_data *mlx)
{
	t_map	*map;

	map = &mlx->map;
	if (map->res.x == 0 || map->res.y == 0 || map->floor_rgb == -1
	|| map->ceiling_rgb == -1 || map->north_tex == 0 || map->south_tex == 0
	|| map->west_tex == 0 || map->east_tex == 0 || map->sprite_tex == 0
	|| map->floor_tex == 0 || map->ceiling_tex == 0)
		error_handling(NO_INFO, mlx);
}

/*
**		Makes a rectangle from the build map.
*/

char	**make_rectangle(t_data *mlx)
{
	char	*extended_line;
	int		y;
	int		old_len;

	y = 0;
	while (mlx->map.map[y] != NULL)
	{
		old_len = ft_strlen(mlx->map.map[y]);
		if (old_len < mlx->map.size.x)
		{
			extended_line = malloc(sizeof(char) * (mlx->map.size.x + 1));
			if (extended_line == NULL)
				return (NULL);
			ft_memcpy(extended_line, mlx->map.map[y], old_len);
			ft_memset(extended_line + old_len, ' ', mlx->map.size.x - old_len);
			extended_line[mlx->map.size.x] = '\0';
			free(mlx->map.map[y]);
			mlx->map.map[y] = extended_line;
		}
		y++;
	}
	return (mlx->map.map);
}

/*
**		Adds the new line to the existing map.
*/

char	**add_line_to_map(char **old_map, char *new_line, int y)
{
	char	**new_map;
	int		i;

	new_map = malloc(sizeof(char *) * (y + 2));
	if (new_map == NULL)
	{
		free(new_line);
		return (NULL);
	}
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
**		Locates player position.
*/

char	*find_player_pos(t_data *mlx, char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_strchr_i("NSEW", str[i]) == 1)
			mlx->map.player.x = i;
		i++;
	}
	if (mlx->map.player.x == 0)
		mlx->map.player.y++;
	return (str);
}

/*
**		Main function about creating the map.
*/

void	map_information(t_data *mlx, char *line)
{
	char	*new_line;
	int		len;

	element_validation(mlx);
	if (mlx->map.check == 0)
		mlx->map.check = 1;
	new_line = ft_strdup(find_player_pos(mlx, line));
	if (new_line == NULL || mlx->map.check == 2)
	{
		if (new_line != NULL)
		{
			free(new_line);
			error_handling(INVALID_CHAR, mlx);
		}
		error_handling(MALLOC, mlx);
	}
	len = ft_strlen(new_line);
	mlx->map.map = add_line_to_map(mlx->map.map, new_line, mlx->map.size.y);
	if (mlx->map.map == NULL)
		error_handling(MALLOC, mlx);
	mlx->map.size.x = (len > mlx->map.size.x) ? len : mlx->map.size.x;
	mlx->map.size.y++;
}
