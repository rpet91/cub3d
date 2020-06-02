/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map1.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/07 11:05:08 by rpet          #+#    #+#                 */
/*   Updated: 2020/03/12 17:35:50 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "../cub3d.h"

/*
**		Checks, refers and processes the given line.
*/

void	check_valid_info(t_data *mlx, char *line)
{
	if (*line == ' ' || *(line + ft_strlen(line) - 1) == ' ')
		element_validation(mlx);
	if (*line == '\0')
		mlx->map.check = (mlx->map.check == 1) ? 2 : mlx->map.check;
	else if (*line == 'R')
		map_resolution(mlx, line);
	else if (*line == 'F')
		read_color(&mlx->map.floor_tex, &mlx->map.floor_rgb, line + 1, mlx);
	else if (*line == 'C')
		read_color(&mlx->map.ceiling_tex, &mlx->map.ceiling_rgb, line + 1, mlx);
	else if (*line == 'N' && *(line + 1) == 'O')
		read_tex(&mlx->map.north_tex, line + 2, mlx);
	else if (*line == 'S' && *(line + 1) == 'O')
		read_tex(&mlx->map.south_tex, line + 2, mlx);
	else if (*line == 'W' && *(line + 1) == 'E')
		read_tex(&mlx->map.west_tex, line + 2, mlx);
	else if (*line == 'E' && *(line + 1) == 'A')
		read_tex(&mlx->map.east_tex, line + 2, mlx);
	else if (*line == 'S' && *(line + 1) != 'O')
		read_tex(&mlx->map.sprite_tex, line + 1, mlx);
	else
		map_information(mlx, mlx->map.line);
}

/*
**		Processes the given line. Checks if it's valid.
*/

int		process_cub_info(t_data *mlx, char *str)
{
	int		i;

	i = 0;
	while (mlx->map.line[i] != '\0')
	{
		if (mlx->map.line[i] == '\n')
			mlx->map.line[i] = '\0';
		i++;
	}
	check_valid_info(mlx, mlx->map.line);
	free(mlx->map.line);
	mlx->map.line = NULL;
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\n')
	{
		ft_strcpy(str, str + i + 1);
		return (1);
	}
	mlx->map.map = make_rectangle(mlx);
	if (mlx->map.map == NULL)
		error_handling(MALLOC, mlx);
	return (0);
}

/*
**		Get next line.
*/

int		read_cub_file(t_data *mlx, int fd)
{
	static char	str[BUFF_SIZE + 1];
	int			ret;

	if (read(fd, NULL, 0) == -1)
		error_handling(READ_ERROR, mlx);
	mlx->map.line = ft_strdup(str);
	if (mlx->map.line == NULL)
		error_handling(MALLOC, mlx);
	ret = 1;
	while (ret > 0 && ft_strchr_i(mlx->map.line, '\n') == 0)
	{
		ret = read(fd, str, BUFF_SIZE);
		if (ret == -1)
			error_handling(READ_ERROR, mlx);
		str[ret] = '\0';
		mlx->map.line = ft_strjoin(mlx->map.line, str);
		if (mlx->map.line == NULL)
			error_handling(MALLOC, mlx);
	}
	return (process_cub_info(mlx, str));
}

/*
**		Main function about the given cub file. Reads and processes the file.
*/

void	parse_map(t_data *mlx, char *str)
{
	int		ret;

	empty_textures(mlx);
	empty_map(mlx);
	if (ft_strcmp(str + ft_strlen(str) - 4, ".cub") != 0)
		error_handling(NO_CUB, mlx);
	mlx->map.fd = open(str, O_RDONLY);
	if (mlx->map.fd == -1)
		error_handling(INVALID_CUB, mlx);
	ret = 1;
	while (ret == 1)
		ret = read_cub_file(mlx, mlx->map.fd);
	close(mlx->map.fd);
	mlx->map.fd = -1;
	check_valid_map(mlx);
}
