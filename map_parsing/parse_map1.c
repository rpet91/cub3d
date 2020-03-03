/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map1.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/07 11:05:08 by rpet          #+#    #+#                 */
/*   Updated: 2020/02/27 16:00:17 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "../cub3d.h"

/*
**		Checks, refers and processes the given line.
*/

void	check_valid_info(t_map *map, char *line)
{
	if (*line == '\0')
		map->check = (map->check == 1) ? 2 : map->check;
	else if (*line == ' ' || *(line + ft_strlen(line) - 1) == ' ')
		map_error_handling(INVALID_CHAR, map);
	else if (*line == 'R')
		map_resolution(map, map->line);
	else if (*line == 'F')
		map_read_color(&map->floor_rgb, line, "F", map);
	else if (*line == 'C')
		map_read_color(&map->ceiling_rgb, line, "C", map);
	else if (*line == 'N')
		map_read_tex(&map->north_tex, line, "NO", map);
	else if (*line == 'S' && *(line + 1) == 'O')
		map_read_tex(&map->south_tex, line, "SO", map);
	else if (*line == 'W')
		map_read_tex(&map->west_tex, line, "WE", map);
	else if (*line == 'E')
		map_read_tex(&map->east_tex, line, "EA", map);
	else if (*line == 'S' && *(line + 1) != 'O')
		map_read_tex(&map->sprite_tex, line, "S", map);
	else
		element_validation(map);
}

/*
**		Processes the given line. Checks if it's valid.
*/

int		process_cub_info(t_map *map, char *str)
{
	int		i;

	i = 0;
	while (map->line[i] != '\0')
	{
		if (map->line[i] == '\n')
			map->line[i] = '\0';
		i++;
	}
	check_valid_info(map, map->line);
	free(map->line);
	map->line = NULL;
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\n')
	{
		ft_strcpy(str, str + i + 1);
		return (1);
	}
	map->map = make_rectangle(map);
	if (map->map == NULL)
		map_error_handling(MALLOC, map);
	return (0);
}

/*
**		Get next line.
*/

int		read_cub_file(t_map *map, int fd)
{
	static char	str[BUFF_SIZE + 1];
	int			ret;

	if (read(fd, NULL, 0) == -1)
		map_error_handling(READ_ERROR, map);
	map->line = ft_strdup(str);
	if (map->line == NULL)
		map_error_handling(MALLOC, map);
	ret = 1;
	while (ret > 0 && ft_strchr(map->line, '\n') == 0)
	{
		ret = read(fd, str, BUFF_SIZE);
		if (ret == -1)
			map_error_handling(READ_ERROR, map);
		str[ret] = '\0';
		map->line = ft_strjoin(map->line, str);
		if (map->line == NULL)
			map_error_handling(MALLOC, map);
	}
	return (process_cub_info(map, str));
}

/*
**		Main function about the given cub file. Reads and processes the file.
*/

void	parse_map(t_map *map, char *str)
{
	int		ret;

	if (ft_strncmp(str + ft_strlen(str) - 4, ".cub", 4) != 0)
		map_error_handling(NO_CUB, map);
	map->fd = open(str, O_RDONLY);
	if (map->fd == -1)
		map_error_handling(NO_CUB, map);
	create_empty_map(map);
	ret = 1;
	while (ret == 1)
		ret = read_cub_file(map, map->fd);
	close(map->fd);
	check_valid_map(map);
}
