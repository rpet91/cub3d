/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map2.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/10 11:02:18 by rpet          #+#    #+#                 */
/*   Updated: 2020/03/03 13:51:45 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "../cub3d.h"

/*
**		Reads info about map size.
*/

void	map_resolution(t_data *mlx, char *str)
{
	char	**resolution;

	if (mlx->map.res.x != 0 || mlx->map.res.y != 0 || mlx->map.check != 0)
		error_handling(WRONG_INFO, mlx);
	resolution = ft_split(str, ' ');
	if (resolution == NULL)
		error_handling(MALLOC, mlx);
	if (ft_strncmp(resolution[0], "R", ft_strlen(resolution[0])) != 0
			|| resolution[3] != NULL)
	{
		free_array(resolution);
		error_handling(WRONG_INFO, mlx);
	}
	mlx->map.res.x = ft_atoi(resolution[1]);
	mlx->map.res.y = ft_atoi(resolution[2]);
	free_array(resolution);
	if (mlx->map.res.x < 1 || mlx->map.res.y < 1)
		error_handling(WRONG_RES_SIZE, mlx);
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

void	read_color(int *rgb, char *str, char *loc, t_data *mlx)
{
	char	**color;

	if (*rgb != -1 || mlx->map.check != 0)
		error_handling(WRONG_INFO, mlx);
	color = ft_split(str, ' ');
	if (color == NULL)
		error_handling(MALLOC, mlx);
	if (ft_strncmp(color[0], loc, ft_strlen(color[0])) != 0 || color[2] != NULL)
	{
		free_array(color);
		error_handling(WRONG_INFO, mlx);
	}
	*rgb = get_color(color[1]);
	if (get_color(color[1]) == -1)
	{
		free_array(color);
		error_handling(WRONG_COLOR, mlx);
	}
	free_array(color);
}

/*
**		Checks if there is a valid given texture string for the walls.
*/

void	read_tex(char **wall, char *str, char *loc, t_data *mlx)
{
	char	**text;

	if (*wall != 0 || mlx->map.check != 0)
		error_handling(WRONG_INFO, mlx);
	text = ft_split(str, ' ');
	if (text == NULL)
		error_handling(MALLOC, mlx);
	if (ft_strncmp(text[0], loc, ft_strlen(text[0])) != 0 || text[2] != NULL)
	{
		free_array(text);
		error_handling(WRONG_INFO, mlx);
	}
	*wall = ft_strdup(text[1]);
	free_array(text);
	if (*wall == NULL)
		error_handling(MALLOC, mlx);
	if (open(*wall, O_RDONLY) == -1)
		error_handling(WRONG_TEXTURE, mlx);
	if (ft_strncmp(*wall + ft_strlen(*wall) - 4, ".png", 4) != 0 &&
		ft_strncmp(*wall + ft_strlen(*wall) - 4, ".xpm", 4) != 0)
		error_handling(WRONG_TEXTURE, mlx);
}
