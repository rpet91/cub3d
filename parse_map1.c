/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map1.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/07 11:05:08 by rpet          #+#    #+#                 */
/*   Updated: 2020/02/18 15:39:06 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "cub3d.h"

/*
**		Checks, refers and processes the given line.
*/

int		check_valid_info(t_map *map, char *line)
{
	if (*line == '\0')
		return (end_of_line(map));
	else if (*line == 'R')
		return (map_resolution(map, line));
	else if (*line == 'F')
		return (map_read_color(&map->floor_rgb, line, "F", map->check));
	else if (*line == 'C')
		return (map_read_color(&map->ceiling_rgb, line, "C", map->check));
	else if (*line == 'N')
		return (map_read_texture(&map->north_tex, line, "NO", map->check));
	else if (*line == 'S' && *(line + 1) == 'O')
		return (map_read_texture(&map->south_tex, line, "SO", map->check));
	else if (*line == 'W')
		return (map_read_texture(&map->west_tex, line, "WE", map->check));
	else if (*line == 'E')
		return (map_read_texture(&map->east_tex, line, "EA", map->check));
	else if (*line == 'S' && *(line + 1) != 'O')
		return (map_read_texture(&map->sprite_tex, line, "S", map->check));
	if (map->resolution.x == 0 || map->resolution.y == 0 || map->floor_rgb == -1
		|| map->ceiling_rgb == -1 || map->north_tex == 0 || map->south_tex == 0
		|| map->west_tex == 0 || map->east_tex == 0 || map->sprite_tex == 0)
		return (-1);
	return (map_information(map, line));
}

/*
**		Shortens the line. Cuts everything after the first new line.
*/

char	*cut_line(char *line)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	result = malloc(sizeof(char) * (i + 1));
	if (result == NULL)
	{
		free(line);
		return (NULL);
	}
	j = 0;
	while (j < i)
	{
		result[j] = line[j];
		j++;
	}
	result[j] = '\0';
	free(line);
	line = NULL;
	return (result);
}

/*
**		Get next line. Also processes the line.
*/

int		process_cub_info(t_map *map, char *str, char *line)
{
	int		i;

	if (ft_strchr(line, '\n') == 1)
		line = cut_line(line);
	if (line == NULL)
		return (-1);
	map->resolution.x = map->resolution.x;
	if (check_valid_info(map, line) == -1)
	{
		free(line);
		return (-1);
	}
	free(line);
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\n')
	{
		ft_strcpy(str, str + i + 1);
		return (1);
	}
	return (0);
}

/*
**		Get next line.
*/

int		read_cub_file(t_map *map, int fd)
{
	static char	str[BUFF_SIZE + 1];
	char		*line;
	int			ret;

	if (read(fd, NULL, 0) == -1)
		return (-1);
	line = ft_strdup(str);
	if (line == NULL)
		return (-1);
	ret = 1;
	while (ret > 0 && ft_strchr(line, '\n') == 0)
	{
		ret = read(fd, str, BUFF_SIZE);
		if (ret == -1)
		{
			free(line);
			return (-1);
		}
		str[ret] = '\0';
		line = ft_strjoin(line, str);
		if (line == NULL)
			return (-1);
	}
	return (process_cub_info(map, str, line));
}

/*
**		Main function about the given cub file. Reads and processes the file.
*/

int		parse_map(t_map *map, char *str)
{
	int		fd;
	int		ret;

	if (str == NULL)
		return (-1);
	if (ft_strncmp(str + ft_strlen(str) - 4, ".cub", 4) != 0)
		return (-1);
	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (-1);
	create_empty_map(map);
	if (map->map == NULL)
		return (-1);
	ret = 1;
	while (ret == 1)
		ret = read_cub_file(map, fd);
	printf("ret1: [%i]\n", ret);
	if (ret == 0)
		ret = check_valid_map(map);
	if (ret == -1)
		free_array(map->map);
	close(fd);
	printf("ret2: [%i]\n", ret);
	return (ret);
}
