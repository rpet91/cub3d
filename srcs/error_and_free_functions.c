/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_and_free_functions.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/26 18:01:18 by rpet          #+#    #+#                 */
/*   Updated: 2020/03/03 10:47:51 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <mlx.h>
#include "../cub3d.h"

void	free_array(char **str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}

void	free_sprite_array(t_data *mlx)
{
	int			i;

	i = 0;
	while (i < mlx->list.amount)
	{
		free(mlx->list.sprites[i]);
		mlx->list.sprites[i] = NULL;
		i++;
	}
	if (mlx->list.sprites != NULL)
		free(mlx->list.sprites);
	mlx->list.sprites = NULL;
}

void	destroy_textures(t_data *mlx)
{
	int			i;
	t_texture	*cur;

	i = 0;
	while (i < 5)
	{
		cur = select_texture_img(mlx, i);
		if (cur->img.img != NULL)
			mlx_destroy_image(mlx->mlx, cur->img.img);
		i++;
	}
}

void	map_error_handling(char *str, t_map *map)
{
	if (map->line != NULL)
		free(map->line);
	if (map->north_tex != NULL)
		free(map->north_tex);
	if (map->south_tex != NULL)
		free(map->south_tex);
	if (map->west_tex != NULL)
		free(map->west_tex);
	if (map->east_tex != NULL)
		free(map->east_tex);
	if (map->sprite_tex != NULL)
		free(map->sprite_tex);
	free_array(map->map);
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd("\n", 1);
	exit(1);
}

void	error_handling(char *str, t_data *mlx)
{
	destroy_textures(mlx);
	free_sprite_array(mlx);
	if (mlx->img1.img != NULL)
		mlx_destroy_image(mlx->mlx, mlx->img1.img);
	if (mlx->img2.img != NULL)
		mlx_destroy_image(mlx->mlx, mlx->img2.img);
	if (mlx->mlx != NULL)
		mlx_destroy_window(mlx->mlx, mlx->win);
	map_error_handling(str, &mlx->map);
}
