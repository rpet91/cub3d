/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map2_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/10 11:02:18 by rpet          #+#    #+#                 */
/*   Updated: 2020/03/11 09:18:14 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "../cub3d_bonus.h"

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
	if (ft_strcmp(resolution[0], "R") != 0 || resolution[3] != NULL ||
		ft_isnumeric(resolution[1]) == 0 || ft_isnumeric(resolution[2]) == 0)
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

void	read_color(char **tex, int *rgb, char *str, t_data *mlx)
{
	int		color;

	color = 0;
	if (*tex != 0 || *rgb != -1 || mlx->map.check != 0 || *str != ' ')
		error_handling(WRONG_INFO, mlx);
	while (*str == ' ')
		str++;
	*rgb = get_color(str);
	if (get_color(str) == -1)
		color = 1;
	if (color == 1)
	{
		*rgb = -2;
		read_tex(tex, str - 1, mlx);
	}
	else
		*tex = malloc(1);
	if (*tex == NULL && color == 0)
		error_handling(MALLOC, mlx);
}

/*
**		Checks if there is a valid given texture string for the walls.
*/

void	read_tex(char **tex, char *str, t_data *mlx)
{
	if (*tex != 0 || mlx->map.check != 0 || *str != ' ')
		error_handling(WRONG_INFO, mlx);
	while (*str == ' ')
		str++;
	if (open(str, O_RDONLY) == -1)
		error_handling(WRONG_TEXTURE, mlx);
	*tex = ft_strdup(str);
	if (*tex == NULL)
		error_handling(MALLOC, mlx);
	if (ft_strcmp(*tex + ft_strlen(*tex) - 4, ".png") != 0 &&
		ft_strcmp(*tex + ft_strlen(*tex) - 4, ".xpm") != 0)
		error_handling(WRONG_TEXTURE, mlx);
}
