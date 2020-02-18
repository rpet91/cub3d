/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map2.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/10 11:02:18 by rpet          #+#    #+#                 */
/*   Updated: 2020/02/18 07:44:59 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
**		check == 0 there is no info found about the map yet
**		check == 1 it found all the info about the map
**		check == 2 it may not find other info than end of line
*/

int		end_of_line(t_map *map)
{
	if (map->check == 1)
		map->check = 2;
	return (1);
}

/*
**		Reads info about map size
*/

int		map_resolution(t_map *map, char *line)
{
	char	**resolution;

	if (map->resolution.x != 0 || map->resolution.y != 0 || map->check != 0)
		return (-1);
	resolution = ft_split(line, ' ');
	if (resolution == NULL)
		return (-1);
	if (ft_strncmp(resolution[0], "R", ft_strlen(resolution[0])) != 0)
		return (-1);
	if (resolution[3] != NULL)
		return (-1);
	map->resolution.x = ft_atoi(resolution[1]);
	map->resolution.y = ft_atoi(resolution[2]);
	if (map->resolution.x < 1 || map->resolution.y < 1)
		return (-1);
	if (map->resolution.x > MAX_RESOLUTION_X)
		map->resolution.x = MAX_RESOLUTION_X;
	if (map->resolution.y > MAX_RESOLUTION_Y)
		map->resolution.y = MAX_RESOLUTION_Y;
	free_array(resolution);
	return (1);
}

/*
**		Converts given color string to viable int
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
**		Checks if there is a valid given color string for the ceiling/floor
*/

int		map_read_color(int *rgb, char *line, char *loc, int check)
{
	char	**color;

	if (*rgb != -1 || check != 0)
		return (-1);
	color = ft_split(line, ' ');
	if (color == NULL)
		return (-1);
	if (ft_strncmp(color[0], loc, ft_strlen(color[0])) != 0)
		return (-1);
	if (color[2] != NULL)
		return (-1);
	*rgb = get_color(color[1]);
	if (get_color(color[1]) == -1)
	{
		free_array(color);
		return (-1);
	}
	free_array(color);
	return (1);
}

/*
**		Checks if there is a valid given texture string for the walls
*/

int		map_read_texture(char **wall, char *line, char *loc, int check)
{
	char	**texture;

	if (*wall != 0 || check != 0)
		return (-1);
	texture = ft_split(line, ' ');
	if (texture == NULL)
		return (-1);
	if (ft_strncmp(texture[0], loc, ft_strlen(texture[0])) != 0)
		return (-1);
	if (texture[2] != NULL)
		return (-1);
	*wall = ft_strdup(texture[1]);
	free_array(texture);
	if (*wall == NULL)
		return (-1);
	return (1);
}
