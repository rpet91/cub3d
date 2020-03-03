/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map2.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/10 11:02:18 by rpet          #+#    #+#                 */
/*   Updated: 2020/02/27 15:53:31 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "../cub3d.h"

/*
**		Reads info about map size.
*/

void	map_resolution(t_map *map, char *str)
{
	char	**resolution;

	if (map->res.x != 0 || map->res.y != 0 || map->check != 0)
		map_error_handling(WRONG_INFO, map);
	resolution = ft_split(str, ' ');
	if (resolution == NULL)
		map_error_handling(MALLOC, map);
	if (ft_strncmp(resolution[0], "R", ft_strlen(resolution[0])) != 0
			|| resolution[3] != NULL)
	{
		free_array(resolution);
		map_error_handling(WRONG_INFO, map);
	}
	map->res.x = ft_atoi(resolution[1]);
	map->res.y = ft_atoi(resolution[2]);
	free_array(resolution);
	if (map->res.x < 1 || map->res.y < 1)
		map_error_handling(WRONG_RES_SIZE, map);
}

/*
**		Converts given color string to viable int.
*/

int		get_color(char *color_line)
{
	int		color;
	int		rgb;
	int		count;

	color = 0;
	rgb = 0;
	count = 0;
	while (*color_line != '\0')
	{
		if (*color_line < '0' || *color_line > '9')
			return (-1);
		rgb = ft_atoi(color_line);
		if (rgb < 0 || rgb > 255)
			return (-1);
		while (*color_line >= '0' && *color_line <= '9')
			color_line++;
		color = (color << 8) + rgb;
		count++;
		if (*color_line == ',' && count != 3)
			color_line++;
	}
	if (count != 3)
		return (-1);
	return (color);
}

/*
**		Checks if there is a valid given color string for the ceiling/floor.
*/

void	map_read_color(int *rgb, char *str, char *loc, t_map *map)
{
	char	**color;

	if (*rgb != -1 || map->check != 0)
		map_error_handling(WRONG_INFO, map);
	color = ft_split(str, ' ');
	if (color == NULL)
		map_error_handling(MALLOC, map);
	if (ft_strncmp(color[0], loc, ft_strlen(color[0])) != 0 || color[2] != NULL)
	{
		free_array(color);
		map_error_handling(WRONG_INFO, map);
	}
	*rgb = get_color(color[1]);
	if (get_color(color[1]) == -1)
	{
		free_array(color);
		map_error_handling(WRONG_COLOR, map);
	}
	free_array(color);
}

/*
**		Checks if there is a valid given texture string for the walls.
*/

void	map_read_tex(char **wall, char *str, char *loc, t_map *map)
{
	char	**text;

	if (*wall != 0 || map->check != 0)
		map_error_handling(WRONG_INFO, map);
	text = ft_split(str, ' ');
	if (text == NULL)
		map_error_handling(MALLOC, map);
	if (ft_strncmp(text[0], loc, ft_strlen(text[0])) != 0 || text[2] != NULL)
	{
		free_array(text);
		map_error_handling(WRONG_INFO, map);
	}
	*wall = ft_strdup(text[1]);
	free_array(text);
	if (*wall == NULL)
		map_error_handling(MALLOC, map);
	if (open(*wall, O_RDONLY) == -1)
		map_error_handling(WRONG_TEXTURE, map);
	if (ft_strncmp(*wall + ft_strlen(*wall) - 4, ".png", 4) != 0 &&
		ft_strncmp(*wall + ft_strlen(*wall) - 4, ".xpm", 4) != 0)
		map_error_handling(WRONG_TEXTURE, map);
}
