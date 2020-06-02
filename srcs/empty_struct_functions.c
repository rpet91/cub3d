/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   empty_struct_functions.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/03 15:13:52 by rpet          #+#    #+#                 */
/*   Updated: 2020/03/12 17:34:31 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../cub3d.h"

/*
**		Creates a new map with every value set to zero.
*/

void	empty_map(t_data *mlx)
{
	mlx->map.player.x = 0;
	mlx->map.player.y = 0;
	mlx->map.res.x = 0;
	mlx->map.res.y = 0;
	mlx->map.size.x = 0;
	mlx->map.size.y = 0;
	mlx->map.line = NULL;
	mlx->map.north_tex = NULL;
	mlx->map.south_tex = NULL;
	mlx->map.west_tex = NULL;
	mlx->map.east_tex = NULL;
	mlx->map.sprite_tex = NULL;
	mlx->map.floor_tex = NULL;
	mlx->map.ceiling_tex = NULL;
	mlx->map.floor_rgb = -1;
	mlx->map.ceiling_rgb = -1;
	mlx->map.check = 0;
	mlx->map.map = malloc(sizeof(char *));
	if (mlx->map.map == NULL)
		error_handling(MALLOC, mlx);
	mlx->map.map[0] = NULL;
}

void	empty_textures(t_data *mlx)
{
	mlx->list_tex.north.img.img = NULL;
	mlx->list_tex.south.img.img = NULL;
	mlx->list_tex.west.img.img = NULL;
	mlx->list_tex.east.img.img = NULL;
	mlx->list_tex.sprite.img.img = NULL;
	mlx->list_tex.floor.img.img = NULL;
	mlx->list_tex.ceiling.img.img = NULL;
	mlx->list.amount = 0;
	mlx->list.sprites = NULL;
}

void	empty_mlx(t_data *mlx)
{
	mlx->mlx = NULL;
	mlx->win = NULL;
	mlx->img1.img = NULL;
	mlx->img2.img = NULL;
	mlx->ray.dis_buffer = NULL;
}
