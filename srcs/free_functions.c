/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/03 12:59:01 by rpet          #+#    #+#                 */
/*   Updated: 2020/03/10 15:10:25 by rpet          ########   odam.nl         */
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
	if (str)
	{
		free(str);
		str = NULL;
	}
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
	{
		free(mlx->list.sprites);
		mlx->list.sprites = NULL;
	}
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

void	free_map(t_data *mlx)
{
	if (mlx->map.fd > 2)
		close(mlx->map.fd);
	if (mlx->map.line != NULL)
		free(mlx->map.line);
	if (mlx->map.north_tex != NULL)
		free(mlx->map.north_tex);
	if (mlx->map.south_tex != NULL)
		free(mlx->map.south_tex);
	if (mlx->map.west_tex != NULL)
		free(mlx->map.west_tex);
	if (mlx->map.east_tex != NULL)
		free(mlx->map.east_tex);
	if (mlx->map.sprite_tex != NULL)
		free(mlx->map.sprite_tex);
	if (mlx->map.floor_tex != NULL)
		free(mlx->map.floor_tex);
	if (mlx->map.ceiling_tex != NULL)
		free(mlx->map.ceiling_tex);
	if (mlx->map.map != NULL)
		free_array(mlx->map.map);
}

void	destroy_mlx(t_data *mlx)
{
	if (mlx->img1.img != NULL)
		mlx_destroy_image(mlx->mlx, mlx->img1.img);
	if (mlx->img2.img != NULL)
		mlx_destroy_image(mlx->mlx, mlx->img2.img);
	if (mlx->win != NULL)
		mlx_destroy_window(mlx->mlx, mlx->win);
}
