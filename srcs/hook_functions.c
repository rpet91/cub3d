/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hook_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/05 15:25:20 by rpet          #+#    #+#                 */
/*   Updated: 2020/03/06 14:01:49 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "../cub3d.h"

int		key_press(int keycode, t_data *mlx)
{
	if (keycode == ESC_BUTTON)
		close_game(mlx);
	if (keycode == KEY_W)
		mlx->move.w = 1;
	if (keycode == KEY_S)
		mlx->move.s = 1;
	if (keycode == KEY_A)
		mlx->move.a = 1;
	if (keycode == KEY_D)
		mlx->move.d = 1;
	if (keycode == KEY_LEFT)
		mlx->move.left = 1;
	if (keycode == KEY_RIGHT)
		mlx->move.right = 1;
	return (0);
}

int		key_release(int keycode, t_data *mlx)
{
	if (keycode == KEY_W)
		mlx->move.w = 0;
	if (keycode == KEY_S)
		mlx->move.s = 0;
	if (keycode == KEY_A)
		mlx->move.a = 0;
	if (keycode == KEY_D)
		mlx->move.d = 0;
	if (keycode == KEY_LEFT)
		mlx->move.left = 0;
	if (keycode == KEY_RIGHT)
		mlx->move.right = 0;
	return (0);
}

int		mouse_move(int x, int y, t_data *mlx)
{
	if (x < 0 || y < 0 || x > mlx->map.res.x || y > mlx->map.res.y)
		return (0);
	if (x - mlx->mouse < 0)
		rotate_player(mlx, -0.1);
	else if (x - mlx->mouse > 0)
		rotate_player(mlx, 0.1);
	else
		rotate_player(mlx, 0);
	mlx->mouse = x;
	return (0);
}

int		close_game(t_data *mlx)
{
	destroy_textures(mlx);
	free_sprite_array(mlx);
	free_map(mlx);
	destroy_mlx(mlx);
	exit(0);
	return (0);
}
